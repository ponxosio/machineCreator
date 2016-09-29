#ifndef NEWPLUGINDIALOG_H
#define NEWPLUGINDIALOG_H

# include <vector>

//Qt
#include <QDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeView>

//local
#include "gui/pluginmanager.h"
#include "plugin/actuators/selfconfiguringplugin.h"

class NewPluginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewPluginDialog(PluginManager* pluginManager, QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~NewPluginDialog();

signals:

protected slots:
    void done();
    void cancel();
    void treeItemSlected(const QModelIndex &index);

protected:
    PluginManager* pluginManager;
    QGridLayout* actualLayout;
    QStandardItem* selectedItem;
    std::vector<std::pair<std::string, QLineEdit*>> params;
    QPushButton* acceptBtn;
    QLineEdit* nameLineEdit;
    QGroupBox* paramsBox;

    void createDefualtLayout();
    void createTypeLayout(const std::string & type);
    void clearsActualLayout();
    void hide3Level(QTreeView* tree);
};

#endif // NEWPLUGINDIALOG_H
