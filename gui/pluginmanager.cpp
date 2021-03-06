#include "pluginmanager.h"

using namespace std;

PluginManager::PluginManager()
{
    this->model = new QStandardItemModel();
    createModel();
    createPrototypes();

    QObject::connect(model, &QStandardItemModel::itemChanged, this, &PluginManager::itemChanged);
}

PluginManager::~PluginManager()
{
    delete model;
}

void PluginManager::insertPlugin(const std::string & superclass, const std::string pluginClass, const std::string & name, std::shared_ptr<SelfConfiguringPlugin> plugin)
{
    QStandardItem* actual = getItem(superclass, pluginClass);
    if (actual == 0) {
        LOG(WARNING) << "empty item: " << pluginClass;
    } else {
        namePluginMap.insert(std::make_pair(name,plugin));
        actual->appendRow(new QStandardItem(QString::fromStdString(name)));
        emit indexChanged(actual->index());
    }
}

std::shared_ptr<SelfConfiguringPlugin> PluginManager::getPlugin(const std::string & name) {
    std::shared_ptr<SelfConfiguringPlugin> finded = NULL;
    auto it = namePluginMap.find(name);

    if (it != namePluginMap.end()) {
        finded = it->second;
    } else {
        LOG(WARNING) << "unexistence plugin: " << name;
    }
    return finded;
}

SelfConfiguringPlugin* PluginManager::makeNewPlugin(const std::string & name, const std::string & superclass, const std::string & type, const std::unordered_map<std::string,std::string> & params) throw (std::invalid_argument) {
    if (superclass.compare(ABSTRACT_STR) == 0) {
        SelfConfiguringPlugin* abstractPlugin = makeAbstractPlugin(name, type, params);
        if (abstractPlugin) {
            return abstractPlugin;
        } else {
            throw(new std::invalid_argument("error while creating abstract plugin: " + type));
        }
    } else {
        auto it = superclassPrototypeMap.find(superclass);
        if (it != superclassPrototypeMap.end()) {
            SelfConfiguringPlugin* newPlugin = it->second->clone();
            newPlugin->setPluginType(type);
            newPlugin->setParams(params);
            newPlugin->setName(name);
            return newPlugin;
        } else {
            throw(new std::invalid_argument(superclass + " is not a valid superClass"));
        }
    }
}

std::vector<QStandardItem*> PluginManager::getAllClassItems() {
    vector<QStandardItem*> classesIndex;
    int rowCountSuperclass = model->invisibleRootItem()->rowCount();

    for (int i = 0; i < rowCountSuperclass; i++) {
        QStandardItem* superclass = model->invisibleRootItem()->child(i);
        int rowCountclass = superclass->rowCount();
        for (int j = 0; j < rowCountclass; j++) {
            classesIndex.push_back(superclass->child(j));
        }
    }
    return classesIndex;
}

std::vector<QStandardItem*> PluginManager::getAllSuperClassItems() {
    vector<QStandardItem*> superclassesIndex;
    int rowCountSuperclass = model->invisibleRootItem()->rowCount();

    for (int i = 0; i < rowCountSuperclass; i++) {
        superclassesIndex.push_back(model->invisibleRootItem()->child(i));
    }
    return superclassesIndex;
}

