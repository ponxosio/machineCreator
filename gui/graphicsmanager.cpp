#include "graphicsmanager.h"

GraphicsManager::GraphicsManager(QGraphicsScene* scene, QObject *parent) : QObject(parent)
{
    this->scene = scene;
}

GraphicsManager::~GraphicsManager() {

}

void GraphicsManager::addContainer(std::shared_ptr<ExecutableContainerNode> container) {
    CustomContainerItem* item = new CustomContainerItem(QPixmap(QString(container->getType()->getTypeImagePath())));
    machine.addContainer(container);
    scene->addItem(item);
}

void GraphicsManager::connectContainers(CustomContainerItem* container1, CustomContainerItem* container2) {
    QHash<CustomContainerItem*,std::shared_ptr<ExecutableContainerNode>>::const_iterator it1 = nodseMap.find(container1);
    QHash<CustomContainerItem*,std::shared_ptr<ExecutableContainerNode>>::const_iterator it2 = nodseMap.find(container2);

    if (it1 != hash.end() && it2 != hash.end()) {
        std::shared_ptr<ExecutableContainerNode> node1 = it1.value();
        std::shared_ptr<ExecutableContainerNode> node2 = it2.value();
        CustomEdgeGraphicsItem* arrow = new CustomEdgeGraphicsItem(container1->pos(), container2->pos());

        machine.connectExecutableContainer(node1->getContainerId(), node2->getContainerId());
        scene->addItem(arrow);
        container1->addLeavingEdge(arrow);
        container2->addLeavingEdge(arrow);

        ExecutableMachineGraph::ExecutableContainerEdgeVectorPtr edge = machine.getGraph()->getEdgeList();

    } else {
        LOG(WARNING) << "try to connect two containers that does not exists";
    }
}

void GraphicsManager::removeContainer(CustomContainerItem* container1) {

}

void GraphicsManager::removeEdge(CustomEdgeGraphicsItem* edge) {

}
