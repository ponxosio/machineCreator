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
    util/AutoEnumerate.cpp \
    util/Utils.cpp \
    fluidControl/machineGraph/ContainerNode.cpp \
    fluidControl/machineGraph/ContainerNodeType.cpp \
    fluidControl/machineGraph/MachineGraph.cpp \
    fluidControl/executable/containers/actuators/communications/CommunicationsInterface.cpp \
    fluidControl/executable/containers/actuators/communications/FileSender.cpp \
    fluidControl/executable/containers/actuators/communications/SerialSender.cpp \
    fluidControl/executable/containers/BidirectionalSwitch.cpp \
    fluidControl/executable/containers/ConvergentSwitch.cpp \
    fluidControl/executable/containers/ConvergentSwitchInlet.cpp \
    fluidControl/executable/containers/DivergentSwitch.cpp \
    fluidControl/executable/containers/DivergentSwitchSink.cpp \
    fluidControl/executable/containers/FlowContainer.cpp \
    fluidControl/executable/containers/InletContainer.cpp \
    fluidControl/executable/containers/SinkContainer.cpp \
    fluidControl/executable/ExecutableMachineGraph.cpp \
    plugin/actuators/ControlPlugin.cpp \
    plugin/actuators/ExtractorPlugin.cpp \
    plugin/actuators/InjectorPlugin.cpp \
    plugin/actuators/LightPlugin.cpp \
    plugin/actuators/MixerPlugin.cpp \
    plugin/actuators/ODSensorPlugin.cpp \
    plugin/actuators/TemperaturePlugin.cpp \
    plugin/PluginFileLoader.cpp \
    plugin/PythonEnvironment.cpp \
    operables/comparison/BooleanComparison.cpp \
    operables/mathematics/ArithmeticOperation.cpp \
    operables/mathematics/ConstantNumber.cpp \
    operables/mathematics/UnaryOperation.cpp \
    operables/mathematics/VariableEntry.cpp \
    operables/VariableTable.cpp \
    pythonPlugins/EVOPROGv2/utilities/TinyWire-master/TinyWireS/TinyWireS.cpp \
    pythonPlugins/EVOPROGv2/utilities/TinyWire-master/TinyWireS/usiTwiSlave.c

HEADERS  += mainwindow.h \
    util/Patch.h \
    util/AutoEnumerate.h \
    util/Utils.h \
    graph/Edge.h \
    graph/Flow.h \
    graph/FlowPtrComparator.h \
    graph/Graph.h \
    graph/Node.h \
    fluidControl/machineGraph/ContainerNode.h \
    fluidControl/machineGraph/ContainerNodeType.h \
    fluidControl/machineGraph/MachineGraph.h \
    fluidControl/executable/containers/actuators/communications/CommandSender.h \
    fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h \
    fluidControl/executable/containers/actuators/communications/FileSender.h \
    fluidControl/executable/containers/actuators/communications/SerialSender.h \
    fluidControl/executable/containers/actuators/extras/Light.h \
    fluidControl/executable/containers/actuators/extras/Mixer.h \
    fluidControl/executable/containers/actuators/extras/ODSensor.h \
    fluidControl/executable/containers/actuators/extras/Temperature.h \
    fluidControl/executable/containers/actuators/liquids/Control.h \
    fluidControl/executable/containers/actuators/liquids/Extractor.h \
    fluidControl/executable/containers/actuators/liquids/Injector.h \
    fluidControl/executable/containers/actuators/Instructable.h \
    fluidControl/executable/containers/BidirectionalSwitch.h \
    fluidControl/executable/containers/ConvergentSwitch.h \
    fluidControl/executable/containers/ConvergentSwitchInlet.h \
    fluidControl/executable/containers/DivergentSwitch.h \
    fluidControl/executable/containers/DivergentSwitchSink.h \
    fluidControl/executable/containers/ExecutableContainerNode.h \
    fluidControl/executable/containers/FlowContainer.h \
    fluidControl/executable/containers/InletContainer.h \
    fluidControl/executable/containers/SinkContainer.h \
    fluidControl/executable/ExecutableMachineGraph.h \
    plugin/actuators/ControlPlugin.h \
    plugin/actuators/ExtractorPlugin.h \
    plugin/actuators/InjectorPlugin.h \
    plugin/actuators/LightPlugin.h \
    plugin/actuators/MixerPlugin.h \
    plugin/actuators/ODSensorPlugin.h \
    plugin/actuators/TemperaturePlugin.h \
    plugin/PluginFileLoader.h \
    plugin/PythonEnvironment.h \
    operables/comparison/BooleanComparison.h \
    operables/comparison/SimpleComparison.h \
    operables/comparison/Tautology.h \
    operables/mathematics/ArithmeticOperation.h \
    operables/mathematics/ConstantNumber.h \
    operables/mathematics/MathematicOperable.h \
    operables/mathematics/UnaryOperation.h \
    operables/mathematics/VariableEntry.h \
    operables/VariableTable.h \
    pythonPlugins/EVOPROGv2/utilities/TinyWire-master/TinyWireS/TinyWireS.h \
    pythonPlugins/EVOPROGv2/utilities/TinyWire-master/TinyWireS/usiTwiSlave.h

FORMS    += mainwindow.ui

INCLUDEPATH += X:/boost_1_61_0
INCLUDEPATH += X:/machineCreator/lib
INCLUDEPATH += C:/Python27/include

LIBS += -L$$quote(X:\boost_1_61_0\stage\lib) -lboost_python-vc140-mt-1_61
LIBS += -L$$quote(C:\Python27\libs)

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
    Img/unknow.png

