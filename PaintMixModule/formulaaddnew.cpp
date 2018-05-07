#include "formulaaddnew.h"

// 数据结构
AddNewModel::AddNewModel(const QString itemName, const QString addLocal, const QString setWeight, const QString motorNum, const QString percent):
    m_itemName(itemName), m_addLocal(addLocal), m_setWeight(setWeight), m_motorNum(motorNum), m_percent(percent)
{

}


// 数据模型
FormulaAddNew::FormulaAddNew(QObject *parent)
    : QAbstractListModel(parent)
{
}

int FormulaAddNew::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    Q_UNUSED(parent);
    return m_list.count();
}

QVariant FormulaAddNew::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    if (index.row() < 0 || index.row() >= m_list.count())
        return QVariant();
    const AddNewModel &addNewModel = m_list[index.row()];
    if (role == ItemNameRole)
        return addNewModel.itemName();
    if (role == AddLocalRole)
        return addNewModel.addLocal();
    if (role == SetWeightRole)
        return addNewModel.setWeight();
    if (role == MotorNumRole)
        return addNewModel.motorNum();
    if (role == PercentRole)
        return addNewModel.percent();
    return QVariant();
}

bool FormulaAddNew::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_list.count())
        return false;
    if (data(index, role) != value) {
        // FIXME: Implement me!
        AddNewModel &addNewModel = m_list[index.row()];
        if (role == ItemNameRole)
            addNewModel.set_itemName(value.toString());
        else if (role == AddLocalRole)
            addNewModel.set_addLocal(value.toString());
        else if (role == SetWeightRole)
            addNewModel.set_setWeight(value.toString());
        else if (role == MotorNumRole)
            addNewModel.set_motorNum(value.toString());
        else if (role == PercentRole)
            addNewModel.set_percent(value.toString());
        else return false;

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags FormulaAddNew::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool FormulaAddNew::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!

    // TODO 好像有点毛病，到时候研究下
    //for (quint8 i=row; i<=row+count-1; i++)
    //{
    m_list.insert(row, AddNewModel("","","","",""));
    //}

    endInsertRows();
    return true;
}

bool FormulaAddNew::removeRows(int row, int count, const QModelIndex &parent)
{
    //qDebug()<< "################################";
    //qDebug()<< "m_list.count->" << m_list.count();
    //qDebug()<< "row->" <<row << "count" << count;
    //qDebug()<< "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    for (quint8 i = row+count-1; i <= row; i++)
    {
        m_list.removeAt(i);
    }
    endRemoveRows();
    return true;
}

bool FormulaAddNew::move(int srcIndex, int desIndex)
{
    //qDebug() << "count:->"<< m_list.count();
    if (desIndex > srcIndex)
    {
        int tmp_index = srcIndex+1 >= desIndex ? desIndex+1 : desIndex;
        emit beginMoveRows(QModelIndex(), srcIndex, srcIndex, QModelIndex(), tmp_index);

        // 设定临时变量 存放数据
        AddNewModel tempModel = m_list.at(srcIndex);
        for (int i=srcIndex; i<desIndex; i++)
        {
            m_list[i] = m_list.at(i + 1);
        }
        m_list[desIndex] = tempModel;

        emit endMoveRows();
        return true;

    }
    else if (srcIndex > desIndex)
    {
        emit beginMoveRows(QModelIndex(), srcIndex, srcIndex, QModelIndex(), desIndex);

        AddNewModel tempModel = m_list.at(srcIndex);
        for (int i=srcIndex; i > desIndex; i--)
        {
            m_list[i] =m_list.at(i-1);
        }
        m_list[desIndex] = tempModel;

        emit endMoveRows();
        return true;
    }

    return false;
}


//删除所有的内容
bool FormulaAddNew::removeAll()
{
    beginRemoveRows(QModelIndex(), 0, m_list.count()-1);
    m_list.clear();
    endRemoveRows();
    return true;
}

