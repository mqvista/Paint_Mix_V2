#ifndef FORMULALISTVIEW_H
#define FORMULALISTVIEW_H

#include <QAbstractListModel>
#include "utils/filereadwrite.h"

// 数据类型， 存放数据到类里面
class FormulaList
{
public:
    FormulaList(const QString &name);
    QString name() const;
private:
    QString m_name;
};


class FormulaListView : public QAbstractListModel
{
    Q_OBJECT

public:
    enum FormulaListRoles
    {
        NameRole = Qt::UserRole + 1
    };
    explicit FormulaListView(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    void insert(int index, const FormulaList &formulaList);

    // Append Data at last
    void append(const FormulaList &formulaList);

    // Remove data;
    void remove(int index);

    // Remove All data
    void removeAll();

    // Remove list and xml
    Q_INVOKABLE void removeWithXML(int index);

    // Get name use index 用 index 换 name
    Q_INVOKABLE QString getNameUseIndex(int index);

    // Reflush the ListView
    Q_INVOKABLE void reflushAll();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    int count() const;
    QList<FormulaList> m_list;
};

#endif // FORMULALISTVIEW_H
