#include "motion.h"
#include <utils/errorhandle.h>

Motion::Motion()
{

}

Motion *Motion::Instance()
{
    static QMutex mutex;
    static QScopedPointer<Motion> instance;
    if (Q_UNLIKELY(!instance)) {
        mutex.lock();
        if (!instance) {
            instance.reset(new Motion);
        }
        mutex.unlock();
    }
    return instance.data();
}

// Open DriverGC Serial Port
// Param1: Target Serial port url
// Param2: Target Serial port baud
bool Motion::openSerial485(QString portSN)
{
    if (!DriverGC::Instance()->OpenUseSN(portSN))
    {
        return false;
    }
    // NOTE Get Serial Error
    connect(DriverGC::Instance(), &DriverGC::ErrorOut, this, &Motion::serial485Error);
    // NOTE Get Debug Data
    //connect(DriverGC::Instance(), &DriverGC::DebugOut, this, &Motion::driverGCDebugInfo);
    return true;
}

// Close DriverGc Serial Port
// No Params
bool Motion::closeSerial485()
{
    DriverGC::Instance()->Close();
    disconnect(DriverGC::Instance(), &DriverGC::ErrorOut, this, &Motion::serial485Error);
    //disconnect(DriverGC::Instance(), &DriverGC::DebugOut, this, &Motion::driverGCDebugInfo);
    return true;
}

// Init all board or it will not work
// No Params
bool Motion::initBoard()
{
    for(quint8 i=1; i<9; i++)
    {
        if (!DriverGC::Instance()->Special_Reset(i))
        {
            return false;
        }
        if (!DriverGC::Instance()->Special_Init(i))
        {
            return false;
        }
    }
    return true;
}

// Get Serial 485 error message from DriverGC signal
// Param1: Error message main
// Param2: Error message sub
void Motion::serial485Error(QString msg1, QString msg2)
{
    qDebug() << "485ERROR-MSG1:" << msg1;
    qDebug() << "485ERROR-MSG2:" << msg2;
}

// 输出driverGC的log
void Motion::driverGCDebugInfo(QString msg, QDateTime curTime)
{
    qDebug()<<curTime.toString("hh:mm:ss.zzz")<<":"<< msg;
}

// Get the small scales senser data (is a slot)
// Parma1: scales value
void Motion::getSmallScalesValue(double value)
{
    m_SmallScalesValue = value;
}

// Get the big scales senser data (is a slot)
// Parma1: scales value
void Motion::getBigScalesValue(double value)
{
    m_BigScalesValue = value;
}

void Motion::getStopCurrentSignal()
{
    m_stopFlag = true;
}

// Block thread untils the motor is free
// Param1: motor number
void Motion::waitWhileFree(quint16 motor)
{
    bool state = true;
    switch (motor) {
    case 0:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(6, 1, state);
            msleep(500);
        }
        break;
    case 1:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(1, 1, state);
            msleep(500);
        }
        break;
    case 2:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(1, 2, state);
            msleep(500);
        }
        break;
    case 3:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(2, 1, state);
            msleep(500);
        }
        break;
    case 4:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(2, 2, state);
            msleep(500);
        }
        break;
    case 5:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(3, 1, state);
            msleep(500);
        }
        break;
    case 6:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(3, 2, state);
            msleep(500);
        }
        break;
    case 7:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(4, 1, state);
            msleep(500);
        }
        break;
    case 8:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(4, 2, state);
            msleep(500);
        }
        break;
    case 9:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(5, 1, state);
            msleep(500);
        }
        break;
    case 10:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(5, 2, state);
            msleep(500);
        }
        break;
    case 11:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(6, 1, state);
            msleep(500);
        }
        break;
    case 12:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(6, 2, state);
            msleep(500);
        }
        break;
    case 13:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(7, 1, state);
            msleep(500);
        }
        break;
    case 14:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(7, 2, state);
            msleep(500);
        }
        break;
    case 15:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(8, 1, state);
            msleep(500);
        }
        break;
    case 16:
        while (state)
        {
            DriverGC::Instance()->Inquire_Status(8, 2, state);
            msleep(500);
        }
        break;
    default:
        break;
    }
}

