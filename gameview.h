#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QMessageBox>
#include <QObject>
#include <QGraphicsView>
#include <QtCore>

#include "snake.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView();

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void keyPress(QKeyEvent *event);

private slots:
    void changedItem(OneBox *addBox,OneBox *delBox);
    void needNewBox();
    void endGame();
private:
    void addItems();

    int score;
    OneBox *randomBox;
    QGraphicsScene *scene;
    Snake *snake;
};

#endif // GAMEVIEW_H
