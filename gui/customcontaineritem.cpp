#include "customcontaineritem.h"

CustomContainerItem::CustomContainerItem(const QString & name, const QPixmap &pixmap, const bool* addons, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent)
{
    this->name = name;
    setToolTip(this->name);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    for (int i = 0; i < ADDONS_MAX; i++) {
        this->addons[i] = addons[i];
    }
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

//overriden
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

void CustomContainerItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);

    QPointF testP;
    testP.setX(33);
    testP.setY(15);
    painter->drawText(testP, name);

    for (int i = 0; i < ADDONS_MAX; i++) {
        if (addons[i]) {
            QPointF actual;
            QPixmap actualPNG = getAddon(i);
            actual.setY(33 * i);
            painter->drawPixmap(actual, actualPNG);
        }
    }
}

//protected
QPixmap CustomContainerItem::getAddon(int i) {
    switch (i) {
    case mixer:
        return QPixmap("Img/mixer.png");
        break;
    case temp:
        return QPixmap("Img/temperature.png");
        break;
    case light:
        return QPixmap("Img/light.png");
        break;
    case OD_sensor:
        return QPixmap("Img/odsensor.png");
        break;
    default:
        LOG(ERROR) << "unknow type of addon: " << i ;
        break;
    }
}
