#include "mainwindow.h"
#include <QApplication>
#include <QTextStream>

#include <util/Utils.h>
#include <graph/Graph.h>
#include <graph/Node.h>
#include <graph/Edge.h>

#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Load configuration from file
    el::Configurations conf("X:\\machineCreator\\configuration\\log.ini");
    // Actually reconfigure all loggers instead
    el::Loggers::reconfigureAllLoggers(conf);

    Graph<Node,Edge>* g = new Graph<Node,Edge>();
    std::shared_ptr<Node> node1 = std::make_shared<Node>(1);
    std::shared_ptr<Node> node2 = std::make_shared<Node>(2);
    std::shared_ptr<Edge> edge12 = std::make_shared<Edge>(1,2);

    g->addNode(node1);
    g->addNode(node2);
    g->addEdge(edge12);

    LOG(INFO) << Utils::getCurrentTimeMilis();
    LOG(INFO) << g->toString();

    return a.exec();
}
