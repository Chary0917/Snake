#include "snake.h"

Snake::Snake(QObject *parent) :
    QObject(parent)
{
//初始化，分配三个OneBox
    OneBox *onebox = new OneBox(50,10);
    oneboxList.append(onebox);
    OneBox *onebox2 = new OneBox(30,10);
    oneboxList.append(onebox2);
    OneBox *onebox3 = new OneBox(10,10);
    oneboxList.append(onebox3);
    current_key_status = KEYRIGHT;

    isPause = false;
    msec = 1000;

    connect(&timer,SIGNAL(timeout()),
            this,SLOT(timeout()));
    timer.start(msec);
}

//停止
void Snake::stop()
{
    timer.stop();

}

//按键处理函数
void Snake::keyPressEvent(QKeyEvent *event)
{
    if(isPause && event->key() != Qt::Key_Space){
        return;
    }
    switch(event->key()){
    case Qt::Key_Up:{
            if(move(KEYUP,20))
                current_key_status = KEYUP;
            break;
        }
    case Qt::Key_Down:{
            if(move(KEYDOWN,20))
                current_key_status = KEYDOWN;
            break;
        }
    case Qt::Key_Left: {
            if(move(KEYLEFT,20))
                current_key_status = KEYLEFT;
            break;
        }
    case Qt::Key_Right:{
            if(move(KEYRIGHT,20))
                current_key_status = KEYRIGHT;
            break;
        }
    case Qt::Key_Space:{
            isPause = !isPause;
            pause();
            break;
        }
    }
}

//超时处理
void Snake::timeout()
{
    if(!isPause)
        move(current_key_status,20);
}


//根据按键状态进行移动
bool Snake::move(KEY_STATUS status, int xy)
{
    bool return_value = false;
    switch(status){
        case KEYRIGHT:{
            if(current_key_status != KEYLEFT && !isColliding(KEYRIGHT)){
                changedPos(oneboxList.at(0)->pos().x()+xy,oneboxList.at(0)->pos().y());
                return_value = true;
            }
            break;
        }
    case KEYLEFT:{
            if(current_key_status != KEYRIGHT && !isColliding(KEYLEFT)){
                changedPos(oneboxList.at(0)->pos().x()-xy,oneboxList.at(0)->pos().y());
                return_value = true;
            }
            break;
        }
    case KEYUP:{
            if(current_key_status != KEYDOWN && !isColliding(KEYUP)){
                changedPos(oneboxList.at(0)->pos().x(),oneboxList.at(0)->pos().y()-xy);
                return_value = true;
            }
            break;
        }
    case KEYDOWN:{
            if(current_key_status != KEYUP && !isColliding(KEYDOWN)){
                changedPos(oneboxList.at(0)->pos().x(),oneboxList.at(0)->pos().y()+xy);
                return_value = true;
            }
            break;
        }
    default:
        break;
    }
    return return_value;
}


//改变坐标，x,y分别为移动后的第一个坐标
void Snake::changedPos(qreal x, qreal y)
{
    OneBox *onebox = new OneBox(x,y);
    emit addandDelBox(onebox,oneboxList.last());
    oneboxList.insert(0,onebox);
    oneboxList.removeLast();

}

//暂停函数
void Snake::pause()
{
    if(isPause){
        timer.setInterval(0);
    } else {
        timer.setInterval(msec);
    }
}

//判断是否碰撞,并对其进行处理
bool Snake::isColliding(KEY_STATUS status)
{
    OneBox *tempBox = oneboxList.front();
    bool isCollidingStatus = false;
    switch(status){
        case KEYDOWN:{
            tempBox->moveBy(0,20);
            if(tempBox->isColliding()){
                current_key_status = KEYDOWN;
                isCollidingStatus = true;
                if(tempBox->collidesWithItem(eatBox)){
 //                      tempBox->moveBy(0,-20);
                       addBox();

                } else{
//                      tempBox->moveBy(0,-20);
                      emit gameEnd();
                }
            }
            tempBox->moveBy(0,-20);
            break;
        }
        case KEYUP:{
            tempBox->moveBy(0,-20);
            if(tempBox->isColliding()){
                current_key_status = KEYUP;
                isCollidingStatus = true;
                if(tempBox->collidesWithItem(eatBox)){
//                       tempBox->moveBy(0,20);
                       addBox();

                } else{
                      tempBox->moveBy(0,20);
                      emit gameEnd();
                }
            }
            tempBox->moveBy(0,20);
            break;
        }
        case KEYLEFT:{
            tempBox->moveBy(-20,0);
            if(tempBox->isColliding()){
                current_key_status = KEYLEFT;
                isCollidingStatus = true;
                if(tempBox->collidesWithItem(eatBox)){
//                       tempBox->moveBy(20,0);
                       addBox();

                } else{
//                      tempBox->moveBy(20,0);
                      emit gameEnd();
                }
            }
            tempBox->moveBy(20,0);
            break;
        }
        case KEYRIGHT:{
            tempBox->moveBy(20,0);
            if(tempBox->isColliding()){
                current_key_status = KEYRIGHT;
                isCollidingStatus = true;
                if(tempBox->collidesWithItem(eatBox)){
//                       tempBox->moveBy(-20,0);
                       addBox();

                } else{
//                      tempBox->moveBy(-20,0);
                      emit gameEnd();
                }
            }
            tempBox->moveBy(-20,0);
            break;
        }
        default: break;
    }
    return isCollidingStatus;
}

/*
//在贪吃蛇尾部加上一个OneBox,坐标取决于最后两个
void Snake::addBox()
{
    OneBox *last1box =oneboxList.last();
    OneBox *last2box = oneboxList.at(oneboxList.count()-2);
    qreal x,y;
    x = 2*last1box->pos().y() - last2box->pos().x();
    y = 2*last1box->pos().y() - last2box->pos().x();

    OneBox *newBox =new OneBox(x,y);
    oneboxList.append(newBox);

    emit addandDelBox(newBox,eatBox);
    emit needNewBox();
}*/

//重新实现addBox,提高效率
void Snake::addBox()
{
    oneboxList.push_front(eatBox);
    emit needNewBox();
}



