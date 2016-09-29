#include "newcontainerdialog.h"

NewContainerDialog::NewContainerDialog(GraphicsManager* manager, PluginManager* pluginManager, QWidget* parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    this->manager = manager;
    this->pluginManager = pluginManager;
    this->actualType = INLET_NAME;

    descriptionTextBox = new QTextEdit(this);
    descriptionTextBox->setReadOnly(true);
    descriptionTextBox->setMinimumHeight(220);
    descriptionTextBox->setMinimumWidth(120);
    setDescription(INLET_NAME);

    mixerEdit = new QLineEdit(this);
    mixerEdit->setReadOnly(true);
    lightEdit = new QLineEdit(this);
    lightEdit->setReadOnly(true);
    temperatureEdit = new QLineEdit(this);
    temperatureEdit->setReadOnly(true);
    odSensorEdit = new QLineEdit(this);
    odSensorEdit->setReadOnly(true);
    nameEdit = new QLineEdit(this);
    capacityEdit = new QLineEdit(this);

    acceptBtn = new QPushButton("accept", this);

    QPushButton* cancelBtn = new QPushButton("cancel", this);

    IdEmitingPushButton* mixerBtn = new IdEmitingPushButton(MIXER_BTN_ID, "mixer search", QIcon( QPixmap("ico/find.png")),this);
    IdEmitingPushButton* lightBtn = new IdEmitingPushButton(LIGHT_BTN_ID, "light search", QIcon( QPixmap("ico/find.png")),this);
    IdEmitingPushButton* temperatureBtn = new IdEmitingPushButton(TEMPERATURE_BTN_ID, "temperature search", QIcon( QPixmap("ico/find.png")),this);
    IdEmitingPushButton* odSensorBtn = new IdEmitingPushButton(ODSENSOR_BTN_ID, "od sensor search", QIcon( QPixmap("ico/find.png")),this);

    QGroupBox* addonsBox = new QGroupBox("addons", this);
    QGridLayout* addonsLayout = new QGridLayout(this);
    addonsLayout->addWidget(new QLabel("mixer: "), 0, 0);
    addonsLayout->addWidget(mixerEdit, 0, 1);
    addonsLayout->addWidget(mixerBtn, 0, 2);

    addonsLayout->addWidget(new QLabel("light: "), 1, 0);
    addonsLayout->addWidget(lightEdit, 1, 1);
    addonsLayout->addWidget(lightBtn, 1, 2);

    addonsLayout->addWidget(new QLabel("temperature: "), 2,0);
    addonsLayout->addWidget(temperatureEdit, 2,1);
    addonsLayout->addWidget(temperatureBtn, 2,2);

    addonsLayout->addWidget(new QLabel("od sensor: "), 3,0);
    addonsLayout->addWidget(odSensorEdit, 3,1);
    addonsLayout->addWidget(odSensorBtn, 3,2);
    addonsBox->setLayout(addonsLayout);

    typeCombo = new QComboBox(this);
    populateComboBox();

    actualGroupbox = new QGroupBox(this);
    actualLayout = new QGridLayout(this);
    createLayout(INLET_NAME);
    actualGroupbox->setLayout(actualLayout);

    QGroupBox* nameBox = new QGroupBox(this);
    QGridLayout* nameLayout = new QGridLayout(this);
    nameLayout->addWidget(new QLabel("name: ", this), 0, 0);
    nameLayout->addWidget(nameEdit, 0, 1);
    nameLayout->addWidget(new QLabel("capacity: ", this), 1, 0);
    nameLayout->addWidget(capacityEdit, 1, 1);
    nameBox->setLayout(nameLayout);

    QGroupBox* editBox = new QGroupBox("properties", this);
    QGridLayout* editLayout = new QGridLayout(this);
    editLayout->addWidget(nameBox, 0, 0);
    editLayout->addWidget(actualGroupbox, 1, 0);
    editBox->setLayout(editLayout);

    QGridLayout* dialogLayout = new QGridLayout(this);
    dialogLayout->addWidget(descriptionTextBox, 0, 0);
    dialogLayout->addWidget(typeCombo, 0, 1);
    dialogLayout->addWidget(editBox, 1, 0);
    dialogLayout->addWidget(addonsBox, 1, 1);
    dialogLayout->addWidget(acceptBtn, 2, 0);
    dialogLayout->addWidget(cancelBtn, 2, 1);

    setLayout(dialogLayout);

    connect(acceptBtn, SIGNAL(clicked(bool)), this, SLOT(done()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancel()));
    connect(typeCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(itemChanged(QString)));
    connect(mixerBtn, SIGNAL(clicked_id(int)), this, SLOT(idButtonPress(int)));
    connect(lightBtn, SIGNAL(clicked_id(int)), this, SLOT(idButtonPress(int)));
    connect(temperatureBtn, SIGNAL(clicked_id(int)), this, SLOT(idButtonPress(int)));
    connect(odSensorBtn, SIGNAL(clicked_id(int)), this, SLOT(idButtonPress(int)));
}

