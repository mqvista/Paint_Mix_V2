#include "formulalistview.h"

// 存放数据类型
FormulaList::FormulaList(const QString &name):m_name(name)
{
}

QString FormulaList::name() const
{
    return m_name;
}



// qml 接口获取数据
FormulaListView::FormulaListView(QObject *parent)
    : QAbstractListModel(parent)
{
    FileReadWrite fileReadWrite;
    QList<QString> nameList;
    fileReadWrite.readProfileLists(&nameList);

    for (quint8 i=0; i<nameList.count(); i++)
    {
        qDebug()<<nameList.at(i);
        append(FormulaList(nameList.at(i)));
    }
}

int FormulaListView::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    Q_UNUSED(parent);
    return m_list.count();
}

QVariant FormulaListView::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    if (index.row() < 0 || index.row() >= m_list.count())
        return QVariant();
    const FormulaList &formulaList = m_list[index.row()];
    if (role == NameRole)
        return formulaList.name();
    return QVariant();
}

bool FormulaListView::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags FormulaListView::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

void FormulaListView::insert(int index, const FormulaList &formulaList)
{
    if (index < 0 || index > m_list.count())
        return;
    beginInsertRows(QModelIndex(), index, index);
    // FIXME: Implement me!
    m_list.insert(index, formulaList);
    endInsertRows();

}

void FormulaListView::append(const FormulaList &formulaList)
{
    insert(count(), formulaList);
}

void FormulaListView::remove(int index)
{
    if (index < 0 || index >= m_list.count())
    {
        return;
    }
    beginRemoveRows(QModelIndex(), index, index);
    m_list.removeAt(index);
    endRemoveRows();
}

void FormulaListView::removeAll()
{
    if (m_list.count() > 0)
    {
        int cot = m_list.count();
        for (int i=0; i<= cot; i++)
        {
            remove(0);
        }
    }
}

void FormulaListView::removeWithXML(int index)
{
    FileReadWrite fileReadWrite;
    fileReadWrite.deleteProfileDetail(getNameUseIndex(index));
    remove(index);
}

QString FormulaListView::getNameUseIndex(int index)
{
    if (index < 0 || index > m_list.count())
        return 0;
    // 从 m_list 内获取 name
    return m_list.at(index).name();

}

void FormulaListView::reflushAll()
{
    removeAll();
    FileReadWrite fileReadWrite;
    QList<QString> nameList;
    fileReadWrite.readProfileLists(&nameList);

    for (quint8 i=0; i<nameList.count(); i++)
    {
        qDebug()<<nameList.at(i);
        append(FormulaList(nameList.at(i)));
    }
}

QHash<int, QByteArray> FormulaListView::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

int FormulaListView::count() const
{
    return rowCount(QModelIndex());
}


