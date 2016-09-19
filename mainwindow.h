#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

# include "gui/graphicsmanager.h"
# include "fluidControl/executable/containers/InletContainer.h"
# include "fluidControl/executable/containers/SinkContainer.h"
# include "plugin/actuators/ExtractorPlugin.h"
# include "plugin/actuators/InjectorPlugin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addContainer();
    void removeContainer();
    void editContainer();
    void connectContainers();
    void saveMachine();
    void openMachine();
    void managePlugins();
    void about();
    void zoomIn();
    void zoomOut();

private:
    void makeToolBar();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
