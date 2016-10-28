#ifndef CONNECTCONTAINERDIALOG_H
#define CONNECTCONTAINERDIALOG_H

//std
#include <stdexcept>

//Qt
#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QHash>
#include <QHashIterator>
#include <QLabel>
#include <QPushButton>

//local
#include "fluidControl/executable/containers/actuators/liquids/Control.h"
#include "fluidControl/executable/containers/BidirectionalSwitch.h"
#include "fluidControl/executable/containers/ConvergentSwitch.h"
#include "fluidControl/executable/containers/ConvergentSwitchInlet.h"
#include "fluidControl/executable/containers/DivergentSwitch.h"
#include "fluidControl/executable/containers/DivergentSwitchSink.h"
#include "fluidControl/executable/containers/ExecutableContainerNode.h"
#include "fluidControl/machineGraph/ContainerNodeType.h"
#include "plugin/actuators/compoundcontrolplugin.h"
#include "plugin/actuators/ControlPlugin.h"


class ConnectContainerDialog : public QDialog
{
     Q_OBJECT
public:
    ConnectContainerDialog(std::shared_ptr<ExecutableContainerNode> source, std::shared_ptr<ExecutableContainerNode> target, QWidget* parent = 0, Qt::WindowFlags f = 0) ;
    virtual ~ConnectContainerDialog();

public slots:
    void ok();
    void cancel();

protected:
    int idSource;
    int idTarget;

    QHash<QComboBox*,int> comboSourceValveMap;
    QHash<QComboBox*,int> comboTargetValveMap;

    std::shared_ptr<Control> sourceControl;
    std::shared_ptr<Control> targetControl;

    QGroupBox* createSourceLayout() throw (std::invalid_argument);
    QGroupBox* createTargetLayout() throw (std::invalid_argument);

    QGroupBox* createControlLayout(std::shared_ptr<ControlPlugin> control, QHash<QComboBox*,int> & map);
    QGroupBox* createCompoundControlLayout(std::shared_ptr<CompoundControlPlugin> control, QHash<QComboBox*,int> & map) throw (std::runtime_error);
    QGroupBox* createEmptyLayout();

    std::shared_ptr<Control> getSourceControlActuator(std::shared_ptr<ExecutableContainerNode> source);
    std::shared_ptr<Control> getTargetControlActuator(std::shared_ptr<ExecutableContainerNode> target);

    template<class E>
    std::shared_ptr<E> castContainer(std::shared_ptr<ExecutableContainerNode> node) throw (std::invalid_argument) {
        std::shared_ptr<E> cast = std::dynamic_pointer_cast<E>(node);
        if (!cast) {
            throw (new std::invalid_argument("connot cast " + std::string(QString::number(node->getContainerId()).toUtf8().constData()) + " container object to " + std::string(typeid(E).name())));
        }
        return cast;
    }
};

#endif // CONNECTCONTAINERDIALOG_H
