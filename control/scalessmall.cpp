#include "scalessmall.h"

ScalesSmall::ScalesSmall()
{

}

void ScalesSmall::serialStrConver2Data(QString msg)
{
    //获取称量状态
    m_scalesStatus = msg.mid(0, 4);
    //获取称量数值
    if(msg.mid(4, 1) == '-')
    {
        m_scalesValue = msg.mid(5, 7).toDouble() * -1;
    }
    else if (msg.mid(4, 1) == '+')
    {
        m_scalesValue = msg.mid(5, 7).toDouble();
    }
    //获取称量单位
    m_scalesUnit = msg.mid(13, 3).simplified();
}
