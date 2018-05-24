#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "Communication.h"
#include "drivergc_global.h"

#include "WaitForSignalHelper.h"
#include <QByteArray>
#include <QDataStream>
#include <QList>
#include <QMetaEnum>
#include <QMutex>
#include <QThread>

class DRIVERGCSHARED_EXPORT Protocol : public Communication {
    Q_OBJECT
public:
    enum Command : quint8 {
        Command_Mask = 0xe0,

        Command_Inquire_Mask = 0x00,
        Command_Inquire_Limit = 0x01,
        Command_Inquire_ExLimit = 0x02,
        Command_Inquire_Valve = 0x03,
        Command_Inquire_Encoder = 0x04,
        Command_Inquire_ADC = 0x05,
        Command_Inquire_ExADC = 0x06,
        Command_Inquire_Tigger = 0x07,
        Command_Inquire_Motor = 0x08,
        Command_Inquire_Special = 0x09,
        Command_Inquire_DAC = 0x0a,
        Command_Inquire_SpecialADCWithTime = 0x0b,
        Command_Inquire_SpecialADCTrigger = 0x0c,
        Command_Inquire_SpecialStatus = 0x0d,
        Command_Inquire_SpecialDoubleADCTrigger = 0x0e,
        Command_Inquire_FlowValue = 0x12,
        Command_Inquire_Status = 0x1f,

        Command_Control_Mask = 0x20,
        Command_Control_Valve = 0x21,
        Command_Control_Motor = 0x22,
        Command_Control_SM = 0x23,
        Command_Control_DAC = 0x24,
        Command_Control_ValveOpen = 0x25,
        Command_Control_ValveClose = 0x26,

        Command_AutoControl_Mask = 0x40,
        Command_AutoControl_SM_By_Step = 0x41,
        Command_AutoControl_SM_By_Limit = 0x42,
        Command_AutoControl_SM_By_Step_With_ADC_And_Encoder = 0x43,
        Command_AutoControl_SpecialADCWithTime = 0x44,
        Command_AutoControl_SpecialADCWithTrigger = 0x45,
        Command_AutoControl_SpecialMotorPosition = 0x46,
        Command_AutoControl_SpecialADCDoubleWithTrigger = 0x47,

        Command_Setting_Mask = 0xa0,
        Command_Setting_SM_Speed = 0xa1,
        Command_Setting_Valve_Default = 0xa2,
        Command_Setting_Encoder_Zero = 0xa3,
        Command_Setting_Protect_Limit = 0xa4,
        Command_Setting_PIDParam = 0xa5,
        Command_Setting_PIDInput = 0xa6,
        Command_Setting_PIDEnable = 0xa7,
        Command_Setting_SM_RelDir = 0xa8,
        Command_Setting_ClearFlowValue = 0xab,
        Command_Setting_USART = 0xbe,
        Command_Setting_Address = 0xbf,

        Command_Special_Mask = 0xc0,
        Command_Special_Reset = 0xc1,
        Command_Special_Stop = 0xc2,
        Command_Special_Continue = 0xc3,
        Command_Special_Cacel = 0xc4,
        Command_Special_Save = 0xc5,
        Command_Special_Init = 0xc6,

        Command_Post_Mask = 0xe0,
        Command_Post_Get = 0xe1,
        Command_Post_Complete = 0xe2,
        Command_Post_Error = 0xe3,

        Command_None = 0xff
    };

    Q_ENUM(Command)

    Protocol();
    bool Analysis(quint16 salveAdd, Protocol::Command cmd, QByteArray& dataOut);
    bool Send(const quint16& salveAdd, const Command& cmd,
        const QByteArray& dataSend, QByteArray& dataReceive);
    void GoToThread(QThread* thread);
signals:
    void ReceiveDone();

protected:
    void ReceiveEvent();
    QByteArray _RcvBuf;
    QList<QByteArray> _RcvFrameList;

private:
    QMutex mutex;
    QMetaEnum meCommand;
    WaitForSignalHelper helper;
};

#endif // PROTOCOL_H
