#ifndef FORMULAGRIDVIEW_H
#define FORMULAGRIDVIEW_H

#include <QAbstractListModel>
#include "utils/filereadwrite.h"

// 数据模型
class FormulaGrid
{
public:
    FormulaGrid(const QString &name, const QString &setValue, const QString &realValue, const QString &addLocal);
    QString name() const;
    QString setValue() const;
    QString realValue() const;
    QString addLocal() const;
    void setName(const QString value);
    void setSetValue(const QString value);
    void setRealValue(const QString value);
    void setAddLocal(const QString value);
private:
    QString m_name;
    QString m_setValue;
    QString m_realValue;
    QString m_addLocal;
};

// qml 获取对象接口
class FormulaGridView : public QAbstractListModel
{
    Q_OBJECT

public:
    enum FormulaGridRoles {
        NameRole = Qt::UserRole + 1,
        SetValueRole = Qt::UserRole + 2,
        RealValueRole = Qt::UserRole + 3,
        AddLocalRole = Qt::UserRole + 4
    };
    explicit FormulaGridView(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // edit the data
    bool setData(const QModelIndex& index, const QVariant& value,
        int role = Qt::EditRole) override;

    // Add data:
    void insert(int index, const FormulaGrid &formulaGrid);

    // Append Data at last
    void append(const FormulaGrid &formulaGrid);

    // Remove data;
    void remove(int index);

    // Remove All data
    void removeAll();

    // Reflush From Name
    Q_INVOKABLE void reflushUseName(QString formulaName);

    // Reflush Calc the realValue
    Q_INVOKABLE void reflushRealValue(int row, QString value);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    int count() const;
    QList<FormulaGrid> m_list;
};

#endif // FORMULAGRIDVIEW_H
