#include "gameview.h"

GameView::GameView()
{
    scene = new QGraphicsScene;
    snake = new Snake;
    addItems();
    setScene(scene);
    score = 0;

    connect(this,SIGNAL(keyPress(QKeyEvent*)),
            snake,SLOT(keyPressEvent(QKeyEvent*)));
    connect(snake,SIGNAL(addandDelBox(OneBox*,OneBox*)),
            this,SLOT(changedItem(OneBox*,OneBox*)));
    connect(snake,SIGNAL(needNewBox()),this,SLOT(needNewBox()));
    connect(snake,SIGNAL(gameEnd()),this,SLOT(endGame()));

    //添加边界线，进行碰撞检测
    QGraphicsLineItem *topLineItem =new QGraphicsLineItem(-20,-20,820,-20);
    QGraphicsLineItem *leftLineItem = new QGraphicsLineItem(-20,-20,-20,620);
    QGraphicsLineItem *buttonLineItem = new QGraphicsLineItem(-20,620,820,620);
    QGraphicsLineItem *rightLineItem = new QGraphicsLineItem(820,-20,820,620);
    scene->addItem(topLineItem);
    scene->addItem(leftLineItem);
    scene->addItem(buttonLineItem);
    scene->addItem(rightLineItem);


    setMinimumSize(802, 602);
    setMaximumSize(802, 602);

    scene->setSceneRect(0,0,800,600);
//    setSceneRect(0,0,800,600);
//    setSceneRect(0,0,800,600);

    setBackgroundBrush(Qt::black);
    needNewBox();
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    emit keyPress(event);
}

//生成随机OneBox
void GameView::needNewBox()
{
    score += 20;
    int x = qrand() % 800;
    int y = qrand() % 600;
    x = (x - x % 20) + 10;
    y = (y - y % 20) + 10;
    randomBox = new OneBox(x,y);
    snake->setEatBox(randomBox);
    scene->addItem(randomBox);
}

void GameView::endGame()
{
    snake->stop();
    QMessageBox::about(this,tr("Good!!!"),tr("You had Lost！<br/>You score is%1").arg(score));
    qApp->exit();
}


//添加删除场景项
void GameView::changedItem(OneBox *addBox, OneBox *delBox)
{
    scene->addItem(addBox);
    scene->removeItem(delBox);
//进行重绘操作，取消会有问题
    this->viewport()->update();
}

//初始化时添加场景项导场景中
void GameView::addItems()
{
    QList<OneBox *> itemList = snake->getOneBoxList();
    foreach (OneBox *box, itemList) {
            scene->addItem(box);
    }
}
