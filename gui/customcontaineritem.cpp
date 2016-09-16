#include "customcontaineritem.h"

CustomContainerItem::CustomContainerItem(const QPixmap &pixmap, QGraphicsItem *parent, QStatusBar* bar) :
    QGraphicsPixmapItem(pixmap, parent)
{
    this->bar = bar;
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

QVariant CustomContainerItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        bar->showMessage("x: " + QString::number(newPos.x()) + " , y: " + QString::number(newPos.y()));
    }
    return QGraphicsItem::itemChange(change, value);
}
