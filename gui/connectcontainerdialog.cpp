#include "connectcontainerdialog.h"

ConnectContainerDialog::ConnectContainerDialog(std::shared_ptr<ExecutableContainerNode> source,
                                               std::shared_ptr<ExecutableContainerNode> target,
                                               QWidget* parent,
                                               Qt::WindowFlags f) :
    QDialog(parent, f)
{
    this->idSource = source->getContainerId();
    this->idTarget = target->getContainerId();

    this->sourceControl = getSourceControlActuator(source);
    this->targetControl = getTargetControlActuator(target);

    QGridLayout* mainLayout = new QGridLayout(this);

    QGroupBox* sourceBox = createSourceLayout();
    QGroupBox* targetBox = createTargetLayout();

    QPushButton* acpt = new QPushButton("Connect");
    QPushButton* cncl = new QPushButton("Cancel");

    mainLayout->addWidget(sourceBox, 0, 0);
    mainLayout->addWidget(targetBox, 0, 1);
    mainLayout->addWidget(acpt, 1, 0);
    mainLayout->addWidget(cncl, 1, 1);

    connect(acpt, SIGNAL(clicked(bool)), this, SLOT(ok()));
    connect(cncl, SIGNAL(clicked(bool)), this, SLOT(cancel()));
}

ConnectContainerDialog::~ConnectContainerDialog() {

}

void ConnectContainerDialog::ok() {
    QHashIterator<QComboBox*,int> itSource(comboSourceValveMap);
    while(itSource.hasNext()) {
        itSource.next();
        int pos = itSource.key()->currentText().toInt();
        pos += itSource.value();
        sourceControl->addConnection(idSource, idTarget, pos);
    }

    QHashIterator<QComboBox*,int> itTarget(comboTargetValveMap);
    while(itTarget.hasNext()) {
        itTarget.next();
        int pos = itTarget.key()->currentText().toInt();
        pos += itTarget.value();
        targetControl->addConnection(idSource, idTarget, pos);
    }

    accept();
}

void ConnectContainerDialog::cancel() {
    reject();
}

QGroupBox* ConnectContainerDialog::createSourceLayout() throw (std::invalid_argument) {
    QGroupBox* sourceBox;
    if (!sourceControl) {
        sourceBox = createEmptyLayout();
        sourceBox->setTitle("source control pos");
    }else if(std::dynamic_pointer_cast<ControlPlugin>(sourceControl)){
        std::shared_ptr<ControlPlugin> castSourceControl = std::dynamic_pointer_cast<ControlPlugin>(sourceControl);
        sourceBox = createControlLayout(castSourceControl, comboSourceValveMap);
        sourceBox->setTitle("source control pos");
    } else if (std::dynamic_pointer_cast<CompoundControlPlugin>(sourceControl)) {
        std::shared_ptr<CompoundControlPlugin> castSourceControl = std::dynamic_pointer_cast<CompoundControlPlugin>(sourceControl);
        sourceBox = createCompoundControlLayout(castSourceControl, comboSourceValveMap);
        sourceBox->setTitle("source control pos");
    } else {
        throw (new std::invalid_argument("connot cast source control object"));
    }
    return sourceBox;
}

QGroupBox* ConnectContainerDialog::createTargetLayout() throw (std::invalid_argument) {
    QGroupBox* targetBox;
    if (!targetControl) {
        targetBox = createEmptyLayout();
        targetBox->setTitle("target control pos");
    }else if(std::dynamic_pointer_cast<ControlPlugin>(targetControl)){
        std::shared_ptr<ControlPlugin> castTargetControl = std::dynamic_pointer_cast<ControlPlugin>(targetControl);
        targetBox = createControlLayout(castTargetControl, comboTargetValveMap);
        targetBox->setTitle("target control pos");
    } else if (std::dynamic_pointer_cast<CompoundControlPlugin>(targetControl)) {
        std::shared_ptr<CompoundControlPlugin> castTargetControl = std::dynamic_pointer_cast<CompoundControlPlugin>(targetControl);
        targetBox = createCompoundControlLayout(castTargetControl, comboTargetValveMap);
        targetBox->setTitle("target control pos");
    } else {
        throw (new std::invalid_argument("connot cast target control object"));
    }
    return targetBox;
}

