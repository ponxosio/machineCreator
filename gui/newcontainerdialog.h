#ifndef NEWCONTAINERDIALOG_H
#define NEWCONTAINERDIALOG_H

# define MIXER_BTN_ID -1
# define LIGHT_BTN_ID -2
# define TEMPERATURE_BTN_ID -3
# define ODSENSOR_BTN_ID -4

# define EXTRACTOR_NAME "extractor"
# define INJECTOR_NAME "injector"
# define CONTROL_1_NAME "control1"
# define CONTROL_2_NAME "control2"

#include <unordered_map>

//Qt
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QComboBox>
#include <QTextEdit>
#include <QStringList>
#include <QMessageBox>

//local
# include "graphicsmanager.h"
# include "pluginmanager.h"
# include "pluginmanagerdialog.h"
# include "idemitingpushbutton.h"
# include "fluidControl/executable/containers/ExecutableContainerNode.h"
# include "fluidControl/executable/containers/InletContainer.h"
# include "fluidControl/executable/containers/SinkContainer.h"
# include "fluidControl/executable/containers/FlowContainer.h"
# include "fluidControl/executable/containers/DivergentSwitch.h"
# include "fluidControl/executable/containers/ConvergentSwitch.h"
# include "fluidControl/executable/containers/DivergentSwitchSink.h"
# include "fluidControl/executable/containers/ConvergentSwitchInlet.h"
# include "fluidControl/executable/containers/BidirectionalSwitch.h"
# include "fluidControl/machineGraph/ContainerNodeType.h"
# include "fluidControl/executable/containers/actuators/liquids/Extractor.h"
# include "fluidControl/executable/containers/actuators/liquids/Injector.h"
# include "fluidControl/executable/containers/actuators/liquids/Control.h"
# include "fluidControl/executable/containers/actuators/extras/Light.h"
# include "fluidControl/executable/containers/actuators/extras/Mixer.h"
# include "fluidControl/executable/containers/actuators/extras/Temperature.h"
# include "fluidControl/executable/containers/actuators/extras/ODSensor.h"
# include "plugin/actuators/ExtractorPlugin.h"
# include "plugin/actuators/InjectorPlugin.h"
# include "plugin/actuators/ControlPlugin.h"
# include "plugin/actuators/MixerPlugin.h"
# include "plugin/actuators/ODSensorPlugin.h"
# include "plugin/actuators/LightPlugin.h"
# include "plugin/actuators/TemperaturePlugin.h"
# include "util/AutoEnumerate.h"

class NewContainerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewContainerDialog(GraphicsManager* manager, PluginManager* pluginManager, QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~NewContainerDialog();

signals:

protected slots:
    void done();
    void cancel();
    void itemChanged(const QString & text);
    void idButtonPress(int id);

protected:
    GraphicsManager* manager;
    PluginManager* pluginManager;
    QString actualType;
    std::unordered_map<std::string, QLineEdit*> pluginLineEditMap;
    std::unordered_map<int, QLineEdit*> buttonIdLineEditMap;

    //gui attributes
    QComboBox* typeCombo;
    QGroupBox* actualGroupbox;
    QGridLayout* actualLayout;
    QPushButton* acceptBtn;
    QTextEdit* descriptionTextBox;
    QLineEdit* mixerEdit;
    QLineEdit* lightEdit;
    QLineEdit* temperatureEdit;
    QLineEdit* odSensorEdit;
    QLineEdit* nameEdit;
    QLineEdit* capacityEdit;

    void clearsActualLayout();
    void createLayout(const QString & type);
    void createPluginInput(int actualSerial, const std::string & name);

    void populateComboBox();

    void setDescription(const QString & type);
    void setInletDescription();
    void setSinkDescription();
    void setFlowDescription();
    void setConvergentSwitchDescription();
    void setDivergentSwitchDescription();
    void setDivergentSwitchSinkDescription();
    void setConvergentSwitchInletDescription();
    void setBidirectionalSwitchDescription();

    //container
    bool createNewContainer(const QString & type);
    void setAddons(ExecutableContainerNode* node);
    ExecutableContainerNode* createInlet(float capacity);
    ExecutableContainerNode* createSink(float capacity);
    ExecutableContainerNode* createFlow(float capacity);
    ExecutableContainerNode* createDivergentSwitch(float capacity);
    ExecutableContainerNode* createConvergentSwitch(float capacity);
    ExecutableContainerNode* createDivergentSwitchSink(float capacity);
    ExecutableContainerNode* createConvergentSwitchInlet(float capacity);
    ExecutableContainerNode* createBidirectionalSwitch(float capacity);

    template<class T>
    T* extractPlugin(const std::string & param) {
        auto finded = pluginLineEditMap.find(param);
        if (finded != pluginLineEditMap.end()) {
            std::string pluginName = finded->second->text().toUtf8().constData();
            SelfConfiguringPlugin* plugin = pluginManager->getPlugin(pluginName);
            return static_cast<T*>(plugin);
        } else {
            LOG(ERROR) << "no line edit with name " << param;
            return NULL;
        }
    }
};

#endif // NEWCONTAINERDIALOG_H
