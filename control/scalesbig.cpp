#include "scalesbig.h"

ScalesBig::ScalesBig()
{

}

void ScalesBig::serialStrConver2Data()
{
    quint16 head = 0, tail = 0;
    bool he = false, ta = false;
    bool hasData;

    for(quint16 i=0; i<p_allData.length(); i++)
    {
        // 判断是否会超过界限
        if (i+1 < p_allData.length())
        {
            if ((p_allData.at(i) == 'S' && p_allData.at(i+1) == 'T') || (p_allData.at(i) == 'U' && p_allData.at(i+1) == 'T'))
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
            QString tmp = p_allData.mid(head, 19);
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

void ScalesBig::splitData(QString msg)
{
    //获取称量状态
    p_scalesStatus = msg.mid(0, 2);
    //获取称量数值
    if(msg.mid(6, 1) == '-')
    {
        p_scalesValue = msg.mid(7, 8).toDouble() * -1;
    }
    else if (msg.mid(6, 1) == '+')
    {
        p_scalesValue = msg.mid(7, 8).toDouble();
    }
    //获取称量单位
    p_scalesUnit = msg.mid(15, 2).simplified();

    emit receiveDataPush(p_scalesValue, p_scalesUnit);
}
