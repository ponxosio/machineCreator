#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    PythonEnvironment::GetInstance()->initEnvironment();

    status = AplicationStatus::normal;
    int communications = 0;
    temp1Container = NULL;
    temp2Container = NULL;

    ui->setupUi(this);

    makeToolBar();
    QGraphicsScene* scene = new QGraphicsScene(this);

    manager = new GraphicsManager(scene);
    pluginManager = new PluginManager();

    ui->graphicsView->setScene(scene);
    ui->statusBar->showMessage("Ready");

    QObject::connect(scene, &QGraphicsScene::selectionChanged, this, &MainWindow::itemSelected);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// SLOTS

void MainWindow::setTestCommunication() {
    CreteFileSenderDialog dialog(manager, this);
    dialog.exec();
}

void MainWindow::setExecCommunication() {
    CreateSerialSenderDialog dialog(manager, this);
    dialog.exec();
}

void MainWindow::itemSelected() {
    switch (status) {
    case AplicationStatus::connect_operation:
        processConnectContainers();
        break;
    default:
        break;
    }
}

void MainWindow:: addContainer() {
    NewContainerDialog* dialog = new NewContainerDialog(manager, pluginManager,this);
    dialog->exec();
    delete dialog;
}

void MainWindow::removeElements(){
    QList<QGraphicsItem*> selected = ui->graphicsView->scene()->selectedItems();
    if (!selected.empty()) {
        if (QMessageBox::warning(this, "remove these elements ?", "do you really want to remove this elements?",QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Ok) {
            for (QGraphicsItem* actual: selected) {
                manager->removeElement(actual);
            }
        }
    } else {
        ui->statusBar->showMessage("please select some elements to remove");
    }
}

void MainWindow::connectContainers() {
    ui->graphicsView->scene()->clearSelection();

    temp1Container = NULL;
    temp2Container = NULL;
    status = AplicationStatus::connect_operation;

    ui->statusBar->showMessage("select source container");
}

void MainWindow::openMachine() {
    QString path = QFileDialog::getOpenFileName(this, "select file to open", QString(), tr("JSON (*.json)"));
    if (!path.isEmpty()) {
        ExecutableMachineGraph* machine = ExecutableMachineGraph::fromJSON(path.toUtf8().constData());
        manager->importMachine(machine);
        pluginManager->importMachine(machine);
    }
}

void MainWindow::managePlugins() {
    PluginManagerDialog manager(pluginManager,this, Qt::WindowTitleHint);
    if (manager.exec() == QDialog::Accepted) {
        LOG(INFO) << "accepted";
    }
}

void MainWindow::about() {
    QMessageBox::about(this, "About", "Machine creator version v" + QString::number(VERSION));
}

void MainWindow::zoomIn() {
    ui->graphicsView->scale(1.2, 1.2);
    ui->graphicsView->update();
}

void MainWindow::zoomOut() {
    ui->graphicsView->scale(0.8, 0.8);
    ui->graphicsView->update();
}

void MainWindow::editContainer() {

}

void MainWindow::exportMachine() {
    QString fileName = QFileDialog::getSaveFileName(this, "save machine");
    if (!fileName.isEmpty()) {
        LOG(DEBUG) << "saving machine to " << fileName.toUtf8().constData();
        manager->exportMachineGraph(fileName);
    }
}

//Override

 void MainWindow::keyPressEvent(QKeyEvent* event) {
     if (event->key() == Qt::Key_Escape) {
        status = AplicationStatus::normal;
        ui->statusBar->showMessage("Ready");
     } else if (event->key() == Qt::Key_Plus) {
        ui->statusBar->showMessage("zoom in");
     } else if (event->key() == Qt::Key_Minus) {
        ui->statusBar->showMessage("zoom out");
     }
 }

 //Methods
 void MainWindow::makeToolBar() {
     ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

     QPixmap addpix("ico/add.png");
     QPixmap removepix( "ico/remove.png");
     QPixmap connectpix( "ico/connect.png");
     QPixmap exportpix( "ico/export.png");
     QPixmap openpix( "ico/open.png");
     QPixmap configpix( "ico/configuration.png");
     QPixmap zoomInpix( "ico/zoom-in.png");
     QPixmap zoomOutpix( "ico/zoom-out.png");
     //QPixmap editpix( "ico/edit.png");
     QPixmap aboutpix("ico/about.png");
     QPixmap testCompix("ico/testCom.png");
     QPixmap execCompix("ico/execCom.png");

     QAction *add = ui->mainToolBar->addAction(QIcon(addpix), "Add container");
     QAction *remove = ui->mainToolBar->addAction(QIcon(removepix), "Remove element");
     //QAction *edit = ui->mainToolBar->addAction(QIcon(editpix), "Edit container");
     QAction *connect = ui->mainToolBar->addAction(QIcon(connectpix), "Connect containers");
     QAction *exportAction = ui->mainToolBar->addAction(QIcon(exportpix), "Export Machine");
     QAction *open = ui->mainToolBar->addAction(QIcon(openpix), "Open file");
     QAction *config = ui->mainToolBar->addAction(QIcon(configpix), "Plugin Manager");
     QAction *setTestCom = ui->mainToolBar->addAction(QIcon(testCompix), "set test communication interface");
     QAction *setExecCom = ui->mainToolBar->addAction(QIcon(execCompix), "set execution communication interface");
     QAction *zoomIn = ui->mainToolBar->addAction(QIcon(zoomInpix), "Zoom in");
     QAction *zoomOut = ui->mainToolBar->addAction(QIcon(zoomOutpix), "Zoom out");
     QAction *about = ui->mainToolBar->addAction(QIcon(aboutpix), "about");

     QObject::connect(add, &QAction::triggered, this, &MainWindow::addContainer);
     QObject::connect(remove, &QAction::triggered, this, &MainWindow::removeElements);
     QObject::connect(connect, &QAction::triggered, this, &MainWindow::connectContainers);
     QObject::connect(exportAction, &QAction::triggered, this, &MainWindow::exportMachine);
     QObject::connect(open, &QAction::triggered, this, &MainWindow::openMachine);
     QObject::connect(config, &QAction::triggered, this, &MainWindow::managePlugins);
     QObject::connect(zoomIn, &QAction::triggered, this, &MainWindow::zoomIn);
     QObject::connect(zoomOut, &QAction::triggered, this, &MainWindow::zoomOut);
    // QObject::connect(edit, &QAction::triggered, this, &MainWindow::editContainer);
     QObject::connect(about, &QAction::triggered, this, &MainWindow::about);
     QObject::connect(setExecCom, &QAction::triggered, this, &MainWindow::setExecCommunication);
     QObject::connect(setTestCom, &QAction::triggered, this, &MainWindow::setTestCommunication);
 }

 void MainWindow::processConnectContainers() {
     if (!temp1Container) {
         QList<QGraphicsItem*> items = ui->graphicsView->scene()->selectedItems();
         if (!items.empty()) {
             QGraphicsItem* actualItem = items.back();
             if (dynamic_cast<CustomContainerItem*>(actualItem)) {
                 temp1Container = dynamic_cast<CustomContainerItem*>(actualItem);
                 ui->statusBar->showMessage("select target container");
             } else {
                 ui->graphicsView->scene()->clearSelection();
                 ui->statusBar->showMessage("ERROR - select a container please");
             }
         }
     } else if (!temp2Container) {
         QList<QGraphicsItem*> items = ui->graphicsView->scene()->selectedItems();
         if (!items.empty()) {
             QGraphicsItem* actualItem = items.back();
             if (dynamic_cast<CustomContainerItem*>(actualItem)) {
                 temp2Container = dynamic_cast<CustomContainerItem*>(actualItem);

                 ConnectContainerDialog controlConfigDialog(manager->getExecutableContainer(temp1Container),
                                                            manager->getExecutableContainer(temp2Container),
                                                            this, Qt::WindowTitleHint);

                 if (controlConfigDialog.exec() == QDialog::Accepted) {
                    manager->connectContainers(temp1Container,
                                               temp2Container,
                                               controlConfigDialog.getConditionalEdges());
                 }
                 status = AplicationStatus::normal;
                 ui->statusBar->showMessage("Ready");
             } else {
                 ui->graphicsView->scene()->clearSelection();
                 ui->statusBar->showMessage("ERROR - select a container please");
             }
         }
     }
 }
