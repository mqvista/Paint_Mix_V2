#include "filereadwrite.h"

FileReadWrite::FileReadWrite(QObject *parent) : QObject(parent)
{

}

//获取方案的配置列表
bool FileReadWrite::readProfileLists(QList<QString> *list)
{
    QFile *file = new QFile(profilePath);
    QDomDocument doc;
    if (!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "File can not access!!";
        return false;
    }
    else if (!doc.setContent(file))
    {
        qDebug() << "set dom content failed";
        file->close();
        return false;
    }
    file->close();
    //获取根节点
    QDomElement root = doc.documentElement();
    //判断头格式是否正确
    if (root.nodeName() == "PaintMix_Profile")
    {
        QDomNode node = root.firstChild();
        while(!node.isNull())
        {
            QDomElement element = node.toElement();
            list->append(element.attribute("Name", ""));
            node = node.nextSibling();
        }
        return true;
    }
    else
    {
        return false;
    }
}

//获取指定方案的内容
//Parame 1、查询的方案名称
//Parame 2、QMAP<编号，QMAP<内容， 数量>> QMAP, Pointer
//Parame 3、unit 的长度, Pointer
bool FileReadWrite::readProfileDetail(QString name, QMap<quint16, QMap<QString,QString> > *detail, qint16 *detailLength)
{
    QFile *file = new QFile(profilePath);
    QDomDocument doc;
    if (!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "File can not access!!";
        return false;
    }
    else if (!doc.setContent(file))
    {
        qDebug() << "set dom content failed";
        file->close();
        return false;
    }
    file->close();
    QDomElement root = doc.documentElement();

    //判断头格式是否正确
    if (root.nodeName() == "PaintMix_Profile")
    {
        QDomNode node = root.firstChild();
        while (!node.isNull())
        {
            //转换为element 并判断是否为需要的element
            QDomElement element = node.toElement();

            if (element.attribute("Name", "") == name)
            {
                //生成Unit 的 nodeList
                QDomNodeList nodeList = element.childNodes();
                //遍历Unit, 并将 unit 数量提交上
                *detailLength = nodeList.length();
                for (qint16 i=0; i<nodeList.length(); i++)
                {
                    QDomNode unitNode = nodeList.at(i);
                    //获取顺序ID编号
                    quint16 id = unitNode.toElement().attribute("ID", "").toUInt();
                    //生成nodelist,遍历Unit的内容, 生成qmap 临时变量保存数据
                    QMap<QString, QString> unitDetail;
                    QDomNodeList unitList = unitNode.toElement().childNodes();
                    for (int j=0; j<unitList.length(); j++)
                    {
                        QString name = unitList.at(j).toElement().tagName();
                        QString value = unitList.at(j).toElement().text();
                        //qDebug() << unitList.at(j).toElement().tagName() << unitList.at(j).toElement().text();
                        unitDetail.insert(name, value);
                    }
                    //插入一个unit的详细配料数据
                    detail->insert(id, unitDetail);
                }
                return true;
            }
            node = node.nextSibling();
        }
        return false;
    }
    return false;
}

//删除指定的配置
//Parame 1、名称
bool FileReadWrite::deleteProfileDetail(QString name)
{
    QFile *file = new QFile(profilePath);
    QDomDocument doc;
    if (!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "File can not access!!";
        return false;
    }
    else if (!doc.setContent(file))
    {
        qDebug() << "set dom content failed";
        file->close();
        return false;
    }
    file->close();
    QDomElement root = doc.documentElement();
    //判断 头格式是否正确
    if (root.nodeName() == "PaintMix_Profile")
    {
        QDomNodeList nodeList = root.childNodes();
        for (quint16 i=0; i<nodeList.length(); i++)
        {
            if (nodeList.at(i).toElement().attribute("Name","") == name)
            {
                //删除查找到的对象
                root.removeChild(nodeList.at(i));
                //保存文件
                if (!file->open(QFile::WriteOnly|QFile::Truncate))
                {
                    qDebug() << "File can not access!!";
                    return false;
                }
                //保存文件，设置4个空格为缩进
                QTextStream out (file);
                doc.save(out, 4);
                file->close();
                return true;
            }
        }
    }
    return false;
}

