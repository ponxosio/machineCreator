#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

//Qt
#include <QObject>
#include <QHash>
#include <QGraphicsScene>

// local
#include "customcontaineritem.h"
#include "customedgegraphicsitem.h"
#include "fluidControl/executable/ExecutableMachineGraph.h"
#include "fluidControl/executable/containers/ExecutableContainerNode.h"
#include "graph/Edge.h"
#include "util/Utils.h"

/**
 * @brief The GraphicsManager class acts as an intermediate between the graphical Objects at the
 * scene and the logic objects of the graph
 */
class GraphicsManager : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsManager(QGraphicsScene* scene, QObject *parent = 0);
    virtual ~GraphicsManager();

    void addContainer(std::shared_ptr<ExecutableContainerNode> container);
    void connectContainers(CustomContainerItem* container1, CustomContainerItem* container2);

    void removeElement(QGraphicsItem* item);

    void exportMachineGraph(const QString & path);
signals:

public slots:

private:
    QGraphicsScene* scene;
    ExecutableMachineGraph machine;
    QHash<CustomContainerItem*,std::shared_ptr<ExecutableContainerNode>> nodesMap;
    QHash<CustomEdgeGraphicsItem*,std::shared_ptr<Edge>> edgesMap;

    void removeContainer(CustomContainerItem* container1);
    void removeEdge(CustomEdgeGraphicsItem* edge);
};

#endif // GRAPHICSMANAGER_H
