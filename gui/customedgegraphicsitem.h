#ifndef CUSTOMEDGEGRAPHICSITEM_H
#define CUSTOMEDGEGRAPHICSITEM_H

# define ARROW_SIZE 6

//Qt
# include <QGraphicsLineItem>
# include <QPointF>
# include <QPainter>
# include <QVector2D>

class CustomEdgeGraphicsItem : public QGraphicsLineItem
{
public:
    CustomEdgeGraphicsItem(const QPointF & startPoint, const QPointF & endPoint, QGraphicsItem * parent = 0);
    virtual ~CustomEdgeGraphicsItem();

    void setStartPoint(const QPointF & startPoint);
    void setEndPoint(const QPointF & endPoint);

    //override methods
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QPointF startPoint;
    QPointF endPoint;
    bool selected;

    void paintArrow(QPainter *painter, const QLineF & line);

};

#endif // CUSTOMEDGEGRAPHICSITEM_H
