#ifndef CUSTOMCONTAINERITEM_H
#define CUSTOMCONTAINERITEM_H

//std
# include <memory>

//Qt
# include <QGraphicsPixmapItem>
# include <QList>
# include <QPixmap>

//lib
# include <easylogging++.h>

//local
# include "gui/customedgegraphicsitem.h"
# include "fluidControl/machineGraph/ContainerNodeType.h"

class CustomContainerItem : public QGraphicsPixmapItem
{
public:
    CustomContainerItem(const QString & name, const QPixmap &pixmap, const bool* addons, QGraphicsItem *parent = Q_NULLPTR);
    virtual ~CustomContainerItem();

    void addArrivingEdge(CustomEdgeGraphicsItem* edge);
    void addLeavingEdge(CustomEdgeGraphicsItem* edge);

    void removeEdge(CustomEdgeGraphicsItem* edge);

    // override
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

    //inline
    inline QList<CustomEdgeGraphicsItem*> getLeavingEdges() const {
        return leavingEdges;
    }
    inline QList<CustomEdgeGraphicsItem*> getArrivingEdges() const {
        return arrivingEdges;
    }
protected:
    QList<CustomEdgeGraphicsItem*> leavingEdges;
    QList<CustomEdgeGraphicsItem*> arrivingEdges;
    bool addons[ADDONS_MAX];
    QString name;

    QPixmap getAddon(int i);

};

#endif // CUSTOMCONTAINERITEM_H