//插入新的方案内容, name不能有重复
//Parame 1、新增的方案名称
//Parame 2、QMAP<编号，QMAP<内容， 数量>> QMAP
//Parame 3、unit 的长度, 最小为1
bool FileReadWrite::insertProfileDetail(QString name, QMap<quint16, QMap<QString, QString> > detail, qint16 detailLength)
{
    //判断name是否重复
    QList<QString> names;
    readProfileLists(&names);
    if (names.contains(name))
    {
        return false;
    }

    QFile *file = new QFile(profilePath);
    QDomDocument doc;
    if (!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "File can not access!!";
        return false;
    }
    else if (!doc.setContent(file))
    {
        qDebug() << "set dom content failed";
        file->close();
        return false;
    }
    file->close();

    QDomElement root = doc.documentElement();
    //创建formula元素，并设定name属性
    QDomElement formula = doc.createElement("Formula");
    formula.setAttribute("Name", name);
    for (quint16 i=1; i<detailLength + 1; i++)
    {
        //新建一个Unit
        QDomElement unit = doc.createElement("Unit");
        //设定Unit的顺序ID
        unit.setAttribute("ID", i);
        //迭代出QMP内的东西
        QMapIterator<QString, QString> mapInter(detail[i]);
        while(mapInter.hasNext())
        {
            mapInter.next();
            //创建内容元素
            QDomElement subItem = doc.createElement(mapInter.key());
            //创建内容Value，并入内容元素
            QDomText text = doc.createTextNode(mapInter.value());
            subItem.appendChild(text);
            //将子元素并入Unit内
            unit.appendChild(subItem);
        }
        //将unit并入formula内
        formula.appendChild(unit);
    }
    //将formula并入root
    root.appendChild(formula);

    //保存文件
    if (!file->open(QFile::WriteOnly|QFile::Truncate))
    {
        qDebug() << "File can not access!!";
        return false;
    }
    //保存文件，设置4个空格为缩进
    QTextStream out (file);
    doc.save(out, 4);
    file->close();
    return true;
}

bool FileReadWrite::replaceProfileDetail(QString name, QMap<quint16, QMap<QString, QString> > detail, qint16 detailLength)
{
    // 长度qmap
    QMap<QString, qint16> detailLengthMap;
    // 先获取name 列表
    QList<QString> nameList;
    readProfileLists(&nameList);
    // 获取全部的profile
    QMap<QString, QMap<quint16, QMap<QString, QString>>> profileDetails;
    QListIterator<QString> nameListIterator(nameList);
    while (nameListIterator.hasNext())
    {
        // 准备subdetail 的变量
        QString subDetailName = nameListIterator.next();
        qint16 tmpDetailLength;
        QMap<quint16, QMap<QString, QString>> subDetail;
        //获取内容
        readProfileDetail(subDetailName, &subDetail, &tmpDetailLength);
        profileDetails[subDetailName] = subDetail;
        detailLengthMap[subDetailName] = tmpDetailLength;
    }
    // 替换内容
    if (!profileDetails.contains(name))
    {
        return false;
    }
    profileDetails[name] = detail;
    detailLengthMap[name] = detailLength;

    // 删除原有的配置
    nameListIterator.toFront();
    while (nameListIterator.hasNext())
    {
        deleteProfileDetail(nameListIterator.next());
    }
    // 将原有的配置恢复过去
    nameListIterator.toFront();
    while (nameListIterator.hasNext())
    {
        QString subDetailName = nameListIterator.next();
        insertProfileDetail(subDetailName, profileDetails[subDetailName], detailLengthMap[subDetailName]);
    }
    return true;
}
