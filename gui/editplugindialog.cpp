#include "editplugindialog.h"

EditPluginDialog::EditPluginDialog(const std::string & name, SelfConfiguringPlugin* plugin, QWidget* parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    setWindowTitle("Edit plugin " + QString::fromStdString(name));
    this->plugin = plugin;
    std::unordered_map<std::string, std::string> actualParams = plugin->getParams();
    std::vector<std::pair<std::string, std::string>> typeParams = SelfConfiguringPlugin::getParamsType(plugin->getPluginType());

    QPushButton* acceptBtn = new QPushButton("Accept");
    QPushButton* cancelBtn = new QPushButton("Cancel");

    QGroupBox* mainBox = new QGroupBox();
    QGridLayout* boxGrid = new QGridLayout();

    int i = 0;
    for (std::pair<std::string, std::string> it: typeParams) {
        std::string key = it.first;
        std::string paramValue = "unknow";
        std::string paramType = it.second;

        auto valueFinded = actualParams.find(key);
        if (valueFinded != actualParams.end()) {
            paramValue = valueFinded->second;
        } else {
            LOG(WARNING) << "params " << key << " has type but no value";
        }

        QLineEdit* valueEdit = new QLineEdit(QString::fromStdString(paramValue));
        paramsLineEditMap.push_back(make_pair(key, valueEdit));

        boxGrid->addWidget(new QLabel(QString::fromStdString(key + "[" + paramType + "]")), i, 0);
        boxGrid->addWidget(valueEdit, i, 1);
        i++;
    }
    mainBox->setLayout(boxGrid);

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(mainBox, 0,0);
    mainLayout->addWidget(acceptBtn, 1,0);
    mainLayout->addWidget(cancelBtn, 1,1);
    this->setLayout(mainLayout);

    connect(acceptBtn, SIGNAL(clicked(bool)), this, SLOT(done()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancel()));
}

EditPluginDialog::~EditPluginDialog() {

}

//slots

void EditPluginDialog::done() {
    updatePlugin();
    accept();
}

void EditPluginDialog::cancel() {
    reject();
}


//protected
void EditPluginDialog::updatePlugin() {
    std::unordered_map<std::string, std::string> newParams;
    for(std::pair<std::string, QLineEdit*> actual: paramsLineEditMap) {
        std::string key = actual.first;
        std::string value = actual.second->text().toUtf8().constData();
        newParams.insert(make_pair(key, value));
    }
    plugin->setParams(newParams);
}
