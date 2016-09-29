#include "pluginmanagerdialog.h"

PluginManagerDialog::PluginManagerDialog(PluginManager* pluginManager, QWidget* parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    setWindowTitle("Plugin Manager");
    this->selectedPlugin = NULL;
    this->pluginManager = pluginManager;
    QTreeView* treeview = new QTreeView(this);

    QStandardItemModel* model = this->pluginManager->getModel();
    treeview->setModel(model);

    this->actualGroupBox = new QGroupBox("no plugin selected");
    actualLayout = new QGridLayout();
    makeDefaultGroupBox();
    actualGroupBox->setLayout(actualLayout);

    acceptBtn = new QPushButton("Select");
    acceptBtn->setEnabled(false);
    QPushButton* cancel = new QPushButton("Cancel");
    QPushButton* newPlugin = new QPushButton("new Plugin");
    editBtn = new QPushButton("edit Plugin");
    editBtn->setEnabled(false);

    QGroupBox* treeBox = new QGroupBox();
    QGridLayout* treeLayOut = new QGridLayout();
    treeLayOut->addWidget(treeview, 0,0);
    treeLayOut->addWidget(newPlugin,1,0);
    treeBox->setLayout(treeLayOut);

    QGroupBox* paramsBox = new QGroupBox();
    QGridLayout* paramsGrid = new QGridLayout();
    paramsGrid->addWidget(editBtn, 1,0);
    paramsGrid->addWidget(actualGroupBox,0,0);
    paramsBox->setLayout(paramsGrid);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(treeBox,0, 0);
    grid->addWidget(paramsBox,0,1);
    grid->addWidget(acceptBtn,1, 0);
    grid->addWidget(cancel,1, 1);
    setLayout(grid);

    connect(this->pluginManager, SIGNAL(indexChanged(const QModelIndex &)), treeview, SLOT(update(const QModelIndex &)));
    connect(treeview, SIGNAL(clicked(const QModelIndex &)), this, SLOT(treeItemSlected(const QModelIndex &)));
    connect(acceptBtn, SIGNAL(clicked(bool)), this, SLOT(done()));
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(cancel()));
    connect(newPlugin, SIGNAL(clicked(bool)), this, SLOT(makeNewPlugin()));
    connect(editBtn, SIGNAL(clicked(bool)), this, SLOT(saveEditedPlugIn()));
}

PluginManagerDialog::~PluginManagerDialog()
{
}

//slot
void PluginManagerDialog::treeItemSlected(const QModelIndex &index)
{
    QStandardItem* item = pluginManager->getModel()->itemFromIndex(index);
    QStandardItem* parent;
    if ((parent = item->parent()) != 0) {
        if (parent->parent() != 0) { // if its from level 3 (the plugins cretated by the user
            selectedPluginName = item->text().toUtf8().constData();
            selectedPlugin = this->pluginManager->getPlugin(selectedPluginName);
            actualGroupBox->setTitle(item->text());
            makePluginGroupBox(selectedPlugin);
            editBtn->setEnabled(true);
            acceptBtn->setEnabled(true);
        }
    }
}

void PluginManagerDialog::saveEditedPlugIn() {
    EditPluginDialog* dialog = new EditPluginDialog(selectedPluginName, this->selectedPlugin, this);
    if (dialog->exec() == QDialog::Accepted) {
        makePluginGroupBox(selectedPlugin);
    }
    delete dialog;
}

void PluginManagerDialog::done() {
    accept();
}

void PluginManagerDialog::cancel() {
    reject();
}

void PluginManagerDialog::makeNewPlugin() {
    NewPluginDialog* newDialog = new NewPluginDialog(this->pluginManager, this);
    newDialog->exec();
    delete newDialog;
}

//protected
void PluginManagerDialog::makeDefaultGroupBox()
{
    clearsActualLayout();
    actualLayout->addWidget(new QLabel("Select a plugin to edit it"), 0, 0);
    actualLayout->update();
}

void PluginManagerDialog::makePluginGroupBox(SelfConfiguringPlugin* plugin)
{
    clearsActualLayout();
    unordered_map<string,string> params = plugin->getParams();
    int i = 0;
    for (auto it = params.begin(); it != params.end(); ++it) {
        actualLayout->addWidget(new QLabel(QString::fromStdString(it->first)), i, 0);
        actualLayout->addWidget(new QLabel(QString::fromStdString(it->second)), i, 1);
        i++;
    }
    actualLayout->update();
}

void PluginManagerDialog::clearsActualLayout() {
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