NewContainerDialog::~NewContainerDialog() {

}

//slots

void NewContainerDialog::done()
{
    if (createNewContainer(actualType)) {
        accept();
    } else {
        QMessageBox::critical(this, "error", "error while creating a new container, check the log");
    }
}

void NewContainerDialog::cancel()
{
    reject();
}

void NewContainerDialog::itemChanged(const QString & text)
{
    actualType = text;
    setDescription(actualType);
    clearsActualLayout();
    createLayout(actualType);
}

void NewContainerDialog::idButtonPress(int id)
{
    PluginManagerDialog* managerDialog = new PluginManagerDialog(pluginManager,this);
    if (managerDialog->exec() == QDialog::Accepted) {
        if (id < 0) {
            switch(id) {
            case MIXER_BTN_ID:
                mixerEdit->setText(QString::fromStdString(managerDialog->getSelectedPlugin()));
                break;
            case LIGHT_BTN_ID:
                lightEdit->setText(QString::fromStdString(managerDialog->getSelectedPlugin()));
                break;
            case TEMPERATURE_BTN_ID:
                temperatureEdit->setText(QString::fromStdString(managerDialog->getSelectedPlugin()));
                break;
            case ODSENSOR_BTN_ID:
                odSensorEdit->setText(QString::fromStdString(managerDialog->getSelectedPlugin()));
                break;
            }
        } else {
            auto finded = buttonIdLineEditMap.find(id);
            if (finded != buttonIdLineEditMap.end()) {
                finded->second->setText(QString::fromStdString(managerDialog->getSelectedPlugin()));
            } else {
                LOG(WARNING) << "buttom key unknow " << id;
            }
        }
    }
    delete managerDialog;
}

//protected

void NewContainerDialog::createLayout(const QString & type) {
    AutoEnumerate serial;

    QStringList outTypes;
    outTypes << INLET_NAME << FLOW_NAME << DIVERGENT_SWITCH_NAME << DIVERGENT_SWITCH_SINK_NAME << CONV_SWITCH_INLET_NAME << BIDIRECTIONAL_SWITCH_NAME;

    QStringList inTypes;
    inTypes << SINK_NAME << FLOW_NAME << CONVERGENT_SWITCH_NAME << CONV_SWITCH_INLET_NAME << DIVERGENT_SWITCH_SINK_NAME << BIDIRECTIONAL_SWITCH_NAME;

    QStringList ctrl1Types;
    ctrl1Types << CONVERGENT_SWITCH_NAME << DIVERGENT_SWITCH_NAME << CONV_SWITCH_INLET_NAME << DIVERGENT_SWITCH_SINK_NAME << BIDIRECTIONAL_SWITCH_NAME;

    buttonIdLineEditMap.clear();
    if (outTypes.contains(type)) {
        createPluginInput(serial.getNextValue(), EXTRACTOR_NAME);
    }

    if (inTypes.contains(type)) {
        createPluginInput(serial.getNextValue(), INJECTOR_NAME);
    }

    if (ctrl1Types.contains(type)) {
        createPluginInput(serial.getNextValue(), CONTROL_1_NAME);
    }

    if (type.compare(BIDIRECTIONAL_SWITCH_NAME) == 0) {
        createPluginInput(serial.getNextValue(), CONTROL_2_NAME);
    }
    actualLayout->update();
}

