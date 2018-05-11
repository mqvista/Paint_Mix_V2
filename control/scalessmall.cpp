#include "scalessmall.h"

ScalesSmall::ScalesSmall()
{

}

void ScalesSmall::serialStrConver2Data()
{
    quint16 head = 0, tail = 0;
    bool he = false, ta = false;
    bool hasData;

    for(quint16 i=0; i<p_allData.length(); i++)
    {
        // 判断是否会超过界限
        if (i+1 < p_allData.length())
        {
            if (p_allData.at(i) == 'W' && p_allData.at(i+1) == 'T')
            {
                head = i;
                he = true;
            }
        }
        if (he && (p_allData.at(i) == '\n'))
        {
            tail = i;
            ta = true;
        }
        if (he && ta)
        {
            QString tmp = p_allData.mid(head, 18);
            splitData(tmp);
            hasData = true;
            he = false;
            ta = false;
        }
    }

    if (hasData)
    {
        p_allData.remove(0, tail+1);
    }

}

void ScalesSmall::splitData(QString msg)
{
    //获取称量状态
    p_scalesStatus = msg.mid(0, 4);
    //获取称量数值
    if(msg.mid(4, 1) == '-')
    {
        p_scalesValue = msg.mid(5, 7).toDouble() * -1;
    }
    else if (msg.mid(4, 1) == '+')
    {
        p_scalesValue = msg.mid(5, 7).toDouble();
    }
    //获取称量单位
    p_scalesUnit = msg.mid(13, 3).simplified();

    emit receiveDataPush(p_scalesValue, p_scalesUnit);
}
