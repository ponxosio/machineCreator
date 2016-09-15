#ifndef CUSTOMIMAGEGRAPHICSITEM_H
#define CUSTOMIMAGEGRAPHICSITEM_H

# include <QGraphicsItem>
# include <QString>

class CustomImageGraphicsItem : public QGraphicsItem
{
public:
    CustomImageGraphicsItem(QString imgPath);

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    QString imgPath;

};

#endif // CUSTOMIMAGEGRAPHICSITEM_H