void NewContainerDialog::createPluginInput(int actualSerial, const std::string & name) {
    IdEmitingPushButton* extractorBtn = new IdEmitingPushButton(actualSerial, QString::fromStdString(name), QIcon( QPixmap("ico/find.png")),this);

    QLineEdit* extractorEdit = new QLineEdit(this);
    extractorEdit->setReadOnly(true);

    actualLayout->addWidget(new QLabel(QString::fromStdString(name), this), actualSerial, 0);
    actualLayout->addWidget(extractorEdit, actualSerial, 1);
    actualLayout->addWidget(extractorBtn, actualSerial, 2);

    buttonIdLineEditMap.insert(make_pair(actualSerial, extractorEdit));
    pluginLineEditMap.insert(make_pair(name, extractorEdit));

    connect(extractorBtn, SIGNAL(clicked_id(int)), this, SLOT(idButtonPress(int)));
}

void NewContainerDialog::populateComboBox()
{
    typeCombo->addItem(INLET_NAME);
    typeCombo->addItem(SINK_NAME);
    typeCombo->addItem(FLOW_NAME);
    typeCombo->addItem(DIVERGENT_SWITCH_NAME);
    typeCombo->addItem(CONVERGENT_SWITCH_NAME);
    typeCombo->addItem(DIVERGENT_SWITCH_SINK_NAME);
    typeCombo->addItem(CONV_SWITCH_INLET_NAME);
    typeCombo->addItem(BIDIRECTIONAL_SWITCH_NAME);
}

void NewContainerDialog::clearsActualLayout() {
    QLayoutItem *child;
    while ((child = actualLayout->takeAt(0)) != 0) {
        if (child->widget()) {
            QWidget* actual = child->widget();
            actual->setVisible(false);
        }
        actualLayout->removeItem(child);
        delete child;
    }
}

void NewContainerDialog::setDescription(const QString & type) {
    if (type.compare(INLET_NAME) == 0) {
        setInletDescription();
    } else if (type.compare(SINK_NAME) == 0) {
        setSinkDescription();
    } else if (type.compare(FLOW_NAME) == 0) {
        setFlowDescription();
    } else if (type.compare(CONVERGENT_SWITCH_NAME) == 0) {
        setConvergentSwitchDescription();
    } else if (type.compare(DIVERGENT_SWITCH_NAME) == 0) {
        setDivergentSwitchDescription();
    } else if (type.compare(DIVERGENT_SWITCH_SINK_NAME) == 0) {
        setDivergentSwitchSinkDescription();
    } else if (type.compare(CONV_SWITCH_INLET_NAME) == 0) {
        setConvergentSwitchInletDescription();
    } else if (type.compare(BIDIRECTIONAL_SWITCH_NAME) == 0) {
        setBidirectionalSwitchDescription();
    } else {
        descriptionTextBox->setHtml("unknow description");
    }
}

void NewContainerDialog::setInletDescription() {
    descriptionTextBox->setHtml("<p> <img src=\"Img/inlet.png\"/> </p><p> Liquid can be extracted from this container to only one other container</p>");
}

void NewContainerDialog::setSinkDescription() {
    descriptionTextBox->setHtml("<p> <img src=\"Img/sink.png\"/> </p><p>Liquid can be inserted into this container from only one other container </p>");
}

void NewContainerDialog::setFlowDescription() {
    descriptionTextBox->setHtml("<p> <img src=\"Img/flow.png\"/> </p><p> Liquid can be inserted into this container from only one other container, also liquid can be extracted from this container to only one other container </p>");
}

void NewContainerDialog::setConvergentSwitchDescription() {
    descriptionTextBox->setHtml("<p> <img src=\"Img/convergentswitch.png\"/> </p><p> Liquid can be inserted into this container from several other containers (one at a time) </p>");
}

void NewContainerDialog::setDivergentSwitchDescription() {
    descriptionTextBox->setHtml("<p> <img src=\"Img/divergentswitch.png\"/> </p><p>Liquid can be extracted from this container to several other containers (one at a time) </p>");
}

void NewContainerDialog::setDivergentSwitchSinkDescription() {
    descriptionTextBox->setHtml("<p> <img src=\"Img/divergentswitchsink.png\"/> </p><p>Liquid can be extracted from this container to several other containers (one at a time), also liquid can be inserted into this container from only one other container </p>");
}

void NewContainerDialog::setConvergentSwitchInletDescription() {
    descriptionTextBox->setHtml("<p> <img src=\"Img/convergentswitchinlet.png\"/> </p><p>Liquid can be inserted into this container from several other containers (one at a time), also liquid can be extracted from this container to only one other container </p>");
}

