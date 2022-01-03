#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QString>

#include "gamemodel.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget(QWidget* parent);
    ~GameWidget();
    void initGame();
    void takeBack();
    void setAI(const QString& AI);
    void generateChange(int score);
signals:
    void scoreChanged(const QString& score);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    // 游戏指针
    GameModel *game;
    // 存储将点击的位置
    int clickPosRow;
    int clickPosCol;

    void drawBoard(QPainter& painter);
    void drawMark(QPainter& painter);
    void drawChess(QPainter& painter);

    void win(bool flag);
    void dead();
};

#endif // GAMEWIDGET_H
