#ifndef BOX_H
#define BOX_H

#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>

class OneBox : public QGraphicsItem
{
public:
    OneBox(qreal x = 0,qreal y = 0);
//    OneBox(OneBox *onebox) { x =onebox->X();y=onebox->Y();}
//    void moveTo(int x,int y);
//    void setX(qreal x) { this->x = x;}
//    void setY(qreal y) { this->y = y;}
//    qreal X(){ return x;}
//    qreal Y(){ return y;}
    bool isColliding();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget);
    QPainterPath shape() const;
private:


};

#endif // BOX_H
