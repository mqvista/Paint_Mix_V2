#include "motionworker.h"
#include "utils/errorhandle.h"

MotionWorker* MotionWorker::Instance()
{
    static QMutex mutex;
    static QScopedPointer<MotionWorker> instance;
    if (Q_UNLIKELY(!instance)) {
        mutex.lock();
        if (!instance) {
            instance.reset(new MotionWorker);
        }
        mutex.unlock();
    }
    return instance.data();
}

void MotionWorker::openSerial485()
{
    qDebug() << "Motion thread" << QThread::currentThreadId() << endl;
    Motion::Instance()->openSerial485("45VBMPWF");
    if (!Motion::Instance()->openSerial485("45VBMPWF")) {
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_RS485_OPEN_FAILED);
    }
}

// 初始化板子和旋转轴
void MotionWorker::initDeviceMotor()
{
    if (!Motion::Instance()->initBoard()) {
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_BOARD_INIT_FAILED);
        return;
    }
    for (quint8 i = 0; i <= 10; i++) {
        if (!Motion::Instance()->initAsixMotor(i)) {
            ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_ROTARY_INIT_FAILED);
            return;
        }
    }
    emit isIniting(false);
}

void MotionWorker::closeSerial485()
{
    Motion::Instance()->closeSerial485();
}

void MotionWorker::addWater(quint32 weight, quint8 scalesNum)
{
    Motion::Instance()->addWater(weight, scalesNum);
}

void MotionWorker::initAsix(quint8 motorNum)
{
    Motion::Instance()->initAsixMotor(motorNum);
}

void MotionWorker::liquidOut(quint8 motorNum, quint32 weight, quint8 scalesNum)
{
    Motion::Instance()->liquidOut(motorNum, weight, scalesNum);
}

// 单次运行方案，执行完毕后停止
void MotionWorker::runFormula(const QString& formulaName, bool needRunningFlag)
{
    if (needRunningFlag) {
        emit runningStatus(true);
    }

    // 先确保tank液位在最上面
    Motion::Instance()->topUpTank();

    // 设置一个变量保存读取出来的数据
    QMap<quint16, QMap<QString, QString>> formula;
    qint16 length;
    // 读取方案文件
    fileReadWrite.readProfileDetail(formulaName, &formula, &length);

    // 循环qmap 找出每一个步骤，并执行
    for (quint8 i = 1; i <= length; i++) {
        // 建立一个子 qmap， 存储循环出来的数据
        QMap<QString, QString> subFormula;
        subFormula = formula.value(i);

        // 判断是否有 Motor 注液流且 Motor 唯一
        if (subFormula.count("Motor") == 1) {
            quint8 motorNum = quint8(subFormula.value("Motor").toUShort());
            quint8 scaleNum = quint8(subFormula.value("Scales").toUShort());
            quint32 weight = subFormula.value("Weight").toUInt();
            // 运动到指定位置
            if (!Motion::Instance()->moveAsixToScales(Motion::Instance()->converyDegree(motorNum, scaleNum))) {
                // 通知错误处理
                ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_ROTARY_ENCODER);
                break;
            }
            // 放水
            if (!Motion::Instance()->liquidOut(motorNum, weight, scaleNum)) {
                break;
            }
            continue;
        }
        // 判断是放清水
        if (subFormula.count("Water") == 1) {
            quint8 scaleNum = quint8(subFormula.value("Scales").toUShort());
            quint32 weight = subFormula.value("Weight").toUInt();
            if (!Motion::Instance()->addWater(weight, scaleNum)) {
                break;
            }
            continue;
        }
        //
        if (subFormula.count("PumpScaleOutside") == 1) {
            quint8 scaleNum = quint8(subFormula.value("PumpScaleOutside").toUShort());
            if (!Motion::Instance()->pumpToOutSide(scaleNum)) {
                break;
            }
            continue;
        }
        // 判断是否是搬运水
        if (subFormula.count("AddWaterMiddle") == 1) {
            double liter = subFormula.value("Weight").toDouble();
            if (!Motion::Instance()->addWaterMiddleTank(liter)) {
                break;
            }
            continue;
        }
    }
    if (needRunningFlag) {
        emit runningStatus(false);
    }
}

