#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(this);

    CustomContainerItem* picItem = new CustomContainerItem(QPixmap("X:/machineCreator/Img/unknow.png"), NULL, ui->statusBar);
    scene->addItem(picItem);

    ui->graphicsView->setScene(scene);
    ui->statusBar->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// SLOTS

void MainWindow:: addContainer() {

}

void MainWindow::removeContainer(){

}

void MainWindow::connectContainers() {

}

void MainWindow::saveMachine() {

}

void MainWindow::openMachine() {

}

void MainWindow::managePlugins() {

}

void MainWindow::about() {
}

void MainWindow::makeToolBar() {

}

void MainWindow::zoomIn() {

}

void MainWindow::zoomOut() {

}

void MainWindow::editContainer() {

}
