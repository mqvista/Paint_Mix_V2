#include "scalesbig.h"

ScalesBig::ScalesBig()
{

}

void ScalesBig::serialStrConver2Data(QString msg)
{
    //获取称量状态
    m_scalesStatus = msg.mid(0, 2);
    //获取称量数值
    if(msg.mid(6, 1) == '-')
    {
        m_scalesValue = msg.mid(7, 8).toDouble() * -1;
    }
    else if (msg.mid(6, 1) == '+')
    {
        m_scalesValue = msg.mid(7, 8).toDouble();
    }
    //获取称量单位
    m_scalesUnit = msg.mid(15, 2).simplified();
}
