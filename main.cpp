#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "gameview.h"


int main(int argc,char **argv)
{
    QApplication app(argc,argv);
//置随机数种子
    qsrand(QTime::currentTime().msec());
    GameView view;
    view.show();


    return app.exec();
}
