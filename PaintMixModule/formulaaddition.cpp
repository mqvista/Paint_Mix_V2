#include "formulaaddition.h"
#include "utils/filereadwrite.h"

// 数据结构
AdditionModel::AdditionModel(const QString itemName, const QString addLocal, const QString setWeight,
                             const QString motorNum, const QString percent, const QString offset, const QString offsetPercent):
    m_itemName(itemName), m_addLocal(addLocal), m_setWeight(setWeight), m_motorNum(motorNum),
    m_percent(percent), m_offset(offset), m_offsetPercent(offsetPercent)
{

}


// 数据模型
FormulaAddition::FormulaAddition(QObject *parent)
    : QAbstractListModel(parent)
{
    qRegisterMetaType<detailType>("detailType");
}

int FormulaAddition::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    Q_UNUSED(parent);
    return m_list.count();
}

QVariant FormulaAddition::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() >= m_list.count())
        return QVariant();
    const AdditionModel &additionModel = m_list[index.row()];
    if (role == ItemNameRole)
        return additionModel.itemName();
    if (role == AddLocalRole)
        return additionModel.addLocal();
    if (role == SetWeightRole)
        return additionModel.setWeight();
    if (role == MotorNumRole)
        return additionModel.motorNum();
    if (role == PercentRole)
        return additionModel.percent();
    if (role == OffsetRole)
        return additionModel.offset();
    if (role == OffsetPercentRole)
        return additionModel.offsetPercent();
    return QVariant();
}

bool FormulaAddition::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_list.count())
        return false;
    if (data(index, role) != value) {
        AdditionModel &additionModel = m_list[index.row()];
        if (role == ItemNameRole)
            additionModel.set_itemName(value.toString());
        else if (role == AddLocalRole)
            additionModel.set_addLocal(value.toString());
        else if (role == SetWeightRole)
            additionModel.set_setWeight(value.toString());
        else if (role == MotorNumRole)
            additionModel.set_motorNum(value.toString());
        else if (role == PercentRole)
            additionModel.set_percent(value.toString());
        else if (role == OffsetRole)
            additionModel.set_offset(value.toString());
        else if (role == OffsetPercentRole)
            additionModel.set_offsetPercent(value.toString());
        else return false;

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

bool FormulaAddition::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    m_list.insert(row, AdditionModel("","","","","","",""));
    endInsertRows();
    return true;
}

bool FormulaAddition::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row+count-1; i <= row; i++)
    {
        m_list.removeAt(i);
    }
    endRemoveRows();
    return true;
}

bool FormulaAddition::removeAll()
{
    beginRemoveRows(QModelIndex(), 0, m_list.count()-1);
    m_list.clear();
    endRemoveRows();
    return true;
}

