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
    gui/customimagegraphicsitem.cpp

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
    operables/comparison/ComparisonOperable.h \
    lib/cereal/archives/adapters.hpp \
    lib/cereal/archives/binary.hpp \
    lib/cereal/archives/json.hpp \
    lib/cereal/archives/portable_binary.hpp \
    lib/cereal/archives/xml.hpp \
    lib/cereal/details/helpers.hpp \
    lib/cereal/details/polymorphic_impl.hpp \
    lib/cereal/details/static_object.hpp \
    lib/cereal/details/traits.hpp \
    lib/cereal/details/util.hpp \
    lib/cereal/external/rapidjson/internal/pow10.h \
    lib/cereal/external/rapidjson/internal/stack.h \
    lib/cereal/external/rapidjson/internal/strfunc.h \
    lib/cereal/external/rapidjson/document.h \
    lib/cereal/external/rapidjson/filestream.h \
    lib/cereal/external/rapidjson/genericstream.h \
    lib/cereal/external/rapidjson/prettywriter.h \
    lib/cereal/external/rapidjson/rapidjson.h \
    lib/cereal/external/rapidjson/reader.h \
    lib/cereal/external/rapidjson/stringbuffer.h \
    lib/cereal/external/rapidjson/writer.h \
    lib/cereal/external/rapidxml/rapidxml.hpp \
    lib/cereal/external/rapidxml/rapidxml_iterators.hpp \
    lib/cereal/external/rapidxml/rapidxml_print.hpp \
    lib/cereal/external/rapidxml/rapidxml_utils.hpp \
    lib/cereal/external/base64.hpp \
    lib/cereal/types/array.hpp \
    lib/cereal/types/base_class.hpp \
    lib/cereal/types/bitset.hpp \
    lib/cereal/types/boost_variant.hpp \
    lib/cereal/types/chrono.hpp \
    lib/cereal/types/common.hpp \
    lib/cereal/types/complex.hpp \
    lib/cereal/types/deque.hpp \
    lib/cereal/types/forward_list.hpp \
    lib/cereal/types/list.hpp \
    lib/cereal/types/map.hpp \
    lib/cereal/types/memory.hpp \
    lib/cereal/types/polymorphic.hpp \
    lib/cereal/types/queue.hpp \
    lib/cereal/types/set.hpp \
    lib/cereal/types/stack.hpp \
    lib/cereal/types/string.hpp \
    lib/cereal/types/tuple.hpp \
    lib/cereal/types/unordered_map.hpp \
    lib/cereal/types/unordered_set.hpp \
    lib/cereal/types/utility.hpp \
    lib/cereal/types/valarray.hpp \
    lib/cereal/types/vector.hpp \
    lib/cereal/access.hpp \
    lib/cereal/cereal.hpp \
    lib/cereal/macros.hpp \
    lib/json/json.hpp \
    lib/easylogging++.h \
    gui/customimagegraphicsitem.h

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

