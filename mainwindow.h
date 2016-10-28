#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define ICON_PATH "ico/"
#define VERSION 0.1

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPoint>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>

# include  "gui/connectcontainerdialog.h"
# include "gui/graphicsmanager.h"
# include "gui/pluginmanagerdialog.h"
# include "gui/pluginmanager.h"
# include "gui/newcontainerdialog.h"
# include "gui/createserialsenderdialog.h"
# include "gui/cretefilesenderdialog.h"
# include "fluidControl/executable/containers/InletContainer.h"
# include "fluidControl/executable/containers/SinkContainer.h"
# include "fluidControl/executable/ExecutableMachineGraph.h"
# include "plugin/actuators/ExtractorPlugin.h"
# include "plugin/actuators/InjectorPlugin.h"
# include "util/Utils.h"

typedef enum AplicationStatus_ {
    normal,
    connect_operation,
    remove_operation
} AplicationStatus;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



protected:
   void keyPressEvent(QKeyEvent* event);

private slots:
    void addContainer();
    void removeElements();
    void editContainer();
    void connectContainers();
    void openMachine();
    void managePlugins();
    void about();
    void zoomIn();
    void zoomOut();
    void itemSelected();
    void exportMachine();
    void setTestCommunication();
    void setExecCommunication();

private:
    Ui::MainWindow *ui;
    AplicationStatus status;
    CustomContainerItem* temp1Container;
    CustomContainerItem* temp2Container;
    GraphicsManager* manager;
    PluginManager* pluginManager;

    void makeToolBar();
    void processConnectContainers();
};

#endif // MAINWINDOW_H
