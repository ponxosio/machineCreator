#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(this);

    GraphicsManager manager(scene);

    vector<string> paramsce{ "7", "1" };
    std::shared_ptr<Extractor> cExtractor13(
                new ExtractorPlugin(communications, "EvoprogV2Pump", paramsce));

    vector<string> paramsdi;
    std::shared_ptr<Injector> dummyInjector(
                new InjectorPlugin(communications, "EvoprogDummyInjector", paramsdi));

    ExecutableMachineGraph::ExecutableContainerNodePtr cInlet1 = std::make_shared<InletContainer>(1, 100.0, cExtractor13);
    ExecutableMachineGraph::ExecutableContainerNodePtr sink2 = std::make_shared<SinkContainer>(2, 100.0, dummyInjector);

    manager.addContainer(cInlet1);
    manager.addContainer(sink2);

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