std::shared_ptr<Control> ConnectContainerDialog::getSourceControlActuator(std::shared_ptr<ExecutableContainerNode> source) {
    std::shared_ptr<Control> controlActuator;
    ContainerType containerType = source->getType()->getContainerType();

    switch(containerType) {
    case ContainerType::divergent_switch : {
        std::shared_ptr<DivergentSwitch> cast = castContainer<DivergentSwitch>(source);
        controlActuator = cast->getControl();
        break;
    }case ContainerType::divergent_switch_sink : {
        std::shared_ptr<DivergentSwitchSink> cast = castContainer<DivergentSwitchSink>(source);
        controlActuator = cast->getControl();
        break;
    }case ContainerType::convergent_switch : {
        std::shared_ptr<ConvergentSwitch> cast = castContainer<ConvergentSwitch>(source);
        controlActuator = cast->getControl();
        break;
    }case ContainerType::convergent_switch_inlet : {
        std::shared_ptr<ConvergentSwitchInlet> cast = castContainer<ConvergentSwitchInlet>(source);
        controlActuator = cast->getControl();
        break;
    }case ContainerType::bidirectional_switch : {
        std::shared_ptr<BidirectionalSwitch> cast = castContainer<BidirectionalSwitch>(source);
        controlActuator = cast->getControlOut();
        break;
    }
    }
    return controlActuator;
}

std::shared_ptr<Control> ConnectContainerDialog::getTargetControlActuator(std::shared_ptr<ExecutableContainerNode> target) {
    std::shared_ptr<Control> controlActuator;
    ContainerType containerType = target->getType()->getContainerType();

    switch(containerType) {
    case ContainerType::divergent_switch : {
        std::shared_ptr<DivergentSwitch> cast = castContainer<DivergentSwitch>(target);
        controlActuator = cast->getControl();
        break;
    }case ContainerType::divergent_switch_sink : {
        std::shared_ptr<DivergentSwitchSink> cast = castContainer<DivergentSwitchSink>(target);
        controlActuator = cast->getControl();
        break;
    }case ContainerType::convergent_switch : {
        std::shared_ptr<ConvergentSwitch> cast = castContainer<ConvergentSwitch>(target);
        controlActuator = cast->getControl();
        break;
    }case ContainerType::convergent_switch_inlet : {
        std::shared_ptr<ConvergentSwitchInlet> cast = castContainer<ConvergentSwitchInlet>(target);
        controlActuator = cast->getControl();
        break;
    }case ContainerType::bidirectional_switch : {
        std::shared_ptr<BidirectionalSwitch> cast = castContainer<BidirectionalSwitch>(target);
        controlActuator = cast->getControlIn();
        break;
    }
    }
    return controlActuator;
}

QGroupBox* ConnectContainerDialog::createControlLayout(std::shared_ptr<ControlPlugin> control, QHash<QComboBox*,int> & map) {
    QGroupBox* box = new QGroupBox();
    QGridLayout* boxLayout = new QGridLayout();
    QComboBox* combo = new QComboBox();
    std::vector<int> availablePos = control->getAvailablePos();

    combo->addItem("-1");
    for (int pos: availablePos) {
        combo->addItem(QString::number(pos));
    }
    map.insert(combo, 0);

    boxLayout->addWidget(new QLabel(QString::fromStdString(control->getName()), 0, 0));
    boxLayout->addWidget(combo, 0, 1);

    box->setLayout(boxLayout);
    return box;
}

QGroupBox* ConnectContainerDialog::createCompoundControlLayout(std::shared_ptr<CompoundControlPlugin> control, QHash<QComboBox*,int> & map) throw (std::runtime_error) {
    QGroupBox* box = new QGroupBox();
    QGridLayout* boxLayout = new QGridLayout();
    QComboBox* combo = new QComboBox();
    combo->addItem("-1");

    std::vector<int> availablePos = control->getAvailablePos();
    std::shared_ptr<std::map<int, std::shared_ptr<ControlPlugin>>> virtualPosMap = control->getVirtualPosMap();

    auto it = virtualPosMap->begin();
    int lastOfset = 0;
    int offset = it->first;
    std::shared_ptr<ControlPlugin> actualControl = it->second;

    int line = 0;
    for (int pos: availablePos) {
        if (pos >= offset) {
            if (it != virtualPosMap->end()) {
                boxLayout->addWidget(new QLabel(QString::fromStdString(actualControl->getName())), line, 0);
                boxLayout->addWidget(combo, line, 1);
                map.insert(combo, lastOfset);

                ++it;
                line++;

                lastOfset = offset;
                offset = it->first;
                actualControl = it->second;

                combo = new QComboBox();
                combo->addItem("-1");
            } else {
               throw (new std::runtime_error("available position beyond max ofset"));
            }
        }
        combo->addItem(QString::number(pos - lastOfset));
    }
    boxLayout->addWidget(new QLabel(QString::fromStdString(actualControl->getName())), line, 0);
    boxLayout->addWidget(combo, line, 1);
    map.insert(combo, lastOfset);

    box->setLayout(boxLayout);
    return box;
}

QGroupBox* ConnectContainerDialog::createEmptyLayout() {
    QGridLayout* boxLayout = new QGridLayout();
    QGroupBox* box = new QGroupBox();

    boxLayout->addWidget(new QLabel("no control actuator in container", 0, 0));
    box->setLayout(boxLayout);

    return box;
}
