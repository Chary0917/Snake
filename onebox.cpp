#include "onebox.h"

OneBox::OneBox(qreal x,qreal y)
{
    setPos(x,y);
}

//void OneBox::moveTo(int x, int y)
//{
//    this->x = x;
//    this->y = y;
//    setPos(this->x,this->y);
//}

//碰撞检测
bool OneBox::isColliding()
{
    QList<QGraphicsItem *> itemList = collidingItems();
    if(itemList.count() > 0){
        return true;
    }
    return false;
}


QRectF OneBox::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10-adjust,-10-adjust,
                    20+adjust,20+adjust);
}

void OneBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
//    static QColor colorTable[7] = {
//        Qt::red,Qt::green,Qt::blue,Qt::cyan,Qt::yellow,Qt::gray,Qt::white
//    };


    painter->setBrush(Qt::yellow);
    painter->setPen(Qt::blue);
    painter->drawRect(-10,-10,20,20);
}

QPainterPath OneBox::shape() const
{
    QPainterPath path;
    path.addRect(-9.5,-9.5,19,19);
    return path;
}