void PluginManager::importMachine(ExecutableMachineGraph* machine) {
    unordered_set<std::shared_ptr<SelfConfiguringPlugin>> pluginSet;

    ExecutableMachineGraph::NodeVectorPtr nodes = machine->getGraph()->getAllNodes();
    for (ExecutableMachineGraph::NodePtr actualNode: *(nodes.get())) {
        if (std::dynamic_pointer_cast<InletContainer>(actualNode)) {
            importInlet(std::dynamic_pointer_cast<InletContainer>(actualNode), pluginSet);
        } else if (std::dynamic_pointer_cast<SinkContainer>(actualNode)) {
            importSink(std::dynamic_pointer_cast<SinkContainer>(actualNode), pluginSet);
        } else if (std::dynamic_pointer_cast<FlowContainer>(actualNode)) {
            importFlow(std::dynamic_pointer_cast<FlowContainer>(actualNode), pluginSet);
        } else if (std::dynamic_pointer_cast<ConvergentSwitch>(actualNode)) {
            importConvergentSwitch(std::dynamic_pointer_cast<ConvergentSwitch>(actualNode), pluginSet);
        } else if (std::dynamic_pointer_cast<DivergentSwitch>(actualNode)) {
            importDivergentSwitch(std::dynamic_pointer_cast<DivergentSwitch>(actualNode), pluginSet);
        } else if (std::dynamic_pointer_cast<ConvergentSwitchInlet>(actualNode)) {
            importConvergentSwitchInlet(std::dynamic_pointer_cast<ConvergentSwitchInlet>(actualNode), pluginSet);
        } else if (std::dynamic_pointer_cast<DivergentSwitchSink>(actualNode)) {
            importDivergentSwitchSink(std::dynamic_pointer_cast<DivergentSwitchSink>(actualNode), pluginSet);
        } else if (std::dynamic_pointer_cast<BidirectionalSwitch>(actualNode)) {
            importBidirectionalSwitch(std::dynamic_pointer_cast<BidirectionalSwitch>(actualNode), pluginSet);
        } else {
            LOG(ERROR) << "unrecognisable container type";
        }
    }
}

void PluginManager::clear() {
    serial.reset();
    namePluginMap.clear();
    model->clear();
    createModel();
}

//slots
void PluginManager::itemChanged(QStandardItem *item)
{
    emit indexChanged(item->index());
}

// protected methods
void PluginManager::createModel() {
    vector<string> classesNames =  PluginFileLoader::GetInstance()->getAllNames();

    QList<QStandardItem*> rowSuperclass;
    for (int i = 0; i < SuperClassType::SUPERCLASS_MAX; i++) {
        rowSuperclass << new QStandardItem(QString::fromStdString(strOfSuperclass((SuperClassType)i)));
    }

    QList<QStandardItem*> rowClass [SuperClassType::SUPERCLASS_MAX];
    for (auto it = classesNames.begin(); it != classesNames.end(); ++it) {
        string superclassStr = PluginFileLoader::GetInstance()->getSuperClass(*it);
        int index = indexOfSuperClass(superclassStr);
        if (index != -1) {
            rowClass[index] << new QStandardItem(QString::fromStdString(*it));
        }
    }
    rowClass[abstract_superclass] << new QStandardItem("compoundControl");
    rowClass[abstract_superclass] << new QStandardItem("valveControlledTwinPump");

    for (int i = 0; i < SuperClassType::SUPERCLASS_MAX; i++) {
        rowSuperclass.at(i)->appendColumn(rowClass[i]);
    }
    model->appendColumn(rowSuperclass);
}

int PluginManager::indexOfSuperClass(const std::string & superclass) {
    int index = -1;
    QString qSuperclass = QString::fromStdString(superclass);

    if (qSuperclass.compare(CONTROL_STR, Qt::CaseInsensitive) == 0) {
        index = SuperClassType::control;
    } else if (qSuperclass.compare(INJECTOR_STR, Qt::CaseInsensitive) == 0) {
        index = SuperClassType::injector;
    } else if (qSuperclass.compare(EXTRACTOR_STR, Qt::CaseInsensitive) == 0) {
        index = SuperClassType::extractor;
    } else if (qSuperclass.compare(MIXER_STR, Qt::CaseInsensitive) == 0) {
        index = SuperClassType::mixer_superclass;
    } else if (qSuperclass.compare(LIGHT_STR, Qt::CaseInsensitive) == 0) {
        index = SuperClassType::light_superclass;
    } else if (qSuperclass.compare(TEMPERATURE_STR, Qt::CaseInsensitive) == 0) {
        index = SuperClassType::temp_superclass;
    } else if (qSuperclass.compare(ODSENSOR_STR, Qt::CaseInsensitive) == 0) {
        index = SuperClassType::OD_sensor_superclass;
    } else if (qSuperclass.compare(ABSTRACT_STR, Qt::CaseInsensitive) == 0) {
        index = SuperClassType::abstract_superclass;
    } else {
        LOG(WARNING) << "unknow super class: " << superclass;
    }
    return  index;
}

