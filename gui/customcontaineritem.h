#ifndef CUSTOMCONTAINERITEM_H
#define CUSTOMCONTAINERITEM_H

//std
# include <memory>

//Qt
# include <QGraphicsPixmapItem>
# include <QList>

//lib
# include <easylogging++.h>

//local
# include "gui/customedgegraphicsitem.h"

class CustomContainerItem : public QGraphicsPixmapItem
{
public:
    CustomContainerItem(const QString & name, const QPixmap &pixmap, QGraphicsItem *parent = Q_NULLPTR);
    virtual ~CustomContainerItem();

    void addArrivingEdge(CustomEdgeGraphicsItem* edge);
    void addLeavingEdge(CustomEdgeGraphicsItem* edge);

    void removeEdge(CustomEdgeGraphicsItem* edge);

    // override
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QList<CustomEdgeGraphicsItem*> leavingEdges;
    QList<CustomEdgeGraphicsItem*> arrivingEdges;
};

#endif // CUSTOMCONTAINERITEM_H
