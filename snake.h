#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItemGroup>
#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QList>


#include "onebox.h"

//枚举上下左右四个按键状态
enum KEY_STATUS {NOSTATUS,KEYUP,KEYDOWN,KEYLEFT,KEYRIGHT};

class Snake : public QObject
{
    Q_OBJECT
public:
    explicit Snake(QObject *parent = 0);
    QList<OneBox *> getOneBoxList() { return oneboxList;}  //返回OneBox列表
    void setEatBox(OneBox *box) { eatBox = box;} //设置要吃的OneBox位置
    void stop();
signals:
    void addandDelBox(OneBox *addbox,OneBox *delBox);
    void gameEnd();
    void needNewBox();

public slots:
    void keyPressEvent(QKeyEvent *event);
    void timeout();

private:
    bool move(KEY_STATUS status,int xy);
    void changedPos(qreal x,qreal y);
    void pause();
    bool isColliding(KEY_STATUS status);
    void addBox();


    OneBox *eatBox;
    unsigned int msec;
    bool isPause;
    QList<OneBox *> oneboxList;
    QTimer timer;
    KEY_STATUS current_key_status;
};

#endif // SNAKE_H
