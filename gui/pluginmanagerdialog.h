#ifndef PLUGINMANAGERDIALOG_H
#define PLUGINMANAGERDIALOG_H

#include <unordered_map>

//Qt
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QColumnView>

//local
#include "plugin/actuators/selfconfiguringplugin.h"
#include "pluginmanager.h"
#include "newplugindialog.h"
#include "editplugindialog.h"

class PluginManagerDialog : public QDialog
{ 
    Q_OBJECT
public:
    PluginManagerDialog(PluginManager* pluginManager, QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~PluginManagerDialog();

    //getters & setters
    inline std::string getSelectedPlugin() const {
        return selectedPluginName;
    }

public slots:
    void treeItemSlected(const QModelIndex &index);
    void saveEditedPlugIn();
    void done();
    void cancel();
    void makeNewPlugin();

protected:
    PluginManager* pluginManager;
    QGroupBox* actualGroupBox;
    QGridLayout* actualLayout;
    std::shared_ptr<SelfConfiguringPlugin> selectedPlugin;
    std::string selectedPluginName;
    QPushButton* editBtn;
    QPushButton* acceptBtn;

    void makeDefaultGroupBox();
    void makePluginGroupBox(std::shared_ptr<SelfConfiguringPlugin> plugin);
    void clearsActualLayout();
};

#endif // PLUGINMANAGERDIALOG_H
