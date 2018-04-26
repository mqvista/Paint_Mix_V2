#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Convert.h"
#include "Protocol.h"
#include "drivergc_global.h"
#include <QBitArray>
#include <QByteArray>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QThread>

class DRIVERGCSHARED_EXPORT Functions : public Protocol {
    Q_OBJECT
public:
    enum StepMotor : quint8 {
        StepMotor_CW = 0x00,
        StepMotor_CCW = 0x01,
        StepMotor_Stop = 0xff
    };

    bool Inquire_Limit(const quint16& salveAdd, QBitArray& limitData);
    bool Inquire_ExLimit(const quint16& salveAdd, QBitArray& limitData);
    bool Inquire_Valve(const quint16& salveAdd, QBitArray& valveData);
    bool Inquire_Encoder(const quint16& salveAdd, const quint8& ch, qint32& encoderData);
    bool Inquire_ADC(const quint16& salveAdd, const quint8& ch, qint16& adcData);
    bool Inquire_ExADC(const quint16& salveAdd, const quint8& ch, qint16& adcData);
    bool Inquire_Tigger(const quint16& salveAdd, quint8& tiggerData);
    bool Inquire_Motor(const quint16& salveAdd, qint16& speed);
    bool Inquire_Special(const quint16& salveAdd);
    bool Inquire_DAC(const quint16& salveAdd, const quint8& ch, quint16& dacData);
    bool Inquire_SpecialADCWithTime(const quint16& salveAdd);
    bool Inquire_SpecialADCTrigger(const quint16& salveAdd);
    bool Inquire_SpecialStatus(const quint16& salveAdd);
    bool Inquire_SpecialDoubleADCTrigger(const quint16& salveAdd);
    bool Inquire_Status(const quint16& salveAdd, const quint8& ch, bool& status);

    bool Control_Valve(const quint16& salveAdd, const QBitArray& status);
    bool Control_Motor(const quint16& salveAdd, const qint16& speed);
    bool Control_SM(const quint16& salveAdd, const quint8& ch, const StepMotor& dir);
    bool Control_DAC(const quint16& salveAdd, const quint8& ch, const quint16& data);
    bool Control_ValveOpen(const quint16& salveAdd, const QBitArray& valveData);
    bool Control_ValveClose(const quint16& salveAdd, const QBitArray& valveData);

    bool AutoControl_SM_By_Step(const quint16& salveAdd, const quint8& ch, const qint32& step);
    bool AutoControl_SM_By_Limit(const quint16& salveAdd, const quint8& ch,
        const StepMotor& dir, const quint8& limitNo);
    bool AutoControl_SM_By_Step_With_ADC_And_Encoder(const quint16& salveAdd);
    bool AutoControl_SpecialADCWithTime(const quint16& salveAdd);
    bool AutoControl_SpecialADCWithTrigger(const quint16& salveAdd);
    bool AutoControl_SpecialMotorPosition(const quint16& salveAdd);
    bool AutoControl_SpecialADCDoubleWithTrigger(const quint16& salveAdd);

    bool Setting_SM_Speed(const quint16& salveAdd, const quint8& ch,
        const quint16& speed, const quint32& accel);
    bool Setting_Valve_Default(const quint16& salveAdd, const QBitArray& valveData);
    bool Setting_Encoder_Zero(const quint16& salveAdd, const quint8& ch);
    bool Setting_Protect_Limit(const quint16& salveAdd, const quint8& ch,
        const StepMotor& dir, const quint8& limitNo);
    bool Setting_PIDParam(const quint16& salveAdd);
    bool Setting_PIDInput(const quint16& salveAdd);
    bool Setting_PIDEnable(const quint16& salveAdd);
    bool Setting_SM_RelDir(const quint16& salveAdd, const quint8& ch, const StepMotor dir);
    bool Setting_USART(const quint16& salveAdd, const quint8& baundNo);
    bool Setting_Address(const quint16& salveAdd, const quint16& salveAddSet);

    bool Special_Reset(const quint16& salveAdd);
    bool Special_Stop(const quint16& salveAdd);
    bool Special_Continue(const quint16& salveAdd);
    bool Special_Cacel(const quint16& salveAdd);
    bool Special_Save(const quint16& salveAdd);
    bool Special_Init(const quint16& salveAdd);

protected:
    Functions();
};

#endif // FUNCTIONS_H
