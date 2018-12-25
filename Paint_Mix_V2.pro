QT += quick
QT += xml
QT += serialport
CONFIG += c++11
CONFIG += sdk_no_version_check


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    utils/filereadwrite.cpp \
    control/scales.cpp \
    control/scalesbig.cpp \
    control/scalessmall.cpp \
    service.cpp \
    control/scalesworker.cpp \
    control/motion.cpp \
    control/motionworker.cpp \
    PaintMixModule/taskmodule.cpp \
    PaintMixModule/indexmodule.cpp \
    PaintMixModule/formulalistview.cpp \
    PaintMixModule/formulagridview.cpp \
    PaintMixModule/formulaaddnew.cpp \
    PaintMixModule/formulaaddition.cpp \
    utils/loginfo.cpp \
    utils/errorhandle.cpp \
    testUseModule/pagesecond.cpp \
    utils/systemcontrol.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    utils/filereadwrite.h \
    control/scales.h \
    control/scalesbig.h \
    control/scalessmall.h \
    service.h \
    control/scalesworker.h \
    control/motion.h \
    control/motionworker.h \
    PaintMixModule/taskmodule.h \
    PaintMixModule/indexmodule.h \
    PaintMixModule/formulalistview.h \
    PaintMixModule/formulagridview.h \
    PaintMixModule/formulaaddnew.h \
    PaintMixModule/formulaaddition.h \
    utils/loginfo.h \
    utils/errorhandle.h \
    testUseModule/pagesecond.h \
    utils/windowfilter.h \
    utils/systemcontrol.h

# 添加机台驱动
unix:!macx: LIBS += -L$$PWD/DriverGC/arm_linux/ -lDriverGC
macx: LIBS += -L$$PWD/DriverGC/osx/ -lDriverGC.1.0.0
win32: LIBS += -L$$PWD/DriverGC/win/ -lDriverGC

INCLUDEPATH += $$PWD/DriverGC/include
DEPENDPATH += $$PWD/DriverGC/include
