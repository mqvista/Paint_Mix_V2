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
    // Get Serial Error
    connect(DriverGC::Instance(), &DriverGC::ErrorOut, this, &Motion::serial485Error);
    // Get Debug Data
    connect(DriverGC::Instance(), &DriverGC::DebugOut, this, &Motion::driverGCDebugInfo);
    return true;
}

// Close DriverGc Serial Port
// No Params
bool Motion::closeSerial485()
{
    DriverGC::Instance()->Close();
    disconnect(DriverGC::Instance(), &DriverGC::ErrorOut, this, &Motion::serial485Error);
    disconnect(DriverGC::Instance(), &DriverGC::DebugOut, this, &Motion::driverGCDebugInfo);
    return true;
}

// Init all board or it will not work
// No Params
bool Motion::initBoard()
{
    for(quint8 i=1; i<=8; i++)
    {
        if (!DriverGC::Instance()->Special_Reset(i))
        {
            return false;
        }
        if (!DriverGC::Instance()->Special_Init(i))
        {
            return false;
        }
        //DriverGC::Instance()->Special_Reset(i);
        //DriverGC::Instance()->Special_Init(i);
    }
    return true;
}

// Get Serial 485 error message from DriverGC signal
// Param1: Error message main
// Param2: Error message sub
void Motion::serial485Error(QString msg1, QString msg2)
{
    qDebug() << msg1;
    qDebug() << msg2;
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
    //qDebug()<< "Small_Scales:" << m_SmallScalesValue;
}