void Motion::m_MoveAsixToTop(quint8 boadrAddr, quint8 motorChannel)
{
    // Fast rise motor asix
    DriverGC::Instance()->Setting_SM_Speed(boadrAddr, motorChannel, 30000, 90000);
    // 应为每个电机轴的高度都不一样，需要设置不同的上移步数
    if (boadrAddr == 1 && motorChannel == 1)
    {
      DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 22000);
    }
    else if (boadrAddr == 1 && motorChannel == 2)
    {
        DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 5000);
    }
    else if (boadrAddr == 2 && motorChannel == 1)
    {
        DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 11000);
    }
    else if (boadrAddr == 2 && motorChannel == 2)
    {
        DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 23000);
    }
    else if (boadrAddr == 3 && motorChannel == 1)
    {
        DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 8000);
    }
    else if (boadrAddr == 3 && motorChannel == 2)
    {
        DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 13000);
    }
    else if (boadrAddr == 4 && motorChannel == 1)
    {
        DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 9000);
    }
    else if (boadrAddr == 4 && motorChannel == 2)
    {
        DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 9000);
    }
    else if (boadrAddr == 5 && motorChannel == 1)
    {
        DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 8500);
    }
    else if (boadrAddr == 5 && motorChannel == 2)
    {
        DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 12000);
    }
}

