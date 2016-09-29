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

void PluginManager::insertPlugin(const std::string & superclass, const std::string pluginClass, const std::string & name, SelfConfiguringPlugin* plugin)
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

SelfConfiguringPlugin* PluginManager::getPlugin(const std::string & name) {
    SelfConfiguringPlugin* finded = NULL;
    auto it = namePluginMap.find(name);

    if (it != namePluginMap.end()) {
        finded = it->second;
    } else {
        LOG(WARNING) << "unexistence plugin: " << name;
    }
    return finded;
}

SelfConfiguringPlugin* PluginManager::makeNewPlugin(const std::string & superclass, const std::string & type, const std::unordered_map<std::string,std::string> & params) throw (std::invalid_argument) {
    auto it = superclassPrototypeMap.find(superclass);
    if (it != superclassPrototypeMap.end()) {
        SelfConfiguringPlugin* newPlugin = it->second->clone();
        newPlugin->setPluginType(type);
        newPlugin->setParams(params);
        return newPlugin;
    } else {
        throw(new std::invalid_argument(superclass + " is not a valid superClass"));
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