std::string PluginManager::strOfSuperclass(SuperClassType superclass) {
    string str = "";
    switch (superclass) {
    case SuperClassType::control:
        str = CONTROL_STR;
        break;
    case SuperClassType::injector:
        str = INJECTOR_STR;
        break;
    case SuperClassType::extractor:
        str = EXTRACTOR_STR;
        break;
    case SuperClassType::mixer_superclass:
        str = MIXER_STR;
        break;
    case SuperClassType::light_superclass:
        str = LIGHT_STR;
        break;
    case SuperClassType::temp_superclass:
        str = TEMPERATURE_STR;
        break;
    case SuperClassType::OD_sensor_superclass:
        str = ODSENSOR_STR;
        break;
    case SuperClassType::abstract_superclass:
        str = ABSTRACT_STR;
        break;
    }
    return str;
}

void PluginManager::createPrototypes() {
    superclassPrototypeMap.insert(make_pair(CONTROL_STR, (SelfConfiguringPlugin*) new ControlPlugin()));
    superclassPrototypeMap.insert(make_pair(INJECTOR_STR, (SelfConfiguringPlugin*) new InjectorPlugin()));
    superclassPrototypeMap.insert(make_pair(EXTRACTOR_STR, (SelfConfiguringPlugin*) new ExtractorPlugin()));
    superclassPrototypeMap.insert(make_pair(TEMPERATURE_STR, (SelfConfiguringPlugin*) new TemperaturePlugin()));
    superclassPrototypeMap.insert(make_pair(LIGHT_STR, (SelfConfiguringPlugin*) new LightPlugin()));
    superclassPrototypeMap.insert(make_pair(ODSENSOR_STR, (SelfConfiguringPlugin*)new ODSensorPlugin()));
    superclassPrototypeMap.insert(make_pair(MIXER_STR, (SelfConfiguringPlugin* )new MixerPlugin()));
}

QStandardItem* PluginManager::getItem(const std::string & superclass, const std::string & pluginClass) {
    QStandardItem* finded = NULL;
    QList<QStandardItem*> superClassItem = model->findItems(QString::fromStdString(superclass));
    if (!superClassItem.empty()) {
        if (superClassItem.size() > 1) {
            LOG(WARNING) << "more than one super class with name " << superclass;
        }
        QStandardItem* actualSuperClass = superClassItem.back();
        int rowCount = actualSuperClass->rowCount();

        for (int i = 0; !finded && i < rowCount; i++) {
            QStandardItem* actual = actualSuperClass->child(i);
            if (actual->text().compare(QString::fromStdString(pluginClass)) == 0) {
                finded = actual;
            }
        }
    } else {
        LOG(ERROR) << "no superclass item " << superclass;
    }
    return finded;
}

void PluginManager::importInlet(shared_ptr<InletContainer> inlet, std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set) {
    importAddons(inlet, set);
    std::shared_ptr<SelfConfiguringPlugin> extr = extractPlugin<Extractor, ExtractorPlugin>(inlet->getExtractor());
    if (extr && set.find(extr) == set.end()) {
        set.insert(extr);
        insertPlugin(EXTRACTOR_STR, extr->getPluginType(), extr->getName(), extr);
    }
}

void PluginManager::importSink(shared_ptr<SinkContainer> sink,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set) {
    importAddons(sink, set);
    std::shared_ptr<SelfConfiguringPlugin> inj = extractPlugin<Injector, InjectorPlugin>(sink->getInjector());
    if (inj && set.find(inj) == set.end()) {
        set.insert(inj);
        insertPlugin(INJECTOR_STR, inj->getPluginType(), inj->getName(), inj);
    }
}

void PluginManager::importFlow(shared_ptr<FlowContainer> flow,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set) {
    importAddons(flow, set);
    std::shared_ptr<SelfConfiguringPlugin> extr = extractPlugin<Extractor, ExtractorPlugin>(flow->getExtractor());
    if (extr && set.find(extr) == set.end()) {
        set.insert(extr);
        insertPlugin(EXTRACTOR_STR, extr->getPluginType(), extr->getName(), extr);
    }
    std::shared_ptr<SelfConfiguringPlugin> inj = extractPlugin<Injector, InjectorPlugin>(flow->getInjector());
    if (inj && set.find(inj) == set.end()) {
        set.insert(inj);
        insertPlugin(INJECTOR_STR, inj->getPluginType(), inj->getName(), inj);
    }
}