// Init the Motor the you start the system
// Param1: Motor number 0 ~ 10
bool Motion::initAsixMotor(quint8 motorNum)
{
    switch (motorNum) {
    //初始化0号轴(圆台运动轴/A轴)
    case 0:
        //设定A轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(6, 1, DriverGC::StepMotor_CW, 0);
        DriverGC::Instance()->Setting_Protect_Limit(6, 1, DriverGC::StepMotor_CCW, 1);
        //设定A轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(6, 1, DriverGC::StepMotor_CW);
        //保存设定
        DriverGC::Instance()->Special_Save(6);
        //设定A轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(6, 1, 20000, 60000);
        //走A轴的CCW极限
        DriverGC::Instance()->AutoControl_SM_By_Limit(6, 1, DriverGC::StepMotor_CCW, 1);
        //阻塞线程，等待电机到位, asix 0
        waitWhileFree(0);
        //清除编码器数值 并保存清除过后的编码器数值
        DriverGC::Instance()->Setting_Encoder_Zero(6, 2);
        DriverGC::Instance()->Inquire_Encoder(6, 2, m_EncoderData);
        //9号轴的绝对角度为0
        m_CurrentDegree = 0;
        break;
    //初始化1号注射轴
    case 1:
        //设定M1轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(1, 1, DriverGC::StepMotor_CW, 0);
        DriverGC::Instance()->Setting_Protect_Limit(1, 1, DriverGC::StepMotor_CCW, 1);
        //设定M1轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(1, 1, DriverGC::StepMotor_CW);
        //保存设定
        DriverGC::Instance()->Special_Save(1);
        //设定M1轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(1, 1, 8000, 18000);
        break;
    //初始化2号注射轴
    case 2:
        //设定M2轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(1, 2, DriverGC::StepMotor_CW, 2);
        DriverGC::Instance()->Setting_Protect_Limit(1, 2, DriverGC::StepMotor_CCW, 3);
        //设定M2轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(1, 2, DriverGC::StepMotor_CW);
        //保存设定
        DriverGC::Instance()->Special_Save(1);
        //设定M2轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(1, 2, 8000, 18000);
        break;
    //初始化3号注射轴
    case 3:
        //设定M3轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(2, 1, DriverGC::StepMotor_CW, 0);
        DriverGC::Instance()->Setting_Protect_Limit(2, 1, DriverGC::StepMotor_CCW, 1);
        //设定M1轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(2, 1, DriverGC::StepMotor_CW);
        //保存设定
        DriverGC::Instance()->Special_Save(2);
        //设定M1轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(2, 1, 8000, 18000);
        break;
    //初始化4号注射轴
    case 4:
        //设定M4轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(2, 2, DriverGC::StepMotor_CW, 2);
        DriverGC::Instance()->Setting_Protect_Limit(2, 2, DriverGC::StepMotor_CCW, 3);
        //设定M4轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(2, 2, DriverGC::StepMotor_CW);
        //保存设定
        DriverGC::Instance()->Special_Save(2);
        //设定M4轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(2, 2, 8000, 18000);
        //走M4轴的CCW极限
        //DriverGC::Instance()->AutoControl_SM_By_Limit(2, 2, DriverGC::StepMotor_CCW, 3);
        break;
    //初始化5号注射轴
    case 5:
        //设定M5轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(3, 1, DriverGC::StepMotor_CW, 0);
        DriverGC::Instance()->Setting_Protect_Limit(3, 1, DriverGC::StepMotor_CCW, 1);
        //设定M5轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(3, 1, DriverGC::StepMotor_CW);
        //保存设定
        DriverGC::Instance()->Special_Save(3);
        //设定M5轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(3, 1, 8000, 18000);
        //走M5轴的CCW极限
        //DriverGC::Instance()->AutoControl_SM_By_Limit(3, 1, DriverGC::StepMotor_CCW, 1);
        break;
    //初始化6号注射轴
    case 6:
        //设定M6轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(3, 2, DriverGC::StepMotor_CW, 2);
        DriverGC::Instance()->Setting_Protect_Limit(3, 2, DriverGC::StepMotor_CCW, 3);
        //设定M6轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(3, 2, DriverGC::StepMotor_CW);
        //保存设定
        DriverGC::Instance()->Special_Save(3);
        //设定M6轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(3, 2, 8000, 18000);
        //走M6轴的CCW极限
        //DriverGC::Instance()->AutoControl_SM_By_Limit(3, 2, DriverGC::StepMotor_CCW, 3);
        break;
    //初始化7号注射轴
    case 7:
        //设定M7轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(4, 1, DriverGC::StepMotor_CW, 0);
        DriverGC::Instance()->Setting_Protect_Limit(4, 1, DriverGC::StepMotor_CCW, 1);
        //设定M7轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(4, 1, DriverGC::StepMotor_CW);
        //保存设定
        DriverGC::Instance()->Special_Save(4);
        //设定M7轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(4, 1, 8000, 18000);
        //走M7轴的CCW极限
        //DriverGC::Instance()->AutoControl_SM_By_Limit(4, 1, DriverGC::StepMotor_CCW, 1);
        break;
    //初始化8号注射轴
    case 8:
        //设定M8轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(4, 2, DriverGC::StepMotor_CW, 2);
        DriverGC::Instance()->Setting_Protect_Limit(4, 2, DriverGC::StepMotor_CCW, 3);
        //设定M8轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(4, 2, DriverGC::StepMotor_CW);
        //保存设定
        DriverGC::Instance()->Special_Save(4);
        //设定M8轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(4, 2, 8000, 18000);
        //走M8轴的CCW极限
        //DriverGC::Instance()->AutoControl_SM_By_Limit(4, 2, DriverGC::StepMotor_CCW, 3);
        break;
    //初始化9号注射轴
    case 9:
        //设定M9轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(5, 1, DriverGC::StepMotor_CW, 0);
        DriverGC::Instance()->Setting_Protect_Limit(5, 1, DriverGC::StepMotor_CCW, 1);
        //设定M9轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(5, 1, DriverGC::StepMotor_CW);
        //保存设定
        DriverGC::Instance()->Special_Save(5);
        //设定M9轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(5, 1, 8000, 18000);
        //走M9轴的CCW极限
        //DriverGC::Instance()->AutoControl_SM_By_Limit(5, 1, DriverGC::StepMotor_CCW, 1);
        break;
    //初始化10号注射轴
    case 10:
        //设定M10轴的限位通道
        DriverGC::Instance()->Setting_Protect_Limit(5, 2, DriverGC::StepMotor_CW, 2);
        DriverGC::Instance()->Setting_Protect_Limit(5, 2, DriverGC::StepMotor_CCW, 3);
        //设定M10轴的运动方向
        DriverGC::Instance()->Setting_SM_RelDir(5, 2, DriverGC::StepMotor_CCW);
        //保存设定
        DriverGC::Instance()->Special_Save(5);
        //设定M10轴的默认运动速度
        DriverGC::Instance()->Setting_SM_Speed(5, 2, 8000, 18000);
        //走M10轴的CCW极限
        //DriverGC::Instance()->AutoControl_SM_By_Limit(5, 2, DriverGC::StepMotor_CCW, 3);
        break;  
    default:
        //错误参数
        return false;
    }
    return true;
}

