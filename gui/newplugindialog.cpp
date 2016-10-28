#include "newplugindialog.h"

using namespace std;

NewPluginDialog::NewPluginDialog(PluginManager* pluginManager, QWidget* parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    setWindowTitle("New Plugin");

    this->pluginManager = pluginManager;
    this->selectedItem = NULL;

    QTreeView* view = new QTreeView(this);
    view->setModel(this->pluginManager->getModel());
    hide3Level(view);

    paramsBox = new QGroupBox("no type selected",this);
    actualLayout = new QGridLayout(this);
    createDefualtLayout();
    paramsBox->setLayout(actualLayout);

    acceptBtn = new QPushButton("Create", this);
    acceptBtn->setEnabled(false);

    QPushButton* cancelBtn = new QPushButton("Cancel", this);

    this->nameLineEdit = new QLineEdit();

    QGroupBox* nameBox = new QGroupBox("Name", this);
    QGridLayout* nameGrid = new QGridLayout(this);
    //nameGrid->addWidget(new QLabel("Name"), 0, 0);
    nameGrid->addWidget(nameLineEdit, 0,0);
    nameBox->setLayout(nameGrid);

    QGroupBox* viewBox = new QGroupBox(this);
    QGridLayout* viewLayout = new QGridLayout(this);
    viewLayout->addWidget(view, 1,0);
    viewLayout->addWidget(acceptBtn, 2,0);
    viewLayout->addWidget(cancelBtn, 2, 1);
    viewBox->setLayout(viewLayout);

    QGridLayout* grid = new QGridLayout();
    grid->addWidget(nameBox, 0,0);
    grid->addWidget(viewBox, 1, 1);
    grid->addWidget(paramsBox, 1, 0);

    setLayout(grid);

    connect(this->pluginManager, SIGNAL(indexChanged(const QModelIndex &)), view, SLOT(update(const QModelIndex &)));
    connect(view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(treeItemSlected(const QModelIndex &)));
    connect(acceptBtn, SIGNAL(clicked(bool)), this, SLOT(done()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancel()));
}

NewPluginDialog::~NewPluginDialog() {

}


//slots
void NewPluginDialog::done() {
    std::unordered_map<std::string,std::string> paramsMap;
    for (auto it = params.begin(); it != params.end(); ++it) {
        paramsMap.insert(make_pair((*it).first, (*it).second->text().toUtf8().constData()));
    }
    std::shared_ptr<SelfConfiguringPlugin> createdPlugin = std::shared_ptr<SelfConfiguringPlugin>(
                                pluginManager->makeNewPlugin(nameLineEdit->text().toUtf8().constData(),
                                                       selectedItem->parent()->text().toUtf8().constData(),
                                                       selectedItem->text().toUtf8().constData(),
                                                       paramsMap));
    pluginManager->insertPlugin(selectedItem->parent()->text().toUtf8().constData(),
                                selectedItem->text().toUtf8().constData(),
                                nameLineEdit->text().toUtf8().constData(),
                                createdPlugin);
    accept();
}

void NewPluginDialog::cancel() {
    reject();
}

void NewPluginDialog::treeItemSlected(const QModelIndex &index) {
    selectedItem = pluginManager->getModel()->itemFromIndex(index);
    if (selectedItem->parent() != 0) {
        this->acceptBtn->setEnabled(true);
        std::string type = selectedItem->text().toUtf8().constData();
        createTypeLayout(type);
        paramsBox->setTitle(QString::fromStdString(type));
    }
}

//protected
void NewPluginDialog::createDefualtLayout() {
    clearsActualLayout();
    actualLayout->addWidget(new QLabel("Select a type to create a new plugin", this), 0, 0);
    actualLayout->update();
}

void NewPluginDialog::createTypeLayout(const std::string & type) {
    clearsActualLayout();
    try {
        std::vector<std::pair<std::string, std::string>> paramsTypes = PythonEnvironment::GetInstance()->getParamsType(type);
        this->params.clear();

        int i = 0;
        for (auto it = paramsTypes.begin(); it != paramsTypes.end(); ++it) {
            QLineEdit* line = new QLineEdit();
            actualLayout->addWidget(line, i, 1);
            actualLayout->addWidget(new QLabel(QString::fromStdString((*it).first + "[" + (*it).second + "]"), this), i, 0);

            this->params.push_back(make_pair((*it).first,line));
            i++;
        }
    } catch (std::runtime_error & e) {
        actualLayout->addWidget(new QLabel("ERROR", this));
        LOG(ERROR) << e.what();
    }
    actualLayout->update();
}

void NewPluginDialog::clearsActualLayout() {
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

void NewPluginDialog::hide3Level(QTreeView* tree) {
    std::vector<QStandardItem*> classItems = pluginManager->getAllClassItems();
    for(QStandardItem* actual: classItems) {
        int rowCount = actual->rowCount();
        for (int i= 0; i < rowCount; i++) {
            tree->setRowHidden(i, actual->index(), true);
        }
    }
}