// 刷新listview 界面 只留一个
void FormulaAddNew::reflush()
{
    // 先清除 m_list 里面所有的东东
    removeAll();
    // 再在 m_list 里面插入一个空行
    insertRows(0, 1);
}

bool FormulaAddNew::saveFormula(QString fName)
{
    FileReadWrite fileReadWrite;
    QMap<quint16, QMap<QString, QString>> formula;
    for (int i=0; i<m_list.count(); i++)
    {
        if (m_list.at(i).itemName() == "Motor")
        {
            // 判断是否为空
            if (m_list.at(i).addLocal() != "" && m_list.at(i).setWeight() != "" && m_list.at(i).motorNum() != "")
            {
                QMap<QString, QString> tmp_map;
                // 先插电机号
                tmp_map.insert("Motor", m_list.at(i).motorNum());
                // 再插秤号
                tmp_map.insert("Scales", m_list.at(i).addLocal());
                // 最后插重量
                tmp_map.insert("Weight", m_list.at(i).setWeight());
                // 插入到大的 map 里面
                formula.insert(i+1, tmp_map);
                continue;
            }
            // 有空数值，返回 false
            return false;
        }

        if (m_list.at(i).itemName() == "Water")
        {
            // 判断是否为空
            if (m_list.at(i).addLocal() != "" && m_list.at(i).setWeight() != "")
            {
                QMap<QString, QString> tmp_map;
                // 先插water  号码无所谓
                tmp_map.insert("Water", "1");
                // 再插秤号
                tmp_map.insert("Scales", m_list.at(i).addLocal());
                // 最后插重量
                tmp_map.insert("Weight", m_list.at(i).setWeight());
                // 插入到大的 map 里面
                formula.insert(i+1, tmp_map);
                continue;
            }
            // 有空数值，返回 false
            return false;
        }

        if (m_list.at(i).itemName() == "Exchange")
        {
            QMap<QString, QString> tmp_map;
            // 先插 exchange  号码无所谓
            tmp_map.insert("Exchange", "1");
            // 插入到大的 map 里面
            formula.insert(i+1, tmp_map);
            continue;
        }
        // 如果有没判断到的内容, 则为空数据
        return false;
    }
    if (fName == "")
    {
        return false;
    }
    if (fileReadWrite.insertProfileDetail(fName, formula, m_list.count()))
    {
        return true;
    }
    qDebug() << formula;
    //if (fileReadWrite.insertProfileDetail())
    return true;
}

bool FormulaAddNew::updatePercent()
{
    quint16 totalWeight = 0;
    // 先计算重量的总和
    for (int i=0; i<m_list.count(); i++)
    {
        if ((m_list.at(i).itemName() == "Motor" || m_list.at(i).itemName() == "Water")
                && m_list.at(i).setWeight() != "")
        {
            totalWeight += m_list.at(i).setWeight().toInt();
        }
    }

    // 再计算百分比
    for (int i=0; i<m_list.count(); i++)
    {
        // 先计算重量的总和
        if (m_list.at(i).itemName() == "Motor" || m_list.at(i).itemName() == "Water")
        {
            // 先设定下 index
            QModelIndex index = this->index(i);

            if (m_list.at(i).setWeight().toInt() > 0)
            {
                // 除一下知道百分比
                float percent;
                percent = m_list.at(i).setWeight().toFloat() / totalWeight * 100;
                // 转到 qv 里面
                QVariant qv = QString::number(percent, 'f', 1);
                // 最后设定进去
                setData(index, qv, PercentRole);
            }
            else
            {
                // 转到 qv 里面
                QVariant qv = "--";
                // 最后设定进去
                setData(index, qv, PercentRole);
            }
        }
    }


    qDebug() << totalWeight;
    return true;
}

QHash<int, QByteArray> FormulaAddNew::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemNameRole] = "ItemName";
    roles[AddLocalRole] = "AddLocal";
    roles[SetWeightRole] = "SetWeight";
    roles[MotorNumRole] = "MotorNum";
    roles[PercentRole] = "Percent";
    return roles;
}


