#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#define CONTROL_STR "Control"
#define INJECTOR_STR "Injector"
#define EXTRACTOR_STR "Extractor"
#define MIXER_STR "Mixer"
#define LIGHT_STR "Light"
#define TEMPERATURE_STR "Temperature"
#define ODSENSOR_STR "OdSensor"

#include <unordered_map>
#include <unordered_set>
#include <vector>

//Qt
# include <QObject>
# include <QStandardItemModel>
# include <QStandardItem>

//local
# include "fluidControl/executable/ExecutableMachineGraph.h"
# include "fluidControl/executable/containers/ExecutableContainerNode.h"
# include "fluidControl/executable/containers/InletContainer.h"
# include "fluidControl/executable/containers/SinkContainer.h"
# include "fluidControl/executable/containers/FlowContainer.h"
# include "fluidControl/executable/containers/DivergentSwitch.h"
# include "fluidControl/executable/containers/ConvergentSwitch.h"
# include "fluidControl/executable/containers/DivergentSwitchSink.h"
# include "fluidControl/executable/containers/ConvergentSwitchInlet.h"
# include "fluidControl/executable/containers/BidirectionalSwitch.h"
# include "plugin/PluginFileLoader.h"
# include "plugin/actuators/selfconfiguringplugin.h"
# include "plugin/actuators/ControlPlugin.h"
# include "plugin/actuators/ExtractorPlugin.h"
# include "plugin/actuators/InjectorPlugin.h"
# include "plugin/actuators/LightPlugin.h"
# include "plugin/actuators/MixerPlugin.h"
# include "plugin/actuators/ODSensorPlugin.h"
# include "plugin/actuators/TemperaturePlugin.h"
# include "util/Patch.h"

/*** Enum for the superclass of the plugins ***/
typedef enum SuperClassType_ {
    control,
    injector,
    extractor,
    mixer_superclass,	// addon that stir a liquid
    light_superclass,	// addon that apply light
    temp_superclass,  // addon that heat/cold a liquid
    OD_sensor_superclass, // addon that reads Optical density
    SUPERCLASS_MAX = OD_sensor_superclass + 1 // Max number of Addons ALWAYS EQUALS TO THE SECOND-TO-LAST TYPE PLUS ONE
} SuperClassType;

/**
 * @brief The PluginManager class stores the user created plugins
 */
class PluginManager : public QObject
{
    Q_OBJECT

public:
    PluginManager();
    virtual ~PluginManager();

    void insertPlugin(const std::string & superclass, const std::string pluginClass, const std::string & name, std::shared_ptr<SelfConfiguringPlugin> plugin);
    std::shared_ptr<SelfConfiguringPlugin> getPlugin(const std::string & name);
    SelfConfiguringPlugin* makeNewPlugin(const std::string & superclass, const std::string & type, const std::unordered_map<std::string,std::string> & params) throw (std::invalid_argument);

    std::vector<QStandardItem*> getAllClassItems();
    std::vector<QStandardItem*> getAllSuperClassItems();

    void importMachine(ExecutableMachineGraph* machine);

    void clear();
    //getters & setters
    inline QStandardItemModel* getModel() {
        return model;
    }
signals:
    void indexChanged(const QModelIndex &index);

public slots:
    void itemChanged(QStandardItem *item);

protected:
    QStandardItemModel* model;
    std::unordered_map<std::string, std::shared_ptr<SelfConfiguringPlugin>> namePluginMap;
    std::unordered_map<std::string, SelfConfiguringPlugin*> superclassPrototypeMap;
    AutoEnumerate serial;

    void createModel();
    void createPrototypes();
    int indexOfSuperClass(const std::string & superclass);
    std::string strOfSuperclass(SuperClassType superclass);
    QStandardItem* getItem(const std::string & superclass, const std::string & pluginClass);

    void importInlet(shared_ptr<InletContainer> inlet, std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set);
    void importSink(shared_ptr<SinkContainer> sink,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set);
    void importFlow(shared_ptr<FlowContainer> flow,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set);
    void importDivergentSwitch(shared_ptr<DivergentSwitch> divergentSwitch,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set);
    void importConvergentSwitch(shared_ptr<ConvergentSwitch> convergentSwitch,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set);
    void importDivergentSwitchSink(shared_ptr<DivergentSwitchSink> divergentSwitchSink,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set);
    void importConvergentSwitchInlet(shared_ptr<ConvergentSwitchInlet> convergentSwitchSink,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set);
    void importBidirectionalSwitch(shared_ptr<BidirectionalSwitch> bidirectionalswitch,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set);
    void importAddons(std::shared_ptr<ExecutableContainerNode> node,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set);

    template<class T, class E>
    std::shared_ptr<SelfConfiguringPlugin> extractPlugin(std::shared_ptr<T> plugin) {
        if (std::dynamic_pointer_cast<E>(plugin)) {
            std::shared_ptr<E> e = std::dynamic_pointer_cast<E>(plugin);
            return std::static_pointer_cast<SelfConfiguringPlugin>(e);
        } else {
            return std::shared_ptr<SelfConfiguringPlugin>();
        }
    }
};

#endif // PLUGINMANAGER_H