// Move to a scales
// Param degree (绝对角度)
bool Motion::moveAsixToScales(quint16 degree)
{
    qint32 tmpSteps;
    //判断当前机器的位置角度是大于目标角度还是小于目标角度
    if (m_CurrentDegree > degree)
    {
        //计算移动需要的步数
        //先计算出角度差，已知1度 需要 3200 个脉冲
        tmpSteps = (m_CurrentDegree - degree) * 3200 * -1;
        //qDebug() << "Steps->" << tmpSteps;

        DriverGC::Instance()->Setting_SM_Speed(6, 1, 45000, 60000);

        DriverGC::Instance()->AutoControl_SM_By_Step(6, 1, tmpSteps);
        m_CurrentDegree = degree;
        //阻塞线程，等待电机到位, asix 0
        waitWhileFree(0);
        //通过编码器侦测是否转到角度
        if(detectEncoder())
        {
            return true;
        }
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_ROTARY_ENCODER);
        qDebug()<<"Encoder error";
        return false;
    }

    if (m_CurrentDegree < degree)
    {
        tmpSteps = (degree - m_CurrentDegree) * 3200;
        //qDebug() << "Steps->" << tmpSteps;

        DriverGC::Instance()->Setting_SM_Speed(6, 1, 45000, 60000);

        DriverGC::Instance()->AutoControl_SM_By_Step(6, 1, tmpSteps);
        m_CurrentDegree = degree;
        waitWhileFree(0);
        //通过编码器侦测是否转到角度
        if(detectEncoder())
        {
            return true;
        }
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_ROTARY_ENCODER);
        qDebug()<<"Encoder error";
        return false;
    }

    if (m_CurrentDegree == degree)
    {
        return true;
    }
    return true;
}

// Detect the asix is in the right local
// No Parmas
// return false if the encoder data is error
bool Motion::detectEncoder()
{
    DriverGC::Instance()->Inquire_Encoder(6, 2, m_EncoderData);
    if (abs(abs(m_EncoderData) - m_CurrentDegree * 1200) <= 100)
    {
        return true;
    }
    qDebug()<< "Encoder error:" << abs(abs(m_EncoderData) - m_CurrentDegree * 1200);
    return false;
}

