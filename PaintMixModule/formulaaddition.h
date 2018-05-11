#ifndef FORMULAADDITION_H
#define FORMULAADDITION_H

#include <QAbstractListModel>
#include "control/motionworker.h"
typedef QMap<quint16, QMap<QString, QString>> detailType;

class AdditionModel{
public:
    AdditionModel(const QString itemName, const QString addLocal, const QString setWeight, const QString motorNum, const QString percent, const QString offset, const QString offsetPercent);
    QString itemName() const
    {
        return m_itemName;
    }
    QString addLocal() const
    {
        return m_addLocal;
    }
    QString setWeight() const
    {
        return m_setWeight;
    }
    QString motorNum() const
    {
        return m_motorNum;
    }
    QString percent() const
    {
        return m_percent;
    }
    QString offset() const
    {
        return m_offset;
    }
    QString offsetPercent() const
    {
        return m_offsetPercent;
    }
    void set_itemName(const QString value)
    {
        m_itemName = value;
    }
    void set_addLocal(const QString value)
    {
        m_addLocal = value;
    }
    void set_setWeight(const QString value)
    {
        m_setWeight = value;
    }
    void set_motorNum(const QString value)
    {
        m_motorNum = value;
    }
    void set_percent(const QString value)
    {
        m_percent = value;
    }
    void set_offset(const QString value)
    {
        m_offset = value;
    }
    void set_offsetPercent(const QString value)
    {
        m_offsetPercent = value;
    }

private:
    QString m_itemName;
    QString m_addLocal;
    QString m_setWeight;
    QString m_motorNum;
    QString m_percent;
    QString m_offset;
    QString m_offsetPercent;
};




class FormulaAddition : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        ItemNameRole = Qt::UserRole + 1,
        AddLocalRole = Qt::UserRole + 2,
        SetWeightRole = Qt::UserRole + 3,
        MotorNumRole = Qt::UserRole + 4,
        PercentRole = Qt::UserRole + 5,
        OffsetRole = Qt::UserRole + 6,
        OffsetPercentRole = Qt::UserRole + 7
    };
    explicit FormulaAddition(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex& index, const QVariant& value,
        int role = Qt::EditRole) override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove all in m_list
    bool removeAll();

    // Remove all rows and Add an xml formula
    Q_INVOKABLE void reflush(QString fName);

    Q_INVOKABLE void reflushOffsetPercent();

    Q_INVOKABLE void runFormula();

    Q_INVOKABLE QMap<quint16, QMap<QString, QString>> getFormulaDetail();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<AdditionModel> m_list;
};

#endif // FORMULAADDITION_H