void MotionWorker::runFormula(const QMap<quint16, QMap<QString, QString>> singleFormula, quint8 length)
{
    // 循环qmap 找出每一个步骤，并执行
    for (quint8 i = 1; i <= length; i++) {
        // 建立一个子 qmap， 存储循环出来的数据
        QMap<QString, QString> subFormula;
        subFormula = singleFormula.value(i);

        // 判断是否有 Motor 注液流且 Motor 唯一
        if (subFormula.count("Motor") == 1) {
            quint8 motorNum = quint8(subFormula.value("Motor").toUShort());
            quint8 scaleNum = quint8(subFormula.value("Scales").toUShort());
            quint32 weight = quint32(subFormula.value("Weight").toFloat());
            // 运动到指定位置
            if (!Motion::Instance()->moveAsixToScales(Motion::Instance()->converyDegree(motorNum, scaleNum))) {
                // 通知错误处理
                ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_ROTARY_ENCODER);
                break;
            }
            // 放水
            if (!Motion::Instance()->liquidOut(motorNum, weight, scaleNum)) {
                break;
            }
            continue;
        }
        // 判断是放清水
        if (subFormula.count("Water") == 1) {
            quint8 scaleNum = quint8(subFormula.value("Scales").toUShort());
            quint32 weight = quint32(subFormula.value("Weight").toFloat());
            if (!Motion::Instance()->addWater(weight, scaleNum)) {
                break;
            }
            continue;
        }
        //
        if (subFormula.count("PumpScaleOutside") == 1) {
            quint8 scaleNum = quint8(subFormula.value("PumpScaleOutside").toUShort());
            if (!Motion::Instance()->pumpToOutSide(scaleNum)) {
                break;
            }
            continue;
        }
        // 判断是否是搬运水
        if (subFormula.count("AddWaterMiddle") == 1) {
            double liter = subFormula.value("AddWaterMiddle").toDouble();
            if (!Motion::Instance()->addWaterMiddleTank(liter)) {
                break;
            }
            continue;
        }
    }
}

void MotionWorker::runLoopFormula(const QString& formulaName)
{
    emit runningStatus(true);
    double microLiter = 0;
    bool loopFlag = true;
    QBitArray tankLimit;
    while (loopFlag) {
        // 关闭标志
        if (m_stopFlag)
        {
            m_stopFlag = false;
            emit runningStatus(false);
            return;
        }
        // 检测外部液位是否触发
        // 用户浆料槽top 液位 board6， channel 2
        DriverGC::Instance()->Inquire_Limit(6, tankLimit);
        if (!tankLimit.at(2)) {
            Motion::Instance()->pumpMiddleTankToUserTank();
        }

        if (m_stopFlag)
        {
            m_stopFlag = false;
            emit runningStatus(false);
            return;
        }

        // 中桶补充
        sleep(5);
        Motion::Instance()->getMiddleTankLevel(&microLiter);
        if (microLiter < 25000) {
            runFormula(formulaName, false);
        }

        if (m_stopFlag)
        {
            m_stopFlag = false;
            emit runningStatus(false);
            return;
        }
        // 开启中桶搅拌电机
        Motion::Instance()->mixMiddleTank(true);
        sleep(10);
        Motion::Instance()->mixMiddleTank(false);
        sleep(10);

        if (m_stopFlag)
        {
            m_stopFlag = false;
            emit runningStatus(false);
            return;
        }
    }
    emit runningStatus(false);
}

