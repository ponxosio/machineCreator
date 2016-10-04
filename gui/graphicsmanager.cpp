#include "graphicsmanager.h"

GraphicsManager::GraphicsManager(QGraphicsScene* scene, QObject *parent) : QObject(parent)
{
    this->scene = scene;
}

GraphicsManager::~GraphicsManager() {

}

CustomContainerItem* GraphicsManager::addContainer(const std::string &name, std::shared_ptr<ExecutableContainerNode> container) {
    std::string imgPath = Utils::getCurrentDir() + container->getType()->getTypeImagePath();
    CustomContainerItem* item = new CustomContainerItem(QString::fromStdString(name), QPixmap(QString::fromUtf8( imgPath.data(), imgPath.size())));

    container->setContainerId(serial.getNextValue());
    machine.addContainer(container);
    scene->addItem(item);
    nodesMap.insert(item, container);

    return item;
}

CustomContainerItem* GraphicsManager::addContainer(std::shared_ptr<ExecutableContainerNode> container) {
    std::string imgPath = Utils::getCurrentDir() + container->getType()->getTypeImagePath();
    CustomContainerItem* item = new CustomContainerItem(QString::number(container->getContainerId()), QPixmap(QString::fromUtf8( imgPath.data(), imgPath.size())));

    machine.addContainer(container);
    scene->addItem(item);
    nodesMap.insert(item, container);

    return item;
}

void GraphicsManager::connectContainers(CustomContainerItem* container1, CustomContainerItem* container2) {
    QHash<CustomContainerItem*,std::shared_ptr<ExecutableContainerNode>>::const_iterator it1 = nodesMap.find(container1);
    QHash<CustomContainerItem*,std::shared_ptr<ExecutableContainerNode>>::const_iterator it2 = nodesMap.find(container2);

    LOG(INFO) << "container1 present: " << (nodesMap.contains(container1));
    LOG(INFO) << "container2 present: " << (nodesMap.contains(container2));

    if (it1 != nodesMap.end() && it2 != nodesMap.end()) {
        std::shared_ptr<ExecutableContainerNode> node1 = it1.value();
        std::shared_ptr<ExecutableContainerNode> node2 = it2.value();
        CustomEdgeGraphicsItem* arrow = new CustomEdgeGraphicsItem(container1->pos(), container2->pos());

        machine.connectExecutableContainer(node1->getContainerId(), node2->getContainerId());
        scene->addItem(arrow);
        container1->addLeavingEdge(arrow);
        container2->addArrivingEdge(arrow);

        ExecutableMachineGraph::ExecutableContainerEdgeVectorPtr edge = machine.getGraph()->getEdgeList();
        bool finded = false;
        for (auto it = edge->begin(); !finded && it != edge->end(); ++it) {
            ExecutableMachineGraph::ExecutableContainerEdgePtr actual = *it;
            finded = ((actual->getIdSource() == node1->getContainerId()) &&
                          (actual->getIdTarget() == node2->getContainerId()));
            if (finded) {
                edgesMap.insert(arrow, actual);
            }
        }

        if (!finded) {
            LOG(WARNING) << "unknow edge in the machine graph";
        }
    } else {
        LOG(WARNING) << "try to connect two containers that does not exists";
    }
}

void GraphicsManager::removeElement(QGraphicsItem* item) {
    if (dynamic_cast<CustomContainerItem*>(item)) {
        CustomContainerItem* cast = dynamic_cast<CustomContainerItem*>(item);
        removeContainer(cast);
    } else if (dynamic_cast<CustomEdgeGraphicsItem*>(item)) {
        CustomEdgeGraphicsItem* cast = dynamic_cast<CustomEdgeGraphicsItem*>(item);
        removeEdge(cast);
    } else {
        LOG(WARNING) << "error no know graphics type";
    }
}

void GraphicsManager::exportMachineGraph(const QString & path) {
    ExecutableMachineGraph::toJSON(path.toUtf8().constData(), machine);
}

void GraphicsManager::importMachine(ExecutableMachineGraph* machine) {
    int maxId = 0;
    QHash<int, CustomContainerItem*> nodeMaps;

    clearScene();
    ExecutableMachineGraph::ExecutableContainerNodeVectorPtr nodes = machine->getGraph()->getAllNodes();
    for (ExecutableMachineGraph::ExecutableContainerNodePtr actualNode: *(nodes.get())) {
        CustomContainerItem* graphItem = addContainer(actualNode);
        nodeMaps.insert(actualNode->getContainerId(), graphItem);
        maxId = qMax(maxId, actualNode->getContainerId());
    }
    serial.reset(maxId + 1);

    ExecutableMachineGraph::ExecutableContainerEdgeVectorPtr edges = machine->getGraph()->getEdgeList();
    for (ExecutableMachineGraph::ExecutableContainerEdgePtr actualEdge: *(edges.get())) {
        CustomContainerItem* iSource = nodeMaps[actualEdge->getIdSource()];
        CustomContainerItem* iTarget = nodeMaps[actualEdge->getIdTarget()];
        connectContainers(iSource, iTarget);
    }
}

void GraphicsManager::clearScene() {
    scene->clear();
    machine.clearMachine();
    nodesMap.clear();
    edgesMap.clear();
    serial.reset();
}

// protected
void GraphicsManager::removeContainer(CustomContainerItem* container1) {
    std::shared_ptr<ExecutableContainerNode> nodeGraph = nodesMap[container1];
    machine.getGraph()->removeNode(nodeGraph->getContainerId());

    QList<CustomEdgeGraphicsItem*> arrivingEdges = container1->getArrivingEdges();
    for (CustomEdgeGraphicsItem* arriving: arrivingEdges) {
        removeEdge(arriving);
    }
    QList<CustomEdgeGraphicsItem*> leavingEdges = container1->getLeavingEdges();
    for (CustomEdgeGraphicsItem* leaving: leavingEdges) {
        removeEdge(leaving);
    }

    scene->removeItem(container1);
    nodesMap.remove(container1);
}

void GraphicsManager::removeEdge(CustomEdgeGraphicsItem* edge) {
    std::shared_ptr<Edge> edgeGraph = edgesMap[edge];
    machine.getGraph()->removeEdge(*edgeGraph.get());

    for (CustomContainerItem* actualNode: nodesMap.keys()) {
        actualNode->removeEdge(edge);
    }
    scene->removeItem(edge);
    edgesMap.remove(edge);
}

void GraphicsManager::setTestPrototype(std::unique_ptr<CommandSender> testPrototype) {
    machine.setTestCommunicationsPrototype(std::move(testPrototype));
}

void GraphicsManager::setExecPrototype(std::unique_ptr<CommandSender> execPrototype) {
    machine.setExecCommunicationsPrototype(std::move(execPrototype));
}


