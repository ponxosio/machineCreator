#include "customimagegraphicsitem.h"

CustomImageGraphicsItem::CustomImageGraphicsItem(QString imgPath)
{
    this->imgPath = imgPath;
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
}


QRectF CustomImageGraphicsItem::boundingRect() const {

}

void CustomImageGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