void FormulaAddition::reflush(QString fName)
{
    // 先移除所有的东东
    removeAll();
    FileReadWrite fileReadWrite;
    QMap<quint16, QMap<QString, QString>> formula;
    qint16 detailLength;
    fileReadWrite.readProfileDetail(fName, &formula, &detailLength);

    // 计算原来的克重
    double totalWeight = 0;
    QList<QString> calcPercent;
    // 先算总重量
    for (quint16 i=1; i<= detailLength; i++)
    {
        // 获取数据
        QMap<QString, QString> tempFormula;
        tempFormula = formula.value(i);

        if (tempFormula.contains("Motor") || tempFormula.contains("Water") || tempFormula.contains("AddWaterMiddle") || tempFormula.contains("AdditionPaint"))
        {
            totalWeight += tempFormula.value("Weight").toDouble();
        }
    }
    // 计算原来的百分比
    for (quint16 i=1; i<= detailLength; i++)
    {
        // 先填充percent 保证里面不会是为初始化的
        //calcPercent[i-1] = "";
        calcPercent.append("");
        // 获取数据
        QMap<QString, QString> tempFormula;
        tempFormula = formula.value(i);
        if (tempFormula.contains("Motor") || tempFormula.contains("Water") || tempFormula.contains("AddWaterMiddle") || tempFormula.contains("AdditionPaint"))
        {
            double tempPercent = tempFormula.value("Weight").toDouble() / totalWeight * 100;
            calcPercent[i-1] = QString::number(tempPercent, 'f', 2);
        }
    }

    // 计算好数据后填充到显示界面里面
    for (quint16 i=1; i<= detailLength; i++)
    {
        // 插入一行吧
        insertRows(i-1, 1);
        // 获取当前 index
        QModelIndex index = this->index(i-1);
        // 获取数据
        QMap<QString, QString> tempFormula;
        tempFormula = formula.value(i);


        // 判断是否是注液 ？
        if (tempFormula.contains("Motor"))
        {
            QVariant itemName = "Motor";
            setData(index, itemName, ItemNameRole);
            QVariant motor = tempFormula.value("Motor");
            setData(index, motor, MotorNumRole);
            QVariant scales = tempFormula.value("Scales");
            setData(index, scales, AddLocalRole);
            QVariant weight = tempFormula.value("Weight");
            setData(index, weight, SetWeightRole);
            QVariant percernt = calcPercent.at(i-1);
            setData(index, percernt, PercentRole);
            continue;
        }
        // 判断是否是注水 ？
        if (tempFormula.contains("Water"))
        {
            QVariant itemName = "Water";
            setData(index, itemName, ItemNameRole);
            QVariant scales = tempFormula.value("Scales");
            setData(index, scales, AddLocalRole);
            QVariant weight = tempFormula.value("Weight");
            setData(index, weight, SetWeightRole);
            QVariant percernt = calcPercent.at(i-1);
            setData(index, percernt, PercentRole);
            continue;
        }
        // 判断是否是加水中桶
        if (tempFormula.contains("AddWaterMiddle"))
        {
            QVariant itemName = "Water";
            setData(index, itemName, ItemNameRole);
            QVariant scales = 3;
            setData(index, scales, AddLocalRole);
            QVariant weight = tempFormula.value("Weight");
            setData(index, weight, SetWeightRole);
            QVariant percernt = calcPercent.at(i-1);
            setData(index, percernt, PercentRole);
            continue;
        }
        // 判断是否是移液 ？
        if (tempFormula.contains("PumpScaleOutside"))
        {
            QVariant itemName = "PumpScaleOutside";
            setData(index, itemName, ItemNameRole);
            if (tempFormula.value("PumpScaleOutside") == "1")
            {
                QVariant scales = 1;
                setData(index, scales, AddLocalRole);
            }
            else if (tempFormula.value("PumpScaleOutside") == "2")
            {
                QVariant scales = 2;
                setData(index, scales, AddLocalRole);
            }
            continue;
        }
        //
        // 判断是否是泵液 ？
        if (tempFormula.contains("AdditionPaint"))
        {
            QVariant itemName = "AdditionPaint";
            setData(index, itemName, ItemNameRole);
            QVariant motor = tempFormula.value("AdditionPaint");
            setData(index, motor, MotorNumRole);
            QVariant scales = tempFormula.value("Scales");
            setData(index, scales, AddLocalRole);
            QVariant weight = tempFormula.value("Weight");
            setData(index, weight, SetWeightRole);
            QVariant percernt = calcPercent.at(i-1);
            setData(index, percernt, PercentRole);
            continue;
        }
    }
}

void FormulaAddition::reflushOffsetPercent()
{
    double totalWeight = 0;
    // 先计算重量的总和
    for (int i=0; i<m_list.count(); i++)
    {
        if (m_list.at(i).itemName() == "Motor" || m_list.at(i).itemName() == "Water" || m_list.at(i).itemName() == "AddWaterMiddle" || m_list.at(i).itemName() == "AdditionPaint")
        {
            totalWeight += m_list.at(i).setWeight().toDouble() + m_list.at(i).offset().toDouble();
        }
    }

    // 再计算百分比
    for (int i=0; i<m_list.count(); i++)
    {
        // 先计算重量的总和
        if (m_list.at(i).itemName() == "Motor" || m_list.at(i).itemName() == "Water" || m_list.at(i).itemName() == "AddWaterMiddle" || m_list.at(i).itemName() == "AdditionPaint")
        {
            // 先设定下 index
            QModelIndex index = this->index(i);

            // 除一下知道百分比
            double percent;
            percent = (m_list.at(i).setWeight().toDouble() + m_list.at(i).offset().toDouble()) / totalWeight * 100;
            // 转到 qv 里面
            QVariant qv = QString::number(percent, 'f', 2);
            // 最后设定进去
            setData(index, qv, OffsetPercentRole);
        }
    }
}


