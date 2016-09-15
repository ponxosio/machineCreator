#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(this);

    QGraphicsPixmapItem* picItem = new QGraphicsPixmapItem(QPixmap("X:/machineCreator/Img/unknow.png"));
    picItem->setFlag(QGraphicsItem::ItemIsMovable);
    picItem->setFlag(QGraphicsItem::ItemIsSelectable);

    scene->addItem(picItem);

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