void PluginManager::importDivergentSwitch(shared_ptr<DivergentSwitch> divergentSwitch,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set) {
    importAddons(divergentSwitch, set);
    std::shared_ptr<SelfConfiguringPlugin> extr = extractPlugin<Extractor, ExtractorPlugin>(divergentSwitch->getExtractor());
    if (extr && set.find(extr) == set.end()) {
        set.insert(extr);
        insertPlugin(EXTRACTOR_STR, extr->getPluginType(), extr->getName(), extr);
    }

    std::shared_ptr<SelfConfiguringPlugin> ctr = extractPlugin<Control, ControlPlugin>(divergentSwitch->getControl());
    if (ctr) {
        if(set.find(ctr) == set.end()) {
            set.insert(ctr);
            insertPlugin(CONTROL_STR, ctr->getPluginType(), ctr->getName(), ctr);
        }
    } else {
        ctr = extractPlugin<Control, CompoundControlPlugin>(divergentSwitch->getControl());
        if (ctr && set.find(ctr) == set.end()) {
            set.insert(ctr);
            insertAbstractPlugin(ctr->getPluginType(), ctr, set);
            insertPlugin(ABSTRACT_STR, ctr->getPluginType(), ctr->getName(), ctr);
        }
    }
}

void PluginManager::importConvergentSwitch(shared_ptr<ConvergentSwitch> convergentSwitch,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set) {
    importAddons(convergentSwitch, set);
    std::shared_ptr<SelfConfiguringPlugin> inj = extractPlugin<Injector, InjectorPlugin>(convergentSwitch->getInjector());
    if (inj && set.find(inj) == set.end()) {
        set.insert(inj);
        insertPlugin(INJECTOR_STR, inj->getPluginType(), inj->getName(), inj);
    }
    std::shared_ptr<SelfConfiguringPlugin> ctr = extractPlugin<Control, ControlPlugin>(convergentSwitch->getControl());
    if (ctr) {
        if(set.find(ctr) == set.end()) {
            set.insert(ctr);
            insertPlugin(CONTROL_STR, ctr->getPluginType(), ctr->getName(), ctr);
        }
    } else {
        ctr = extractPlugin<Control, CompoundControlPlugin>(convergentSwitch->getControl());
        if (ctr && set.find(ctr) == set.end()) {
            set.insert(ctr);
            insertAbstractPlugin(ctr->getPluginType(), ctr, set);
            insertPlugin(ABSTRACT_STR, ctr->getPluginType(), ctr->getName(), ctr);
        }
    }
}

void PluginManager::importDivergentSwitchSink(shared_ptr<DivergentSwitchSink> divergentSwitchSink,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set) {
    importAddons(divergentSwitchSink, set);
    std::shared_ptr<SelfConfiguringPlugin> extr = extractPlugin<Extractor, ExtractorPlugin>(divergentSwitchSink->getExtractor());
    if (extr && set.find(extr) == set.end()) {
        set.insert(extr);
        insertPlugin(EXTRACTOR_STR, extr->getPluginType(), extr->getName(), extr);
    }
    std::shared_ptr<SelfConfiguringPlugin> inj = extractPlugin<Injector, InjectorPlugin>(divergentSwitchSink->getInjector());
    if (inj && set.find(inj) == set.end()) {
        set.insert(inj);
        insertPlugin(INJECTOR_STR, inj->getPluginType(), inj->getName(), inj);
    }
    std::shared_ptr<SelfConfiguringPlugin> ctr = extractPlugin<Control, ControlPlugin>(divergentSwitchSink->getControl());
    if (ctr) {
        if(set.find(ctr) == set.end()) {
            set.insert(ctr);
            insertPlugin(CONTROL_STR, ctr->getPluginType(), ctr->getName(), ctr);
        }
    } else {
        ctr = extractPlugin<Control, CompoundControlPlugin>(divergentSwitchSink->getControl());
        if (ctr && set.find(ctr) == set.end()) {
            set.insert(ctr);
            insertAbstractPlugin(ctr->getPluginType(), ctr, set);
            insertPlugin(ABSTRACT_STR, ctr->getPluginType(), ctr->getName(), ctr);
        }
    }
}