// Get the big scales senser data (is a slot)
// Parma1: scales value
void Motion::getBigScalesValue(double value)
{
    m_BigScalesValue = value;
    //qDebug()<< "Big_Scales:" << m_BigScalesValue;
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
        //默认初始化后停留在10号轴
        //m_CurrentMotor = 10;
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
        DriverGC::Instance()->Setting_SM_Speed(1, 1, 6000, 18000);
        //走M1轴的CCW极限
        DriverGC::Instance()->AutoControl_SM_By_Limit(1, 1, DriverGC::StepMotor_CCW, 1);
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
        DriverGC::Instance()->Setting_SM_Speed(1, 2, 6000, 18000);
        //走M2轴的CCW极限
        DriverGC::Instance()->AutoControl_SM_By_Limit(1, 2, DriverGC::StepMotor_CCW, 3);
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
        DriverGC::Instance()->Setting_SM_Speed(2, 1, 6000, 18000);
        //走M1轴的CCW极限
        DriverGC::Instance()->AutoControl_SM_By_Limit(2, 1, DriverGC::StepMotor_CCW, 1);
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
        DriverGC::Instance()->Setting_SM_Speed(2, 2, 6000, 18000);
        //走M4轴的CCW极限
        DriverGC::Instance()->AutoControl_SM_By_Limit(2, 2, DriverGC::StepMotor_CCW, 3);
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
        DriverGC::Instance()->Setting_SM_Speed(3, 1, 6000, 18000);
        //走M5轴的CCW极限
        DriverGC::Instance()->AutoControl_SM_By_Limit(3, 1, DriverGC::StepMotor_CCW, 1);
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
        DriverGC::Instance()->Setting_SM_Speed(3, 2, 6000, 18000);
        //走M6轴的CCW极限
        DriverGC::Instance()->AutoControl_SM_By_Limit(3, 2, DriverGC::StepMotor_CCW, 3);
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
        DriverGC::Instance()->Setting_SM_Speed(4, 1, 6000, 18000);
        //走M7轴的CCW极限
        DriverGC::Instance()->AutoControl_SM_By_Limit(4, 1, DriverGC::StepMotor_CCW, 1);
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
        DriverGC::Instance()->Setting_SM_Speed(4, 2, 6000, 18000);
        //走M8轴的CCW极限
        DriverGC::Instance()->AutoControl_SM_By_Limit(4, 2, DriverGC::StepMotor_CCW, 3);
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
        DriverGC::Instance()->Setting_SM_Speed(5, 1, 6000, 18000);
        //走M9轴的CCW极限
        DriverGC::Instance()->AutoControl_SM_By_Limit(5, 1, DriverGC::StepMotor_CCW, 1);
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
        DriverGC::Instance()->AutoControl_SM_By_Limit(5, 2, DriverGC::StepMotor_CCW, 3);
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
    // stop current job
    if (m_stopFlag)
    {
        m_stopFlag = false;
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
    if (abs(abs(m_EncoderData) - m_CurrentDegree * 1200) <= 10)
    {
        return true;
    }
    qDebug()<< "Encoder error:" << abs(abs(m_EncoderData) - m_CurrentDegree * 1200);
    return false;
}

// Take the liquid to bottole
// Param1: motor number 1~10
// Parma2: liquid weight
// Param3: scales number 1 or 2 (1 is scale small, 2 is scale big)
bool Motion::liquidOut(quint8 motorNum, quint32 weight, quint8 scalesNum)
{
    // Set motion state to make the liquie function is always run
    bool liquidRunStatus = true;
    // Set motor busy status;
    bool motorBusyStatus;
    // Get the scalesNum , decide is small scale or big scale
    double oldWeight;
    if (scalesNum == 1)
    {
        oldWeight = m_SmallScalesValue;
    }
    else
    {
        oldWeight = m_BigScalesValue;
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
            // Fast rise motor asix
            DriverGC::Instance()->Setting_SM_Speed(boadrAddr, motorChannel, 8000, 18000);
            DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 10000);
            // Query motor is busy;
            motorBusyStatus = true;
            while (motorBusyStatus)
            {
                // stop current job
                if (m_stopFlag)
                {
                    stopDrop(motorNum);
                    m_stopFlag = false;
                    return false;
                }

                DriverGC::Instance()->Inquire_Status(boadrAddr, motorChannel, motorBusyStatus);
                msleep(100);
            }
        }
        // High speed injection
        // 差大于3g
        if (oldWeight + weight - *currentWeight > 3)
        {
            //设定慢速注射
            DriverGC::Instance()->Setting_SM_Speed(boadrAddr, motorChannel, 4000, 12000);
            DriverGC::Instance()->AutoControl_SM_By_Limit(boadrAddr, motorChannel, DriverGC::StepMotor_CCW, limNum);
            //等待任务完成
            motorBusyStatus = true;
            while(motorBusyStatus)
            {
                // stop current job
                if (m_stopFlag)
                {
                    stopDrop(motorNum);
                    m_stopFlag = false;
                    return false;
                }

                DriverGC::Instance()->Inquire_Status(boadrAddr, motorChannel, motorBusyStatus);
                msleep(50);
            }
            continue;
        }
        // Low speed injection
        // 差小于3g
        if (*currentWeight - oldWeight < weight)
        {
            //设定慢速注射
            DriverGC::Instance()->Setting_SM_Speed(boadrAddr, motorChannel, 200, 1200);
            DriverGC::Instance()->AutoControl_SM_By_Limit(boadrAddr, motorChannel, DriverGC::StepMotor_CCW, limNum);
            //查询是否在自动控制
            motorBusyStatus = true;
            while(motorBusyStatus)
            {
                // stop current job
                if (m_stopFlag)
                {
                    stopDrop(motorNum);
                    m_stopFlag = false;
                    return false;
                }

                DriverGC::Instance()->Inquire_Status(boadrAddr, motorChannel, motorBusyStatus);
                msleep(50);
                if (*currentWeight-oldWeight >= weight)
                {
                    liquidRunStatus = false;
                    motorBusyStatus = false;
                    stopDrop(motorNum);
                    // 发射信号 告诉界面最终的重量, 先等待数值稳定
                    msleep(500);
                    emit finishWeight(*currentWeight-oldWeight);
                    //高速回抽
                    DriverGC::Instance()->Setting_SM_Speed(boadrAddr, motorChannel, 8000, 18000);
                    DriverGC::Instance()->AutoControl_SM_By_Step(boadrAddr, motorChannel, 2000);
                }
            }
        }
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
bool Motion::addWater(quint32 weight, quint8 scalesNum)
{
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
    DriverGC::Instance()->Control_ValveOpen(6, sta);
    if (weight > 3)
    {
        DriverGC::Instance()->Control_Motor(6, 10000);
    }
    else
    {
        DriverGC::Instance()->Control_Motor(6, 3500);
    }
    loopFlag = true;

    while (loopFlag)
    {
        // stop current job
        if (m_stopFlag)
        {
            DriverGC::Instance()->Control_ValveClose(6, sta);
            DriverGC::Instance()->Control_Motor(6, 0);
            m_stopFlag = false;
            return false;
        }

        if((oldWeight + weight - *currentWeight < 3) && (*currentWeight - oldWeight < weight -1))
        {
            DriverGC::Instance()->Control_Motor(6, 3500);
        }
        // 到重量 关闭电机和阀
        if (*currentWeight - oldWeight >= weight)
        {
            DriverGC::Instance()->Control_ValveClose(6, sta);
            DriverGC::Instance()->Control_Motor(6, 0);
            loopFlag = false;
            // 发射信号 告诉界面最终的重量, 先等待数值稳定
            msleep(500);
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
        DriverGC::Instance()->Setting_SM_Speed(6, 2, 4000, 12000);
        DriverGC::Instance()->Control_SM(6, 2, DriverGC::StepMotor_CW);
    }
    else if (scaleNum == 2)
    {
        // 记录抽取前的重量
        currentWeight = &m_BigScalesValue;
        originalWeight = m_BigScalesValue;
        oldweight = m_BigScalesValue;
        DriverGC::Instance()->Setting_SM_Speed(8, 1, 4000, 12000);
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
        msleep(500);
    }
    // 给界面提供数据
    emit pumpToOutsideWeight(originalWeight - *currentWeight);
    return true;
}


// 小罐子加注原液
// 新需求
bool Motion::topUpTank()
{
    bool loopFlag;
    QBitArray valueArray(24);
    valueArray.fill(false);
    QBitArray tankLimit;

    moveAsixToScales(scales1Motor09);
    //
    DriverGC::Instance()->Inquire_Limit(8, tankLimit);
    if(!tankLimit.at(0))
    {
        loopFlag = true;
        valueArray[18] = true;
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
        valueArray[20] = true;
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
        valueArray[19] = true;
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
        valueArray[17] = true;
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
    qint16 adcValue;
    DriverGC::Instance()->Inquire_ExADC(7, 0, adcValue);
    if (adcValue <0)
        adcValue = 0;
    *microLiter = 1.582 * adcValue - 1223;
    return true;
}

// 从中桶到外部液槽
// FIXME 等待实现 参数未定，外部传感器位置未定
bool Motion::pumpMiddleTankToUserTank(bool OnOff)
{
    DriverGC::Instance()->Setting_SM_Speed(7, 2, 40000, 40000);
    if (OnOff)
    {
        DriverGC::Instance()->Control_SM(7, 2, DriverGC::StepMotor_CCW);
    }
    else
    {
        DriverGC::Instance()->Control_SM(7, 2, DriverGC::StepMotor_Stop);
    }
    return true;
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
    if (targetLiter >= 30)
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
        msleep(500);
    }
    return true;
}

