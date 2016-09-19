#include "customedgegraphicsitem.h"

CustomEdgeGraphicsItem::CustomEdgeGraphicsItem(const QPointF & startPoint, const QPointF & endPoint, QGraphicsItem * parent) :
    QGraphicsLineItem(QLineF(startPoint, endPoint), parent), startPoint(startPoint), endPoint(endPoint)
{
    this->selected = false;

    setFlag(QGraphicsItem::ItemIsSelectable);
}

CustomEdgeGraphicsItem::~CustomEdgeGraphicsItem()  {

}

void CustomEdgeGraphicsItem::setStartPoint(const QPointF & startPoint) {
    QGraphicsLineItem::setLine(QLineF(startPoint,endPoint));
    this->startPoint = QPointF(startPoint);
    update(shape().boundingRect());
}

void CustomEdgeGraphicsItem::setEndPoint(const QPointF & endPoint) {
    QGraphicsLineItem::setLine(QLineF(startPoint,endPoint));
    this->endPoint = QPointF(endPoint);
    update(shape().boundingRect());
}

/*
 * Overriden methods
 */
void CustomEdgeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (selected) {
        painter->setPen(Qt::red);
    } else {
        painter->setPen(Qt::black);
    }

    QLineF line(startPoint,endPoint);
    painter->drawLine(line);

    paintArrow(painter, line);
}

void CustomEdgeGraphicsItem::paintArrow(QPainter *painter, const QLineF & line) {
    QLineF normal = line.normalVector();

    QVector2D lineV(line.p2());
    lineV -= QVector2D(line.p1());
    lineV.normalize();

    QVector2D normalV(normal.p2());
    normalV -= QVector2D(normal.p1());
    normalV.normalize();

    QVector2D endPointV(endPoint);
    QVector2D backPoint;
    backPoint = endPointV - ARROW_SIZE*lineV;

    QVector2D topPoint = backPoint + ARROW_SIZE*normalV;
    QVector2D buttomPoint = backPoint - ARROW_SIZE*normalV;

    painter->drawLine(topPoint.toPointF(),endPoint);
    painter->drawLine(buttomPoint.toPointF(),endPoint);
}

QVariant CustomEdgeGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if ( change == QGraphicsItem::ItemSelectedChange ) {
        if (value == true) {
            selected = true;
        } else {
            selected = false;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

QPainterPath CustomEdgeGraphicsItem::shape() const {

    QLineF line = QGraphicsLineItem::line();
    QLineF normal = line.normalVector();

    QVector2D normalV(normal.p2());
    normalV -= QVector2D(normal.p1());
    normalV.normalize();

    QVector2D endPointV(endPoint);
    QVector2D startPointV(startPoint);

    QVector2D topLeftPoint = startPointV + ARROW_SIZE*normalV;
    QVector2D buttomLeftPoint = startPointV - ARROW_SIZE*normalV;
    QVector2D topRightPoint = endPointV + ARROW_SIZE*normalV;
    QVector2D buttomRightPoint = endPointV - ARROW_SIZE*normalV;

    QPainterPath path;
    QPolygonF polygon;

    polygon << topLeftPoint.toPointF();
    polygon << buttomLeftPoint.toPointF();
    polygon << buttomRightPoint.toPointF();
    polygon << topRightPoint.toPointF();

    path.addPolygon(polygon);
    return path;
}