// 注液啊！！
// Take the liquid to bottole
// Param1: motor number 1~10
// Parma2: liquid weight
// Param3: scales number 1 or 2 (1 is scale small, 2 is scale big)
bool Motion::liquidOut(quint8 motorNum, double weight, quint8 scalesNum)
{
    // 等待稳定
    sleep(2);
    // Set motion state to make the liquie function is always run
    bool liquidRunStatus = true;
    // Set motor busy status;
    bool motorBusyStatus;
    // Get the scalesNum , decide is small scale or big scale
    double oldWeight;
    if (scalesNum == 1)
    {
        oldWeight = m_SmallScalesValue;
        qDebug() << "liquidOutWeight:" << oldWeight;
    }
    else
    {
        oldWeight = m_BigScalesValue;
        qDebug() << "liquidOutWeight:" << oldWeight;
    }
    // Get which limit channel is you need
    quint8 motorChannel;
    quint8 limNum;
    if (motorNum % 2 == 1)
    {
        limNum = 1;
        motorChannel = 1;
    }
    else
    {
        limNum = 3;
        motorChannel = 2;
    }
    // Get which scale is you need
    double* currentWeight;
    if (scalesNum == 1)
    {
        currentWeight = &m_SmallScalesValue;
    }
    else
    {
        currentWeight = &m_BigScalesValue;
    }

    // Get the boadr address
    quint8 boadrAddr = (motorNum-1) / 2 + 1;
    // Loop until liquid out finish
    while (liquidRunStatus)
    {
        // Query the limit is in the lowest
        QBitArray limitData;
        DriverGC::Instance()->Inquire_Limit(boadrAddr, limitData);
        // If the motor is in the lowest
        if (limitData[limNum] == 1)
        {
            m_MoveAsixToTop(boadrAddr, motorChannel);

            // Query motor is busy;
            motorBusyStatus = true;
            while (motorBusyStatus)
            {
                DriverGC::Instance()->Inquire_Status(boadrAddr, motorChannel, motorBusyStatus);
                msleep(200);
            }
        }
        // High speed injection
        // 差大于4g
        if (oldWeight + weight - *currentWeight > 4)
        {
            //设定慢速注射
            DriverGC::Instance()->Setting_SM_Speed(boadrAddr, motorChannel, 15000, 50000);
            DriverGC::Instance()->AutoControl_SM_By_Limit(boadrAddr, motorChannel, DriverGC::StepMotor_CCW, limNum);
            //等待任务完成
            motorBusyStatus = true;
            while(motorBusyStatus)
            {
                DriverGC::Instance()->Inquire_Status(boadrAddr, motorChannel, motorBusyStatus);
                msleep(500);
            }
            continue;
        }
        // Middle speed injection
        // 差大于1g
        if (oldWeight + weight - *currentWeight > 1)
        {
            //设定慢速注射
            DriverGC::Instance()->Setting_SM_Speed(boadrAddr, motorChannel, 5000, 12000);
            DriverGC::Instance()->AutoControl_SM_By_Limit(boadrAddr, motorChannel, DriverGC::StepMotor_CCW, limNum);
            //等待任务完成
            motorBusyStatus = true;
            while(motorBusyStatus)
            {
                DriverGC::Instance()->Inquire_Status(boadrAddr, motorChannel, motorBusyStatus);
                //////
                if (oldWeight + weight - *currentWeight <= 1)
                {
                    stopDrop(motorNum);
                    motorBusyStatus = false;
                }
                //////
                msleep(500);
            }
            continue;
        }
        // Low speed injection
        // 差小于1g
        if (*currentWeight - oldWeight < weight)
        {
            //设定慢速注射
            DriverGC::Instance()->Setting_SM_Speed(boadrAddr, motorChannel, 250, 2000);
            DriverGC::Instance()->AutoControl_SM_By_Limit(boadrAddr, motorChannel, DriverGC::StepMotor_CCW, limNum);
            //查询是否在自动控制
            motorBusyStatus = true;
            while(motorBusyStatus)
            {
                DriverGC::Instance()->Inquire_Status(boadrAddr, motorChannel, motorBusyStatus);
                msleep(100);
                if (*currentWeight-oldWeight >= weight)
                {
                    liquidRunStatus = false;
                    motorBusyStatus = false;
                    stopDrop(motorNum);
                    //高速回抽
                    DriverGC::Instance()->Setting_SM_Speed(boadrAddr, motorChannel, 20000, 50000);
                    DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 5000);
                    // 发射信号 告诉界面最终的重量, 先等待数值稳定
                    sleep(2);
                    emit finishWeight(*currentWeight-oldWeight);

                }
            }
        }
        // 如果等于的话
        /*if ((oldWeight + weight - *currentWeight) < 0.1)
        {
            liquidRunStatus = false;
            motorBusyStatus = false;
            stopDrop(motorNum);
            emit finishWeight(*currentWeight-oldWeight);
        }*/
    }
    return true;
}

// Stop the motor motion
// 1 is mall scale. 2 is big scale
bool Motion::stopDrop(quint8 motorNum)
{
    // Get the boadr address
    quint8 boadrAddr = (motorNum-1) / 2 + 1;
    // Get which limit channel is you need
    quint8 motorChannel;
    if (motorNum % 2 == 1)
    {
        motorChannel = 1;
    }
    else
    {
        motorChannel = 2;
    }
    DriverGC::Instance()->Control_SM(boadrAddr, motorChannel, DriverGC::StepMotor_Stop);
    return true;
}

// 给大秤和小秤加水
// Parma1: weight
// Param2: scales Number 1 or 2
bool Motion::addWater(double weight, quint8 scalesNum)
{
    // 等待稳定
    sleep(2);

    QBitArray sta(24);
    sta.fill(false);
    double* currentWeight;
    double oldWeight;
    bool loopFlag;
    if (scalesNum == 1)
    {
        currentWeight = &m_SmallScalesValue;
        // save weight before add water
        oldWeight = m_SmallScalesValue;
        // Small scale valve
        sta.setBit(0);
    }
    else
    {
        currentWeight = &m_BigScalesValue;
        // save weight before add water
        oldWeight = m_BigScalesValue;
        // Big scale valve
        sta.setBit(1);
    }
    // //
    qDebug()<< "oldWaterWeight" << oldWeight;
    // //
    DriverGC::Instance()->Control_ValveOpen(6, sta);
    if (weight > 3)
    {
        // TODO 测试速度
        DriverGC::Instance()->Control_Motor(6, 20000);
    }
    else
    {
        DriverGC::Instance()->Control_Motor(6, 4000);
    }
    loopFlag = true;

    while (loopFlag)
    {
        if ((oldWeight + weight - *currentWeight < 3) /*&& (*currentWeight - oldWeight < weight -1)*/)
        {
            DriverGC::Instance()->Control_Motor(6, 4000);
        }
        // 到重量 关闭电机和阀
        if (*currentWeight - oldWeight >= weight)
        {
            DriverGC::Instance()->Control_ValveClose(6, sta);
            DriverGC::Instance()->Control_Motor(6, 0);
            loopFlag = false;
            // 发射信号 告诉界面最终的重量, 先等待数值稳定
            sleep(2);
            emit finishWeight(*currentWeight-oldWeight);
            return true;
        }
        msleep(200);
    }
    return true;
}

