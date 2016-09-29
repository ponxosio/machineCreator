#include "mainwindow.h"
#include <QApplication>
#include <QTextStream>

#include "fluidControl/executable/containers/actuators/liquids/Control.h"
#include "fluidControl/executable/containers/actuators/liquids/Injector.h"
#include "fluidControl/executable/containers/actuators/liquids/Extractor.h"

#include "fluidControl/executable/containers/actuators/extras/Temperature.h"
#include "fluidControl/executable/containers/actuators/extras/ODSensor.h"
#include "fluidControl/executable/containers/actuators/extras/Light.h"
#include "fluidControl/executable/containers/actuators/extras/Mixer.h"

#include "fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h"
#include "fluidControl/executable/containers/actuators/communications/CommandSender.h"
#include "fluidControl/executable/containers/actuators/communications/FileSender.h"
#include "fluidControl/executable/containers/actuators/communications/SerialSender.h"

#include "fluidControl/executable/ExecutableMachineGraph.h"
#include "fluidControl/executable/containers/InletContainer.h"
#include "fluidControl/executable/containers/BidirectionalSwitch.h"
#include "fluidControl/executable/containers/ConvergentSwitch.h"
#include "fluidControl/executable/containers/ConvergentSwitchInlet.h"
#include "fluidControl/executable/containers/DivergentSwitch.h"
#include "fluidControl/executable/containers/DivergentSwitchSink.h"
#include "fluidControl/executable/containers/ExecutableContainerNode.h"
#include "fluidControl/executable/containers/FlowContainer.h"
#include "fluidControl/executable/containers/SinkContainer.h"

//plugins
#include "plugin/PluginFileLoader.h"
#include "plugin/PythonEnvironment.h"
#include "plugin/actuators/ODSensorPlugin.h"
#include "plugin/actuators/MixerPlugin.h"
#include "plugin/actuators/TemperaturePlugin.h"
#include "plugin/actuators/LightPlugin.h"
#include "plugin/actuators/ControlPlugin.h"
#include "plugin/actuators/ExtractorPlugin.h"
#include "plugin/actuators/InjectorPlugin.h"

#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Load configuration from file
    std::string currentDir = Utils::getCurrentDir();
    currentDir = currentDir + "\\" + "\\configuration\\log.ini";
    el::Configurations conf(currentDir);

    // Actually reconfigure all loggers instead
    el::Loggers::reconfigureAllLoggers(conf);

    //PluginFileLoader::GetInstance()->toText();

    /***************************************
     * TEST
     * ************************************/
   /* try {
        std::unique_ptr<CommandSender> test = std::unique_ptr<CommandSender>(new FileSender("test.log", "inputFileData.txt"));
        std::unique_ptr<CommandSender> exec = std::unique_ptr<CommandSender>(new SerialSender());

        int communications = 0;
        LOG(INFO) << "creating machine husk";
        ExecutableMachineGraph* machine = new ExecutableMachineGraph(
                    "simpleMachine", std::move(exec), std::move(test));

        LOG(INFO) << "creating 2 way valve";
        vector<string> paramsc{ "46" };
        std::shared_ptr<Control> control(new ControlPlugin(communications, 2, "Evoprog2WayValve", paramsc));

        LOG(INFO) << "creating pump";
        vector<string> paramsce{ "7", "1" };
        std::shared_ptr<Extractor> cExtractor13(
                    new ExtractorPlugin(communications, "EvoprogV2Pump", paramsce));

        LOG(INFO) << "creating injector";
        vector<string> paramsdi;
        std::shared_ptr<Injector> dummyInjector(
                    new InjectorPlugin(communications, "EvoprogDummyInjector", paramsdi));

        LOG(INFO) << "creating inlet";
        ExecutableMachineGraph::ExecutableContainerNodePtr cInlet1 = std::make_shared<DivergentSwitch>(1, 100.0, cExtractor13, control);
        LOG(INFO) << "creating injector";
        ExecutableMachineGraph::ExecutableContainerNodePtr sink2 = std::make_shared<SinkContainer>(2, 100.0, dummyInjector);
        LOG(INFO) << "creating injector";
        ExecutableMachineGraph::ExecutableContainerNodePtr sink3 = std::make_shared<SinkContainer>(3, 100.0, dummyInjector);

        machine->addContainer(cInlet1);
        machine->addContainer(sink2);
        machine->addContainer(sink3);

        machine->connectExecutableContainer(1, 2);
        machine->connectExecutableContainer(1, 3);

        LOG(INFO) << machine->getGraph()->toString();
    } catch (std::exception & e) {
        LOG(ERROR) << e.what();
    }

    PythonEnvironment::GetInstance()->finishEnvironment();*/

    /***************************************/

    return a.exec();
}
