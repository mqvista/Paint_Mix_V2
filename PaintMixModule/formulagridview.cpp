#include "formulagridview.h"

// 数据模型
FormulaGrid::FormulaGrid(const QString &name, const QString &setValue, const QString &realValue, const QString &addLocal)
    :m_name(name), m_setValue(setValue), m_realValue(realValue), m_addLocal(addLocal)
{

}

QString FormulaGrid::name() const
{
    return m_name;
}

QString FormulaGrid::setValue() const
{
    return m_setValue;
}

QString FormulaGrid::realValue() const
{
    return m_realValue;
}

QString FormulaGrid::addLocal() const
{
    return m_addLocal;
}



// qml 获取对象接口
FormulaGridView::FormulaGridView(QObject *parent)
    : QAbstractListModel(parent)
{
}

int FormulaGridView::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    Q_UNUSED(parent);
    return m_list.count();
}

QVariant FormulaGridView::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    const FormulaGrid &formulaGrid = m_list[index.row()];

    if (role == NameRole)
        return formulaGrid.name();
    if (role == SetValueRole)
        return formulaGrid.setValue();
    if (role == RealValueRole)
        return formulaGrid.realValue();
    if (role == AddLocalRole)
        return formulaGrid.addLocal();

    return QVariant();
}

void FormulaGridView::insert(int index, const FormulaGrid &formulaGrid)
{
    if (index < 0 || index > m_list.count())
        return;
    beginInsertRows(QModelIndex(), index, index);
    m_list.insert(index, formulaGrid);
    endInsertRows();
}

void FormulaGridView::append(const FormulaGrid &formulaGrid)
{
    insert(count(), formulaGrid);
}

void FormulaGridView::remove(int index)
{
    if(index < 0 || index >= m_list.count()) {
        return;
    }
    beginRemoveRows(QModelIndex(), index, index);
    m_list.removeAt(index);
    endRemoveRows();
}

void FormulaGridView::removeAll()
{
    if (m_list.count() > 0)
    {
        int cot = m_list.count();
        for (int i=0 ; i<= cot; i++)
        {
            remove(0);
        }
    }
}

// 使用名称 刷新gridview 数据
void FormulaGridView::reflushUseName(QString formulaName)
{
    // 先移除原有的数据
    removeAll();
    // 新建一个存储的临时map
    QMap<quint16, QMap<QString, QString>> detail;
    qint16 length;
    FileReadWrite fileReadWrite;
    //读取配置文件
    fileReadWrite.readProfileDetail(formulaName, &detail, &length);
    // 通过长度迭代出数据
    for (quint8 i=1; i<=length; i++)
    {
        QMap<QString, QString> subDetail = detail.value(i);
        // 判断是否是注液
        if (subDetail.count("Motor") == 1)
        {
            QString name = "颜料" + subDetail.value("Motor");
            QString setValue = subDetail.value("Weight") + "G";
            QString realValue = "-----";
            QString addLocal;
            if (subDetail.value("Scales") == 1)
            {
                addLocal = "小秤";
            }
            else
            {
                addLocal = "大秤";
            }
            append(FormulaGrid(name, setValue, realValue, addLocal));
            continue;
        }
        // 判断是否是加水
        if (subDetail.count("Water") == 1)
        {
            QString name = "加水";
            QString setValue = subDetail.value("Weight") + "G";
            QString realValue = "-----";
            QString addLocal;
            if (subDetail.value("Scales") == 1)
            {
                addLocal = "小秤";
            }
            else
            {
                addLocal = "大秤";
            }
            append(FormulaGrid(name, setValue, realValue, addLocal));
            continue;
        }
        // 判断是否是转移液体
        if (subDetail.count("Exchange") == 1)
        {
            QString name = "移液";
            QString setValue = "-----";;
            QString realValue = "-----";
            QString addLocal;
            if (subDetail.value("Scales") == 1)
            {
                addLocal = "小秤";
            }
            else
            {
                addLocal = "大秤";
            }
            append(FormulaGrid(name, setValue, realValue, addLocal));
            continue;
        }

    }
}

QHash<int, QByteArray> FormulaGridView::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[SetValueRole] = "setValue";
    roles[RealValueRole] = "realValue";
    roles[AddLocalRole] = "addLocal";
    return roles;
}

int FormulaGridView::count() const
{
    return rowCount(QModelIndex());
}




