#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

# include "gui/customcontaineritem.h"

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
