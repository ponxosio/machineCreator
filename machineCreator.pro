#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T13:00:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = machineCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gui/customcontaineritem.cpp \
    gui/customedgegraphicsitem.cpp \
    gui/graphicsmanager.cpp \
    gui/pluginmanagerdialog.cpp \
    gui/pluginmanager.cpp \
    gui/newplugindialog.cpp \
    gui/editplugindialog.cpp \
    gui/newcontainerdialog.cpp \
    gui/idemitingpushbutton.cpp \
    gui/cretefilesenderdialog.cpp \
    gui/createserialsenderdialog.cpp
HEADERS  += mainwindow.h \
    gui/customcontaineritem.h \
    gui/customedgegraphicsitem.h \
    gui/graphicsmanager.h \
    gui/pluginmanagerdialog.h \
    gui/pluginmanager.h \
    gui/newplugindialog.h \
    gui/editplugindialog.h \
    gui/newcontainerdialog.h \
    gui/idemitingpushbutton.h \
    gui/cretefilesenderdialog.h \
    gui/createserialsenderdialog.h

FORMS    += mainwindow.ui

INCLUDEPATH += X:/boost_1_61_0
INCLUDEPATH += X:/EvoCoreLibrary/include
INCLUDEPATH += X:/EvoCoreLibrary/lib
INCLUDEPATH += C:/Python27/include

LIBS += -L$$quote(X:/boost_1_61_0/stage/lib) -lboost_python-vc140-mt-1_61
LIBS += -L$$quote(C:/Python27/libs)
LIBS += -L$$quote(X:/EvoCoreLibrary/lib) -lEvoCoderCore

QMAKE_CXXFLAGS += -bigobj

DISTFILES += \
    configuration/log.ini \
    inputFileData.txt \
    test.log \
    pythonPlugins/basePlugins/control.pyc \
    pythonPlugins/basePlugins/extractor.pyc \
    pythonPlugins/basePlugins/injector.pyc \
    pythonPlugins/basePlugins/odsensor.pyc \
    pythonPlugins/EVOPROG/EVOPROG_continuousPump.pyc \
    pythonPlugins/EVOPROG/EVOPROG_discretePump.pyc \
    pythonPlugins/EVOPROG/EVOPROG_dummyInjector.pyc \
    pythonPlugins/EVOPROG/EVOPROG_odsensor.pyc \
    pythonPlugins/EVOPROG/EVOPROG_sixwayvalve.pyc \
    pythonPlugins/EVOPROGv2/evoprog2wayvalve.pyc \
    pythonPlugins/EVOPROGv2/evoprogv2pump.pyc \
    pythonPlugins/basePlugins/control.py \
    pythonPlugins/basePlugins/extractor.py \
    pythonPlugins/basePlugins/injector.py \
    pythonPlugins/basePlugins/light.py \
    pythonPlugins/basePlugins/mixer.py \
    pythonPlugins/basePlugins/odsensor.py \
    pythonPlugins/basePlugins/temperature.py \
    pythonPlugins/EVOPROG/EVOPROG_continuousPump.py \
    pythonPlugins/EVOPROG/EVOPROG_discretePump.py \
    pythonPlugins/EVOPROG/EVOPROG_dummyInjector.py \
    pythonPlugins/EVOPROG/EVOPROG_light.py \
    pythonPlugins/EVOPROG/EVOPROG_mixer.py \
    pythonPlugins/EVOPROG/EVOPROG_odsensor.py \
    pythonPlugins/EVOPROG/EVOPROG_sixwayvalve.py \
    pythonPlugins/EVOPROG/EVOPROG_temperature.py \
    pythonPlugins/EVOPROGv2/evoprog1wayvalve.py \
    pythonPlugins/EVOPROGv2/evoprog2wayvalve.py \
    pythonPlugins/EVOPROGv2/evoprogv2pump.py \
    Img/continuous_bidirectionalswitch.png \
    Img/continuous_convergentswitchinlet.png \
    Img/continuous_divergentswitch.png \
    Img/continuous_divergentswitchsink.png \
    Img/continuous_flow.png \
    Img/continuous_inlet.png \
    Img/convergentswitch.png \
    Img/discrete_bidirectionalswitch.png \
    Img/discrete_convergentswitchinlet.png \
    Img/discrete_divergentswitch.png \
    Img/discrete_divergentswitchsink.png \
    Img/discrete_flow.png \
    Img/discrete_inlet.png \
    Img/light.png \
    Img/mixer.png \
    Img/odsensor.png \
    Img/sink.png \
    Img/temperature.png \
    Img/unknow.png \
    ico/about.png \
    ico/add.png \
    ico/configuration.png \
    ico/connect.png \
    ico/edit.png \
    ico/export.png \
    ico/open.png \
    ico/remove.png \
    ico/zoom-in.png \
    ico/zoom-out.png \
    ico/add.ico \
    ico/configuration.ico \
    ico/connect.ico \
    ico/edit.ico \
    ico/export.ico \
    ico/open.ico \
    ico/remove.ico \
    ico/zoom-in.ico \
    ico/zoom-out.ico

RESOURCES += \
    icons.qrc