quint16 Motion::converyDegree(quint8 motorNum, quint8 scaleNum)
{
    if (scaleNum == 1)
    {
        if (motorNum == 1)
            return scales1Motor01;
        if (motorNum == 2)
            return scales1Motor02;
        if (motorNum == 3)
            return scales1Motor03;
        if (motorNum == 4)
            return scales1Motor04;
        if (motorNum == 5)
            return scales1Motor05;
        if (motorNum == 6)
            return scales1Motor06;
        if (motorNum == 7)
            return scales1Motor07;
        if (motorNum == 8)
            return scales1Motor08;
        if (motorNum == 9)
            return scales1Motor09;
        if (motorNum == 10)
            return scales1Motor10;
    }
    if (scaleNum == 2)
    {
        if (motorNum == 1)
            return scales2Motor01;
        if (motorNum == 2)
            return scales2Motor02;
        if (motorNum == 3)
            return scales2Motor03;
        if (motorNum == 4)
            return scales2Motor04;
        if (motorNum == 5)
            return scales2Motor05;
        if (motorNum == 6)
            return scales2Motor06;
        if (motorNum == 7)
            return scales2Motor07;
        if (motorNum == 8)
            return scales2Motor08;
        if (motorNum == 9)
            return scales2Motor09;
        if (motorNum == 10)
            return scales2Motor10;
    }
    return 1;
}


// 抽液体到外桶, 参数 1(小秤)to middle or 2(大秤)to middle
// 新增
bool Motion::pumpToOutSide(quint8 scaleNum)
{
    sleep(1);
    bool loopFlag = true;
    double* currentWeight;
    double originalWeight;
    double oldweight;

    if (scaleNum == 1)
    {
        // 记录抽取前的重量
        currentWeight = &m_SmallScalesValue;
        originalWeight = m_SmallScalesValue;
        oldweight = m_SmallScalesValue;
        DriverGC::Instance()->Setting_SM_Speed(6, 2, 6000, 20000);
        DriverGC::Instance()->Control_SM(6, 2, DriverGC::StepMotor_CW);
    }
    else if (scaleNum == 2)
    {
        // 记录抽取前的重量
        currentWeight = &m_BigScalesValue;
        originalWeight = m_BigScalesValue;
        oldweight = m_BigScalesValue;
        DriverGC::Instance()->Setting_SM_Speed(8, 1,30000, 80000);
        DriverGC::Instance()->Control_SM(8, 1, DriverGC::StepMotor_CW);
    }
    else
        return false;
    // 先预先抽取
    msleep(5000);
    // 等待秤的变化率小于1就停止抽液
    while (loopFlag)
    {
        if (oldweight - *currentWeight <=1)
        {
            loopFlag = false;
            if (scaleNum == 1)
            {
                DriverGC::Instance()->Control_SM(6, 2, DriverGC::StepMotor_Stop);
            }
            else if (scaleNum == 2)
            {
                DriverGC::Instance()->Control_SM(8, 1, DriverGC::StepMotor_Stop);
            }
        }
        oldweight = *currentWeight;
        // 等待500ms抽取时间
        msleep(2000);
    }
    // 给界面提供数据
    sleep(1);
    emit finishWeight(oldweight-*currentWeight);
    return true;
}

bool Motion::pumpToOutSideManual(quint8 scaleNum, bool flag)
{
    switch (scaleNum) {
    case 1:
        if (flag)
        {
            DriverGC::Instance()->Setting_SM_Speed(6, 2, 6000, 20000);
            DriverGC::Instance()->Control_SM(6, 2, DriverGC::StepMotor_CW);
            return true;
        }
        else
        {
            DriverGC::Instance()->Control_SM(6, 2, DriverGC::StepMotor_Stop);
            return true;
        }
    case 2:
        if (flag)
        {
            DriverGC::Instance()->Setting_SM_Speed(8, 1,30000, 80000);
            DriverGC::Instance()->Control_SM(8, 1, DriverGC::StepMotor_CW);
            return true;
        }
        else
        {
            DriverGC::Instance()->Control_SM(8, 1, DriverGC::StepMotor_Stop);
            return true;
        }
    default:
        return false;
    }
}

