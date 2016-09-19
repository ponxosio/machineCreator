#include "customcontaineritem.h"

CustomContainerItem::CustomContainerItem(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

CustomContainerItem::~CustomContainerItem() {
}

void CustomContainerItem::addArrivingEdge(CustomEdgeGraphicsItem* edge) {
    this->arrivingEdges.append(edge);
}

void CustomContainerItem::addLeavingEdge(CustomEdgeGraphicsItem* edge) {
    this->leavingEdges.append(edge);
}

void CustomContainerItem::removeEdge(CustomEdgeGraphicsItem* edge) {
    int indexArriving = arrivingEdges.indexOf(edge);
    if (indexArriving != -1) {
        arrivingEdges.removeAt(indexArriving);
    } else {
        int indexLeaving = leavingEdges.indexOf(edge);
        if (indexLeaving != -1) {
            leavingEdges.removeAt(indexLeaving);
        } else {
            LOG(WARNING) << "deleting an unexisting edge";
        }
    }
}

QVariant CustomContainerItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();

        QListIterator<CustomEdgeGraphicsItem*> itLeaving(arrivingEdges);
        while(itLeaving.hasNext()) {
            CustomEdgeGraphicsItem* actual = itLeaving.next();
            actual->setEndPoint(newPos);
        }

        QListIterator<CustomEdgeGraphicsItem*> itArraving(leavingEdges);
        while(itArraving.hasNext()) {
            CustomEdgeGraphicsItem* actual = itArraving.next();
            actual->setStartPoint(newPos);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
