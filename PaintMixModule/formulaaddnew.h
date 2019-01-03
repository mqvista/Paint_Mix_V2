#ifndef FORMULAADDNEW_H
#define FORMULAADDNEW_H

#include <QAbstractListModel>
#include <QDebug>
#include "utils/filereadwrite.h"

class AddNewModel{
public:
    AddNewModel(const QString itemName, const QString addLocal, const QString setWeight, const QString motorNum, const QString percent);
    /*AddNewModel(const AddNewModel& model)
    {
        m_itemName = model.itemName();
        m_addLocal = model.addLocal();
        m_setWeight = model.setWeight();
    }*/
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

private:
    QString m_itemName;
    QString m_addLocal;
    QString m_setWeight;
    QString m_motorNum;
    QString m_percent;
};

class FormulaAddNew : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(double totalWeight READ totalWeight NOTIFY totalWeightChanged)

public:
    enum {
        ItemNameRole = Qt::UserRole + 1,
        AddLocalRole = Qt::UserRole + 2,
        SetWeightRole = Qt::UserRole + 3,
        MotorNumRole = Qt::UserRole + 4,
        PercentRole = Qt::UserRole + 5
    };
    explicit FormulaAddNew(QObject* parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex& index, const QVariant& value,
        int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    Q_INVOKABLE bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    // Remove data:
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    // Move row to any where
    Q_INVOKABLE bool move(int srcIndex, int desIndex);

    // Remove all in m_list
    bool removeAll();

    // Remove all rows and Add an new empty row
    Q_INVOKABLE void reflush();

    // Save current formula into xml file
    Q_INVOKABLE bool saveFormula(QString fName);

    //
    Q_INVOKABLE bool updatePercent();

    double totalWeight();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<AddNewModel> m_list;
    double m_totalWeight;

signals:
    void totalWeightChanged();
};

#endif // FORMULAADDNEW_H