void Motion::getUserTankTop(bool *flag)
{
    // 用户浆料槽top 液位 board6， channel 2
    QBitArray userTankLimit;
    DriverGC::Instance()->Inquire_Limit(6, userTankLimit);
    if (userTankLimit.at(2))
    {
        *flag = true;
    }
    else
    {
        *flag = false;
    }
}

void Motion::mixMiddleTank(bool flag)
{
    if (flag)
    {
        DriverGC::Instance()->Setting_SM_Speed(7, 1, 40000, 12000);
        if (m_MixTurn)
        {
            DriverGC::Instance()->Control_SM(7, 1, DriverGC::StepMotor_CW);
            m_MixTurn = false;
        }
        else
        {
            DriverGC::Instance()->Control_SM(7, 1, DriverGC::StepMotor_CCW);
            m_MixTurn = true;
        }
    }
    else
    {
        DriverGC::Instance()->Control_SM(7, 1, DriverGC::StepMotor_Stop);
    }
}


// 小罐子加注原液
// 已经遗弃
bool Motion::topUpTank()
{
    bool loopFlag;
    QBitArray valueArray(24);
    valueArray.fill(false);
    QBitArray tankLimit;

    moveAsixToScales(scales1Motor09);
    DriverGC::Instance()->Inquire_Limit(8, tankLimit);
    if(!tankLimit.at(0))
    {
        loopFlag = true;
        valueArray[20] = true;
        DriverGC::Instance()->Control_ValveOpen(7, valueArray);
        while (loopFlag)
        {
            DriverGC::Instance()->Inquire_Limit(8, tankLimit);
            if (tankLimit.at(0))
            {
                DriverGC::Instance()->Control_ValveClose(7, valueArray);
                valueArray.fill(false);
                loopFlag = false;
            }
            msleep(500);
        }
    }

    if(!tankLimit.at(1))
    {
        loopFlag = true;
        valueArray[19] = true;
        DriverGC::Instance()->Control_ValveOpen(7, valueArray);
        while (loopFlag)
        {
            DriverGC::Instance()->Inquire_Limit(8, tankLimit);
            if (tankLimit.at(1))
            {
                DriverGC::Instance()->Control_ValveClose(7, valueArray);
                valueArray.fill(false);
                loopFlag = false;
            }
            msleep(500);
        }
    }

    if(!tankLimit.at(2))
    {
        loopFlag = true;
        valueArray[17] = true;
        DriverGC::Instance()->Control_ValveOpen(7, valueArray);
        while (loopFlag)
        {
            DriverGC::Instance()->Inquire_Limit(8, tankLimit);
            if (tankLimit.at(2))
            {
                DriverGC::Instance()->Control_ValveClose(7, valueArray);
                valueArray.fill(false);
                loopFlag = false;
            }
            msleep(500);
        }
    }

    if(!tankLimit.at(3))
    {
        loopFlag = true;
        valueArray[18] = true;
        DriverGC::Instance()->Control_ValveOpen(7, valueArray);
        while (loopFlag)
        {
            DriverGC::Instance()->Inquire_Limit(8, tankLimit);
            if (tankLimit.at(3))
            {
                DriverGC::Instance()->Control_ValveClose(7, valueArray);
                valueArray.fill(false);
                loopFlag = false;
            }
            msleep(500);
        }
    }
    return true;
}

// 获取中间罐桶的液体升数
bool Motion::getMiddleTankLevel(double *microLiter)
{
    qint16 adcValue = 0;
    quint32 filtedAdcValue = 0;
    DriverGC::Instance()->Inquire_ExADC(7, 0, adcValue);

    //filtedAdcValue = uWindowFilter.Get(adcValue);
    for (int i=0; i<10; i++)
    {
        DriverGC::Instance()->Inquire_ExADC(7, 0, adcValue);
        filtedAdcValue += adcValue;
    }
    filtedAdcValue /= 10;
    // calc real lite
    if (filtedAdcValue <0)
        filtedAdcValue = 0;
    *microLiter = 1.426 * filtedAdcValue - 2890;
    //qDebug() << "TankADC:" << filtedAdcValue;
    emit broadCaseMiddleTankLevel(*microLiter);
    return true;
}

