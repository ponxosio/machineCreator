#ifndef CUSTOMCONTAINERITEM_H
#define CUSTOMCONTAINERITEM_H

# include <QGraphicsPixmapItem>
# include <QStatusBar>

class CustomContainerItem : public QGraphicsPixmapItem
{
public:
    CustomContainerItem(const QPixmap &pixmap, QGraphicsItem *parent = Q_NULLPTR, QStatusBar* bar = Q_NULLPTR);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    QStatusBar* bar;
};

#endif // CUSTOMCONTAINERITEM_H
