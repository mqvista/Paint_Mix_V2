#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "control/scalesworker.h"
#include "control/motionworker.h"


//module
#include "PaintMixModule/taskmodule.h"
#include "PaintMixModule/indexmodule.h"
#include "PaintMixModule/formulalistview.h"
#include "PaintMixModule/formulagridview.h"
#include "PaintMixModule/formulaaddnew.h"

class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QQmlApplicationEngine *appEng, QObject *parent = nullptr);
    ~Service();
    void initContext();
    void initSignalSlotConnect();
    void initSystem();


signals:

public slots:

private:
    QQmlApplicationEngine *m_engine;
    QThread scalesWorkerThread;
    QThread motionWorkerThread;

    //module
    TaskModule m_TaskModule;
    IndexModule m_IndexModule;
    FormulaListView m_FormulaListView;
    FormulaGridView m_FormulaGridView;
    FormulaAddNew m_FormulaAddNew;

};

#endif // SERVICE_H