void PluginManager::importConvergentSwitchInlet(shared_ptr<ConvergentSwitchInlet> convergentSwitchSink,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set) {
    importAddons(convergentSwitchSink, set);
    std::shared_ptr<SelfConfiguringPlugin> extr = extractPlugin<Extractor, ExtractorPlugin>(convergentSwitchSink->getExtractor());
    if (extr && set.find(extr) == set.end()) {
        set.insert(extr);
        insertPlugin(EXTRACTOR_STR, extr->getPluginType(), extr->getName(), extr);
    }
    std::shared_ptr<SelfConfiguringPlugin> inj = extractPlugin<Injector, InjectorPlugin>(convergentSwitchSink->getInjector());
    if (inj && set.find(inj) == set.end()) {
        set.insert(inj);
        insertPlugin(INJECTOR_STR, inj->getPluginType(), inj->getName(), inj);
    }

    std::shared_ptr<SelfConfiguringPlugin> ctr = extractPlugin<Control, ControlPlugin>(convergentSwitchSink->getControl());
    if (ctr) {
        if(set.find(ctr) == set.end()) {
            set.insert(ctr);
            insertPlugin(CONTROL_STR, ctr->getPluginType(), ctr->getName(), ctr);
        }
    } else {
        ctr = extractPlugin<Control, CompoundControlPlugin>(convergentSwitchSink->getControl());
        if (ctr && set.find(ctr) == set.end()) {
            set.insert(ctr);
            insertAbstractPlugin(ctr->getPluginType(), ctr, set);
            insertPlugin(ABSTRACT_STR, ctr->getPluginType(), ctr->getName(), ctr);
        }
    }
}

void PluginManager::importBidirectionalSwitch(shared_ptr<BidirectionalSwitch> bidirectionalswitch,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set) {
    importAddons(bidirectionalswitch, set);
    std::shared_ptr<SelfConfiguringPlugin> extr = extractPlugin<Extractor, ExtractorPlugin>(bidirectionalswitch->getExtractor());
    if (extr && set.find(extr) == set.end()) {
        set.insert(extr);
        insertPlugin(EXTRACTOR_STR, extr->getPluginType(), extr->getName(), extr);
    }
    std::shared_ptr<SelfConfiguringPlugin> inj = extractPlugin<Injector, InjectorPlugin>(bidirectionalswitch->getInjector());
    if (inj && set.find(inj) == set.end()) {
        set.insert(inj);
        insertPlugin(INJECTOR_STR, inj->getPluginType(), inj->getName(), inj);
    }

    std::shared_ptr<SelfConfiguringPlugin> ctrin = extractPlugin<Control, ControlPlugin>(bidirectionalswitch->getControlIn());
    if (ctrin) {
        if(set.find(ctrin) == set.end()) {
            set.insert(ctrin);
            insertPlugin(CONTROL_STR, ctrin->getPluginType(), ctrin->getName(), ctrin);
        }
    } else {
        ctrin = extractPlugin<Control, CompoundControlPlugin>(bidirectionalswitch->getControlIn());
        if (ctrin && set.find(ctrin) == set.end()) {
            set.insert(ctrin);
            insertAbstractPlugin(ctrin->getPluginType(), ctrin, set);
            insertPlugin(ABSTRACT_STR, ctrin->getPluginType(), ctrin->getName(), ctrin);
        }
    }

    std::shared_ptr<SelfConfiguringPlugin> ctrout = extractPlugin<Control, ControlPlugin>(bidirectionalswitch->getControlOut());
    if (ctrout) {
        if(set.find(ctrout) == set.end()) {
            set.insert(ctrout);
            insertPlugin(CONTROL_STR, ctrout->getPluginType(), ctrout->getName(), ctrout);
        }
    } else {
        ctrout = extractPlugin<Control, CompoundControlPlugin>(bidirectionalswitch->getControlOut());
        if (ctrout && set.find(ctrout) == set.end()) {
            set.insert(ctrout);
            insertAbstractPlugin(ctrout->getPluginType(), ctrout, set);
            insertPlugin(ABSTRACT_STR, ctrout->getPluginType(), ctrout->getName(), ctrout);
        }
    }
}