// 单次调整用的
void MotionWorker::runAndSaveNewFormula(QString formulaName, FixedType newFormula)
{
    // 先读取原始的参数, 计算出原始的比例
    qint16 length;
    // 原始的方案重量
    qint32 originalWeight = 0;
    // 修改后的的方案重量
    qint32 fixedWeight = 0;
    QMap<quint16, QMap<QString, QString>> originalFormula;
    QMap<quint16, QMap<QString, QString>> fixedFormula = newFormula;
    double middleTankLiter = 0;
    double finallTankLiter = 0;
    // 获取中桶液位升数
    Motion::Instance()->getMiddleTankLevel(&middleTankLiter);
    if (middleTankLiter < 0) {
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_TANK_IS_EMPTY_OR_TANK_SENSER_ERROR);
        // TODO 取消注释
        //return;
    }
    fileReadWrite.readProfileDetail(formulaName, &originalFormula, &length);

    // 循环qmap 找出每一个步骤，统计总重量
    for (quint8 i = 1; i <= length; i++) {
        // 建立一个子 qmap， 存储循环出来的数据
        QMap<QString, QString> subFormula;
        subFormula = originalFormula.value(i);

        // 判断是否有 weight
        if (subFormula.count("Weight") == 1) {
            quint32 weight = subFormula.value("Weight").toUInt();
            originalWeight += weight;
        }
    }

    // 把百分比带入原来的里面
    for (quint8 i = 1; i <= length; i++) {
        if (originalFormula.value(i).count("Weight") == 1) {
            double percent = originalFormula.value(i).value("Weight").toDouble() / originalWeight;
            originalFormula[i].insert("Percent", QString::number(percent));
            // 计算中桶对应的数量
            double middleLiter = middleTankLiter * percent;
            originalFormula[i].insert("MiddleTankLiter", QString::number(middleLiter));
        }
    }

    // 循环qmap 找出每一个步骤，统计总重量
    for (quint8 i = 1; i <= length; i++) {
        // 建立一个子 qmap， 存储循环出来的数据
        QMap<QString, QString> subFormula;
        subFormula = fixedFormula.value(i);

        // 判断是否有 weight
        if (subFormula.count("Weight") == 1) {
            quint32 weight = subFormula.value("Weight").toUInt();
            fixedWeight += weight;
        }
    }

    // 把百分比带入原来的里面
    for (quint8 i = 1; i <= length; i++) {
        if (fixedFormula.value(i).count("Weight") == 1) {
            double percent = fixedFormula.value(i).value("Weight").toDouble() / fixedWeight;
            fixedFormula[i].insert("Percent", QString::number(percent));
        }
    }

    //求出差旧的和新的差最大的重量
    double maxDifference = 0;
    quint8 maxDifferenceUnit = 0;

    // diffA 判定为大的单元， diffB为临时用的单元
    double diffA = -1;
    quint8 diffAUnit = 0;
    double diffB = 0;
    quint8 diffBUnit = 0;
    // 注意从2开始
    for (quint8 i = 1; i <= length; i++) {
        if (fixedFormula.value(i).count("Weight") == 1) {
            if (diffA <= 0) {
                diffA = originalFormula.value(i).value("Percent").toDouble() - fixedFormula.value(i).value("Percent").toDouble();
                diffAUnit = i;
            }

            diffB = originalFormula.value(i).value("Percent").toDouble() - fixedFormula.value(i).value("Percent").toDouble();
            diffBUnit = i;

            // 对比谁的差最大
            if (diffA >= diffB && diffA > 0) {
                maxDifferenceUnit = diffAUnit;
                maxDifference = diffA;
            } else if (diffB > diffA && diffB > 0) {
                maxDifferenceUnit = diffBUnit;
                maxDifference = diffB;
                diffA = diffB;
                diffAUnit = diffBUnit;
            }
        }
    }

    // 先代入比例差值最大的目标，并代入对应的桶内重量
    if (maxDifferenceUnit == 0) {
        maxDifferenceUnit = 1;
    }
    fixedFormula[maxDifferenceUnit].insert("MiddleTankLiter", originalFormula.value(maxDifferenceUnit).value("MiddleTankLiter"));
    // 算出目标的每个点所占的系数
    double newPrecentModulus = fixedFormula.value(maxDifferenceUnit).value("MiddleTankLiter").toDouble() / fixedFormula.value(maxDifferenceUnit).value("Percent").toDouble();
    ;
    for (quint8 i = 1; i <= length; i++) {
        if (i == maxDifferenceUnit)
            continue;
        if (fixedFormula.value(i).contains("Percent") == 1) {
            double tempMiddleLiter = fixedFormula.value(i).value("Percent").toDouble() * newPrecentModulus;
            fixedFormula[i].insert("MiddleTankLiter", QString::number(tempMiddleLiter));
        }
    }


    bool scaleVoerLoad = false;
    // 新建个qmap 准备参数并运行
    // 按照计算出桶里面的重量比例来秤分量
    QMap<quint16, QMap<QString, QString>> formulaToRun;
    quint8 count = 1;
    for (quint8 i = 1; i <= length; i++) {
        double tempOrigWeight, tempFixedWeight;
        if (originalFormula.value(i).contains("Percent") == 1) {
            tempOrigWeight = originalFormula.value(i).value("MiddleTankLiter").toDouble();
            tempFixedWeight = fixedFormula.value(i).value("MiddleTankLiter").toDouble();
            if (tempFixedWeight - tempOrigWeight > 0) {
                QMap<QString, QString> subFormula;
                if (originalFormula.value(i).contains("Motor") == 1) {
                    subFormula.insert("Motor", originalFormula.value(i).value("Motor"));
                    subFormula.insert("Scales", originalFormula.value(i).value("Scales"));
                    subFormula.insert("Weight", QString::number(tempFixedWeight - tempOrigWeight, 'd', 1));
                    formulaToRun.insert(count, subFormula);
                    // 判断是否超重小秤
                    if (originalFormula.value(i).value("Scales") == "1")
                    {
                        if (QString::number(tempFixedWeight - tempOrigWeight, 'd', 1) > 200)
                        {
                            scaleVoerLoad = true;
                        }
                    }
                    // 判断是否超重大秤
                    if (originalFormula.value(i).value("Scales") == "1")
                    {
                        if (QString::number(tempFixedWeight - tempOrigWeight, 'd', 1) > 3000)
                        {
                            scaleVoerLoad = true;
                        }
                    }
                    count++;
                    // 统计桶内重量
                    finallTankLiter += tempFixedWeight;
                    continue;
                }
                if (originalFormula.value(i).contains("Water") == 1) {
                    subFormula.insert("Water", "1");
                    subFormula.insert("Scales", originalFormula.value(i).value("Scales"));
                    subFormula.insert("Weight", QString::number(tempFixedWeight - tempOrigWeight, 'd', 1));
                    formulaToRun.insert(count, subFormula);
                    count++;
                    // 统计桶内重量
                    finallTankLiter += tempFixedWeight;
                    continue;
                }
                if (originalFormula.value(i).contains("AddWaterMiddle") == 1) {
                    subFormula.insert("AddWaterMiddle", "1");
                    subFormula.insert("Weight", QString::number(tempFixedWeight - tempOrigWeight, 'd', 1));
                    formulaToRun.insert(count, subFormula);
                    count++;
                    // 统计桶内重量
                    finallTankLiter += tempFixedWeight;
                    continue;
                }
            }
        }
    }

    // 先判断桶内容量和秤上分量是否足够这次调整，不够就不调整，并用ERROR_HANDLER 提示用户
    if (middleTankLiter > 30000) {
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_TANK_WILL_OVER_LIMIT);
        return;
    }
    if (scaleVoerLoad)
    {
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_TANK_WILL_OVER_LIMIT);
        return;
    }


    emit runningStatus(true);
    runFormula(formulaToRun, count);
    emit runningStatus(false);
    fileReadWrite.replaceProfileDetail(formulaName, newFormula, length);

    // TODO QML 设定微调不能超过2G,单个颜料
}

