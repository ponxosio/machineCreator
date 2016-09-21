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

# include "gui/graphicsmanager.h"
# include "fluidControl/executable/containers/InletContainer.h"
# include "fluidControl/executable/containers/SinkContainer.h"
# include "plugin/actuators/ExtractorPlugin.h"
# include "plugin/actuators/InjectorPlugin.h"
# include "util/Utils.h"

typedef enum AplicationStatus_ {
    normal,
    connect_operation
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
    void saveMachine();
    void openMachine();
    void managePlugins();
    void about();
    void zoomIn();
    void zoomOut();
    void itemSelected();
    void exportMachine();

private:
    Ui::MainWindow *ui;
    AplicationStatus status;
    CustomContainerItem* temp1Container;
    CustomContainerItem* temp2Container;
    GraphicsManager* manager;

    void makeToolBar();
    void processConnectContainers();
};

#endif // MAINWINDOW_H