void PluginManager::importAddons(std::shared_ptr<ExecutableContainerNode> node,  std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set) {
    if (node->getLight()) {
        std::shared_ptr<SelfConfiguringPlugin> light = extractPlugin<Light, LightPlugin>(node->getLight());
        if (light && set.find(light) != set.end()) {
            set.insert(light);
            insertPlugin(LIGHT_STR, light->getPluginType(), light->getName(), light);
        }
    }
    if (node->getMix()) {
        std::shared_ptr<SelfConfiguringPlugin> mix = extractPlugin<Mixer, MixerPlugin>(node->getMix());
        if (mix && set.find(mix) != set.end()) {
            set.insert(mix);
            insertPlugin(MIXER_STR, mix->getPluginType(), mix->getName(), mix);
        }
    }
    if (node->getTemperature()) {
        std::shared_ptr<SelfConfiguringPlugin> temp = extractPlugin<Temperature, TemperaturePlugin>(node->getTemperature());
        if (temp && set.find(temp) != set.end()) {
            set.insert(temp);
            insertPlugin(TEMPERATURE_STR, temp->getPluginType(), temp->getName(), temp);
        }
    }
    if (node->getOd()) {
        std::shared_ptr<SelfConfiguringPlugin> od = extractPlugin<ODSensor, ODSensorPlugin>(node->getOd());
        if (od && set.find(od) != set.end()) {
            set.insert(od);
            insertPlugin(ODSENSOR_STR, od->getPluginType(), od->getName(), od);
        }
    }
}

SelfConfiguringPlugin* PluginManager::makeAbstractPlugin(const std::string & name, const std::string & pluginType, const std::unordered_map<std::string,std::string> & params) {
    if (pluginType.compare("compoundControl") == 0) {
        std::vector<std::shared_ptr<ControlPlugin>> controls;
        auto valves = params.find("list_of_controls");

        if (valves != params.end()) {
            QString value = QString::fromStdString(valves->second);
            QStringList tokens = value.split(';');

            for (QString pluginName : tokens) {
                std::shared_ptr<ControlPlugin> plugin = std::static_pointer_cast<ControlPlugin>(getPlugin(pluginName.toUtf8().constData()));
                controls.push_back(plugin);
            }

            CompoundControlPlugin* compoundValve = new CompoundControlPlugin(-1, name, params,controls);
            return compoundValve;
        }
    } else if (pluginType.compare("valveControlledTwinPump") == 0) {
        auto pump1 = params.find("pump1");
        auto pump2 = params.find("pump2");
        auto control = params.find("controlActuator");
        auto positions = params.find("positionsPump1Works");

        if (pump1 != params.end() &&
            pump2 != params.end() &&
            control != params.end() &&
            positions != params.end())
        {
            std::vector<int> positionsVextor;
            std::shared_ptr<ExtractorPlugin> pump1Plugin =  std::static_pointer_cast<ExtractorPlugin>(getPlugin(pump1->second));
            std::shared_ptr<ExtractorPlugin> pump2Plugin =  std::static_pointer_cast<ExtractorPlugin>(getPlugin(pump2->second));
            std::shared_ptr<ControlPlugin> controlPlugin =  std::static_pointer_cast<ControlPlugin>(getPlugin(control->second));

            QString positionsQs = QString::fromStdString(positions->second);
            QStringList tokens = positionsQs.split(';');
            for (QString pos: tokens) {
                positionsVextor.push_back(pos.toInt());
            }

            ValveControlledTwinPump* pumps = new ValveControlledTwinPump(-1, name, params, pump1Plugin, pump2Plugin, controlPlugin, positionsVextor);
            return pumps;
        }
    }
    return NULL;
}

void PluginManager::insertAbstractPlugin(const std::string pluginClass, std::shared_ptr<SelfConfiguringPlugin> plugin, std::unordered_set<std::shared_ptr<SelfConfiguringPlugin>> & set) {
    if (pluginClass.compare("compoundControl") == 0) {
        std::shared_ptr<CompoundControlPlugin> cast = std::dynamic_pointer_cast<CompoundControlPlugin>(plugin);
        std::shared_ptr<std::map<int, std::shared_ptr<ControlPlugin>>> valves = cast->getVirtualPosMap();

        for (auto it = valves->begin(); it != valves->end(); ++it) {
            if (it->second && set.find(it->second) == set.end()) {
                set.insert(it->second);
                insertPlugin(CONTROL_STR, it->second->getPluginType(), it->second->getName(), it->second);
            }
        }
    }
}
