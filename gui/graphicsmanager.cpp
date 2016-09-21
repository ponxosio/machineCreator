#include "graphicsmanager.h"

GraphicsManager::GraphicsManager(QGraphicsScene* scene, QObject *parent) : QObject(parent)
{
    this->scene = scene;
}

GraphicsManager::~GraphicsManager() {

}

void GraphicsManager::addContainer(std::shared_ptr<ExecutableContainerNode> container) {
    std::string imgPath = Utils::getCurrentDir() + container->getType()->getTypeImagePath();
    LOG(DEBUG) << "loading picture : " << imgPath;
    CustomContainerItem* item = new CustomContainerItem(QPixmap(QString::fromUtf8( imgPath.data(), imgPath.size())));
    machine.addContainer(container);
    scene->addItem(item);
    nodesMap.insert(item, container);
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

}

void GraphicsManager::exportMachineGraph(const QString & path) {

}

void GraphicsManager::removeContainer(CustomContainerItem* container1) {

}

void GraphicsManager::removeEdge(CustomEdgeGraphicsItem* edge) {

}


