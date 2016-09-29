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
#include <vector>

//Qt
# include <QObject>
# include <QStandardItemModel>
# include <QStandardItem>

//local
# include "fluidControl/executable/ExecutableMachineGraph.h"
# include "plugin/PluginFileLoader.h"
# include "plugin/actuators/selfconfiguringplugin.h"
# include "plugin/actuators/ControlPlugin.h"
# include "plugin/actuators/ExtractorPlugin.h"
# include "plugin/actuators/InjectorPlugin.h"
# include "plugin/actuators/LightPlugin.h"
# include "plugin/actuators/MixerPlugin.h"
# include "plugin/actuators/ODSensorPlugin.h"
# include "plugin/actuators/TemperaturePlugin.h"

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

    void insertPlugin(const std::string & superclass, const std::string pluginClass, const std::string & name, SelfConfiguringPlugin* plugin);
    SelfConfiguringPlugin* getPlugin(const std::string & name);
    SelfConfiguringPlugin* makeNewPlugin(const std::string & superclass, const std::string & type, const std::unordered_map<std::string,std::string> & params) throw (std::invalid_argument);

    std::vector<QStandardItem*> getAllClassItems();
    std::vector<QStandardItem*> getAllSuperClassItems();

    void importMachine(ExecutableMachineGraph* machine);

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
    std::unordered_map<std::string, SelfConfiguringPlugin*> namePluginMap;
    std::unordered_map<std::string, SelfConfiguringPlugin*> superclassPrototypeMap;

    void createModel();
    void createPrototypes();
    int indexOfSuperClass(const std::string & superclass);
    std::string strOfSuperclass(SuperClassType superclass);
    QStandardItem* getItem(const std::string & superclass, const std::string & pluginClass);
};

#endif // PLUGINMANAGER_H