void MotionWorker::moveAsix(quint8 num)
{
    switch (num) {
    case 1:
        Motion::Instance()->moveAsixToScales(Motion::scales1Motor01);
        break;
    case 2:
        Motion::Instance()->moveAsixToScales(Motion::scales1Motor02);
        break;
    case 3:
        Motion::Instance()->moveAsixToScales(Motion::scales1Motor03);
        break;
    case 4:
        Motion::Instance()->moveAsixToScales(Motion::scales1Motor04);
        break;
    case 5:
        Motion::Instance()->moveAsixToScales(Motion::scales1Motor05);
        break;
    case 6:
        Motion::Instance()->moveAsixToScales(Motion::scales1Motor06);
        break;
    case 7:
        Motion::Instance()->moveAsixToScales(Motion::scales1Motor07);
        break;
    case 8:
        Motion::Instance()->moveAsixToScales(Motion::scales1Motor08);
        break;
    case 9:
        Motion::Instance()->moveAsixToScales(Motion::scales1Motor09);
        break;
    case 10:
        Motion::Instance()->moveAsixToScales(Motion::scales1Motor10);
        break;
    default:
        break;
    }
}

void MotionWorker::getExternADCValue()
{
    double tmp;
    Motion::Instance()->getMiddleTankLevel(&tmp);
}

// test use
void MotionWorker::openExtrenPump()
{
    //Motion::Instance()->pumpMiddleTankToUserTank(true);
}

// test use
void MotionWorker::closeExtrenPump()
{
    //Motion::Instance()->pumpMiddleTankToUserTank(false);
}

MotionWorker::MotionWorker()
{
    qRegisterMetaType<FixedType>("FixedType");
}

void MotionWorker::getStopCurrentSignal()
{
    m_stopFlag = true;
}