void NewContainerDialog::setBidirectionalSwitchDescription() {
    descriptionTextBox->setHtml("<p> <img src=\"Img/bidirectionalswitch.png\"/> </p><p>Liquid can be inserted into this container from several other containers (one at a time), also liquid can be extracted from this container to several other containers (one at a time) </p>");
}

 bool NewContainerDialog::createNewContainer(const QString & type) {
     bool correctExecution = false;
     ExecutableContainerNode* nodeCreated = NULL;

     bool ok;
     float capacity = capacityEdit->text().toFloat(&ok);
     if (!ok) {
         LOG(ERROR) << "capacity is not a real number";
     } else {
         if (type.compare(INLET_NAME) == 0) {
             nodeCreated = createInlet(capacity);
         } else if (type.compare(SINK_NAME) == 0) {
             nodeCreated = createSink(capacity);
         } else if (type.compare(FLOW_NAME) == 0) {
             nodeCreated = createFlow(capacity);
         } else if (type.compare(CONVERGENT_SWITCH_NAME) == 0) {
             nodeCreated = createConvergentSwitch(capacity);
         } else if (type.compare(DIVERGENT_SWITCH_NAME) == 0) {
             nodeCreated = createDivergentSwitch(capacity);
         } else if (type.compare(DIVERGENT_SWITCH_SINK_NAME) == 0) {
             nodeCreated = createDivergentSwitchSink(capacity);
         } else if (type.compare(CONV_SWITCH_INLET_NAME) == 0) {
             nodeCreated = createConvergentSwitchInlet(capacity);
         } else if (type.compare(BIDIRECTIONAL_SWITCH_NAME) == 0) {
             nodeCreated = createBidirectionalSwitch(capacity);
         } else {
             LOG(ERROR) << "unknow type " << type.toUtf8().constData();
         }

         if (nodeCreated) {
             std::string name = nameEdit->text().toUtf8().constData();
             setAddons(nodeCreated);
             manager->addContainer(name, std::shared_ptr<ExecutableContainerNode>(nodeCreated));
             correctExecution = true;
         }
     }
     return correctExecution;
 }

 ExecutableContainerNode* NewContainerDialog::createInlet(float capacity) {
     ExecutableContainerNode* container = NULL;
     ExtractorPlugin* extr = extractPlugin<ExtractorPlugin>(EXTRACTOR_NAME);
     if (extr) {
         container = new InletContainer(-1, capacity, std::shared_ptr<Extractor>(extr));
     }
     return container;
 }

 ExecutableContainerNode* NewContainerDialog::createSink(float capacity) {
     ExecutableContainerNode* container = NULL;
     InjectorPlugin* inj = extractPlugin<InjectorPlugin>(INJECTOR_NAME);
     if (inj) {
        container = new SinkContainer(-1, capacity, std::shared_ptr<Injector>(inj));
     }
     return container;
 }

 ExecutableContainerNode* NewContainerDialog::createFlow(float capacity) {
     ExecutableContainerNode* container = NULL;
     ExtractorPlugin* extr = extractPlugin<ExtractorPlugin>(EXTRACTOR_NAME);
     InjectorPlugin* inj = extractPlugin<InjectorPlugin>(INJECTOR_NAME);
     if (inj && extr) {
        container = new FlowContainer(-1, capacity,std::shared_ptr<Extractor>(extr), std::shared_ptr<Injector>(inj));
     }
     return container;
 }

 ExecutableContainerNode* NewContainerDialog::createDivergentSwitch(float capacity) {
     ExecutableContainerNode* container = NULL;
     ExtractorPlugin* extr = extractPlugin<ExtractorPlugin>(EXTRACTOR_NAME);
     ControlPlugin* ctr = extractPlugin<ControlPlugin>(CONTROL_1_NAME);
     if (extr && ctr) {
        container = new DivergentSwitch(-1, capacity, std::shared_ptr<Extractor>(extr), std::shared_ptr<Control>(ctr));
     }
     return container;
 }

 ExecutableContainerNode* NewContainerDialog::createConvergentSwitch(float capacity) {
     ExecutableContainerNode* container = NULL;
     InjectorPlugin* inj = extractPlugin<InjectorPlugin>(INJECTOR_NAME);
     ControlPlugin* ctr = extractPlugin<ControlPlugin>(CONTROL_1_NAME);
     if (inj && ctr) {
        container = new ConvergentSwitch(-1, capacity, std::shared_ptr<Injector>(inj), std::shared_ptr<Control>(ctr));
     }
     return container;
 }

 ExecutableContainerNode* NewContainerDialog::createDivergentSwitchSink(float capacity) {
     ExecutableContainerNode* container = NULL;
     ExtractorPlugin* extr = extractPlugin<ExtractorPlugin>(EXTRACTOR_NAME);
     InjectorPlugin* inj = extractPlugin<InjectorPlugin>(INJECTOR_NAME);
     ControlPlugin* ctr = extractPlugin<ControlPlugin>(CONTROL_1_NAME);
     if (extr && ctr && inj) {
        container = new DivergentSwitchSink(-1, capacity,std::shared_ptr<Injector>(inj), std::shared_ptr<Extractor>(extr), std::shared_ptr<Control>(ctr));
     }
     return container;
 }

 ExecutableContainerNode* NewContainerDialog::createConvergentSwitchInlet(float capacity) {
     ExecutableContainerNode* container = NULL;
     ExtractorPlugin* extr = extractPlugin<ExtractorPlugin>(EXTRACTOR_NAME);
     InjectorPlugin* inj = extractPlugin<InjectorPlugin>(INJECTOR_NAME);
     ControlPlugin* ctr = extractPlugin<ControlPlugin>(CONTROL_1_NAME);
     if (extr && ctr && inj) {
        container = new ConvergentSwitchInlet(-1, capacity,std::shared_ptr<Injector>(inj), std::shared_ptr<Extractor>(extr), std::shared_ptr<Control>(ctr));
     }
     return container;
 }

 ExecutableContainerNode* NewContainerDialog::createBidirectionalSwitch(float capacity) {
     ExecutableContainerNode* container = NULL;
     ExtractorPlugin* extr = extractPlugin<ExtractorPlugin>(EXTRACTOR_NAME);
     InjectorPlugin* inj = extractPlugin<InjectorPlugin>(INJECTOR_NAME);
     ControlPlugin* ctr = extractPlugin<ControlPlugin>(CONTROL_1_NAME);
     ControlPlugin* ctr2 = extractPlugin<ControlPlugin>(CONTROL_1_NAME);
     if (extr && ctr && ctr2 && inj) {
        container = new BidirectionalSwitch(-1, capacity,std::shared_ptr<Extractor>(extr), std::shared_ptr<Injector>(inj), std::shared_ptr<Control>(ctr), std::shared_ptr<Control>(ctr2));
     }
     return container;
 }

 void NewContainerDialog::setAddons(ExecutableContainerNode* node) {
     if (!mixerEdit->text().isEmpty()) {
         MixerPlugin* mixerAddon = static_cast<MixerPlugin*>(pluginManager->getPlugin(mixerEdit->text().toUtf8().constData()));
         if (mixerAddon) {
            node->setMix(std::shared_ptr<Mixer>(mixerAddon));
         } else {
             LOG(ERROR) << "wrong cast to " << mixerEdit->text().toUtf8().constData();
         }
     }
     if (!lightEdit->text().isEmpty()) {
         LightPlugin* lightAddon = static_cast<LightPlugin*>(pluginManager->getPlugin(lightEdit->text().toUtf8().constData()));
         if (lightAddon) {
            node->setLight(std::shared_ptr<Light>(lightAddon));
         } else {
             LOG(ERROR) << "wrong cast to " << lightEdit->text().toUtf8().constData();
         }
     }
     if (!temperatureEdit->text().isEmpty()) {
         TemperaturePlugin* tempAddon = static_cast<TemperaturePlugin*>(pluginManager->getPlugin(temperatureEdit->text().toUtf8().constData()));
         if (tempAddon) {
            node->setTemperature(std::shared_ptr<Temperature>(tempAddon));
         } else {
             LOG(ERROR) << "wrong cast to " << temperatureEdit->text().toUtf8().constData();
         }
     }
     if (!odSensorEdit->text().isEmpty()) {
         ODSensorPlugin* odAddon = static_cast<ODSensorPlugin*>(pluginManager->getPlugin(odSensorEdit->text().toUtf8().constData()));
         if (odAddon) {
            node->setOd(std::shared_ptr<ODSensor>(odAddon));
         } else {
             LOG(ERROR) << "wrong cast to " << odSensorEdit->text().toUtf8().constData();
         }
     }
 }