// 从中桶到外部液槽
// FIXME 等待测试
bool Motion::pumpMiddleTankToUserTank()
{
    bool loopFlag = true;
    QBitArray tankLimit;
    double currentWeight;

    // 先获取原始的液体量
    double lastWeight;
    getMiddleTankLevel(&lastWeight);
    //开pump
    DriverGC::Instance()->Setting_SM_Speed(7, 2, 30000, 40000);
    DriverGC::Instance()->Control_SM(7, 2, DriverGC::StepMotor_CCW);
    // 检测外部液位是否触发
    // 用户浆料槽top 液位 board6， channel 2
    while (loopFlag) {
        sleep(5);
        getMiddleTankLevel(&currentWeight);
        DriverGC::Instance()->Inquire_Limit(6, tankLimit);
        if ((lastWeight-currentWeight >0) && (lastWeight-currentWeight < 40))
        {
            qDebug() << "shit it ";
        }
        if (tankLimit.at(2) || ((lastWeight-currentWeight >0) && (lastWeight-currentWeight < 200)))
        {
            DriverGC::Instance()->Control_SM(7, 2, DriverGC::StepMotor_Stop);
            return true;
        }
        lastWeight = currentWeight;
    }
    return true;
}

void Motion::controlMiddleTankToOutside(bool value)
{
    if (value)
    {
        DriverGC::Instance()->Setting_SM_Speed(7, 2, 30000, 40000);
        DriverGC::Instance()->Control_SM(7, 2, DriverGC::StepMotor_CCW);
    }
    else
    {
        DriverGC::Instance()->Control_SM(7, 2, DriverGC::StepMotor_Stop);
    }
}

void Motion::controlMiddleTankAddWater(bool value)
{
    QBitArray valueArray(24);
    valueArray.fill(false);
    // 水泵 22 port
    valueArray[21] = true;
    if (value)
    {
        DriverGC::Instance()->Control_ValveOpen(7, valueArray);
    }
    else
    {
        DriverGC::Instance()->Control_ValveClose(7, valueArray);
    }
}

bool Motion::addWaterMiddleTank(double liter)
{
    QBitArray valueArray(24);
    valueArray.fill(false);
    // 水泵 22 port
    valueArray[21] = true;
    bool loopFlag = true;
    double currentLiter;
    double targetLiter;
    getMiddleTankLevel(&currentLiter);

    targetLiter = currentLiter + liter;
    // 防止超过30L
    if (targetLiter >= 30000)
    {
        return false;
    }

    // port num 22
    DriverGC::Instance()->Control_ValveOpen(7, valueArray);
    while (loopFlag)
    {
        getMiddleTankLevel(&currentLiter);
        if (currentLiter >= targetLiter)
        {
            DriverGC::Instance()->Control_ValveClose(7, valueArray);
            loopFlag = false;
            break;
        }
        msleep(1000);
    }
    return true;
}

// 从蠕动泵加液
bool Motion::pumpPaint(quint8 pumpNum, double weight)
{
    // 等待稳定
    sleep(1);
    QBitArray valueArray(24);
    valueArray.fill(false);
    double* currentWeight;
    currentWeight = &m_BigScalesValue;
    double oldWeight;
    oldWeight = m_BigScalesValue;

    bool loopFlag = true;

    switch (pumpNum) {
    case 1:
        valueArray[17] = true;
        DriverGC::Instance()->Control_ValveOpen(7, valueArray);
        break;
    case 2:
        valueArray[18] = true;
        DriverGC::Instance()->Control_ValveOpen(7, valueArray);
        break;
    case 3:
        valueArray[20] = true;
        DriverGC::Instance()->Control_ValveOpen(7, valueArray);
        break;
    case 4:
        valueArray[19] = true;
        DriverGC::Instance()->Control_ValveOpen(7, valueArray);
        break;
    default:
        break;
    }
    while (loopFlag)
    {
        msleep(300);
        if (*currentWeight-oldWeight >= weight)
        {
            DriverGC::Instance()->Control_ValveClose(7, valueArray);
            loopFlag = false;
            sleep(1);
            emit finishWeight(*currentWeight-oldWeight);
        }
    }
    return true;
}

