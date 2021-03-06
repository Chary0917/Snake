#ifndef BOX_H
#define BOX_H

#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>


//�ߵ������Box
class OneBox : public QGraphicsItem
{
public:
    OneBox(qreal x = 0,qreal y = 0);
    bool isColliding();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget);
    QPainterPath shape() const;

};

#endif // BOX_H