// TODO 等待实现后面的调整参数
void FormulaAddition::runAndSaveFixedFormula(QString fName)
{
    FixedType tempFormula;
    tempFormula = getFormulaDetail();
    // TODO 还需要传入新修改的内容
    QMetaObject::invokeMethod(MotionWorker::Instance(), "runAndSaveNewFormula",
                              Qt::QueuedConnection, Q_ARG(QString, fName), Q_ARG(FixedType, tempFormula));

}

QMap<quint16, QMap<QString, QString> > FormulaAddition::getFormulaDetail()
{
    QMap<quint16, QMap<QString, QString>> formula;
    for (int i=0; i<m_list.count(); i++)
    {
        if (m_list.at(i).itemName() == "Motor")
        {
            qint32 weight = m_list.at(i).setWeight().toInt() + m_list.at(i).offset().toInt();

            QMap<QString, QString> tmp_map;
            // 先插电机号
            tmp_map.insert("Motor", m_list.at(i).motorNum());
            // 再插秤号
            tmp_map.insert("Scales", m_list.at(i).addLocal());
            // 最后插重量
            tmp_map.insert("Weight", QString::number(weight));
            // 插入到大的 map 里面
            formula.insert(quint8(i+1), tmp_map);
            continue;
        }

        if (m_list.at(i).itemName() == "Water" && (m_list.at(i).addLocal() != "3"))
        {
            double weight = m_list.at(i).setWeight().toDouble() + m_list.at(i).offset().toDouble();

                QMap<QString, QString> tmp_map;
                // 先插water  号码无所谓
                tmp_map.insert("Water", "1");
                // 再插秤号
                tmp_map.insert("Scales", m_list.at(i).addLocal());
                // 最后插重量
                tmp_map.insert("Weight", QString::number(weight));
                // 插入到大的 map 里面
                formula.insert(quint8(i+1), tmp_map);
                continue;
        }

        if (m_list.at(i).itemName() == "Water" && (m_list.at(i).addLocal() == "3"))
        {
            qint32 weight = m_list.at(i).setWeight().toDouble() + m_list.at(i).offset().toDouble();
            QMap<QString, QString> tmp_map;
            // 先插 name 号码无所谓
            tmp_map.insert("AddWaterMiddle", "1");
            // 插入 weight
            tmp_map.insert("Weight", QString::number(weight));
            // 插入到大的 map 里面
            formula.insert(quint8(i+1), tmp_map);
            continue;
        }

        if (m_list.at(i).itemName() == "PumpScaleOutside")
        {
            QMap<QString, QString> tmp_map;
            // 先插 exchange  号码无所谓
            tmp_map.insert("PumpScaleOutside", m_list.at(i).addLocal());
            // 插入到大的 map 里面
            formula.insert(quint8(i+1), tmp_map);
            continue;
        }

        if (m_list.at(i).itemName() == "AdditionPaint")
        {
            double weight = m_list.at(i).setWeight().toDouble() + m_list.at(i).offset().toDouble();

            QMap<QString, QString> tmp_map;
            // 先插AdditionPaint  号码无所谓
            tmp_map.insert("AdditionPaint", m_list.at(i).motorNum());
            // 再插秤号
            tmp_map.insert("Scales", m_list.at(i).addLocal());
            // 最后插重量
            tmp_map.insert("Weight", QString::number(weight));
            // 插入到大的 map 里面
            formula.insert(quint8(i+1), tmp_map);
            continue;
        }
    }
    return formula;
}


QHash<int, QByteArray> FormulaAddition::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemNameRole] = "ItemName";
    roles[AddLocalRole] = "AddLocal";
    roles[SetWeightRole] = "SetWeight";
    roles[MotorNumRole] = "MotorNum";
    roles[PercentRole] = "Percent";
    roles[OffsetRole] = "Offset";
    roles[OffsetPercentRole] = "OffsetPercent";
    return roles;
}




