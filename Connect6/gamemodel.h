#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// ---- 游戏模型类 ---- //
#include <QVector>
#include <QStack>
#include <QObject>

#include "ai.h"

enum PlayerFlags {
    BLACK1 = 0,
    BLACK2 = 1,
    WHITE1 = 2,
    WHITE2 = 3
};

class GameModel : public QObject
{
    Q_OBJECT
public:
    int pos(int row, int col);
    int flag();

    void startGame();
    void humanAction(int row, int col);
    void AIAction();
    void takeBack();

    void setAI(AIFlags flag);
signals:
    // 黑方胜则flag置为true
    void win(bool flag);
    void dead();
    void changed(int score);
private:
    int playerFlag;
    int AIFlag = AI_NONE;

    // 标识是否刚开局，供AI做特判
    bool onStart;

    // 存储当前游戏棋盘和棋子的情况，值为ChessFlags
    QVector<QVector<int>> gameMapVec;
    // 存储历史存列，悔棋用
    QStack<QPair<int, int>> gameStack;

    void changePlayer(bool forward = true);

    void action(int row, int col);

    void check(int row, int col);
    void checkDead();
    //给定一点与一个方向失量，检查是否符合胜利条件
    bool checkWin(int row, int col, int x, int y);
};

#endif // GAMEMODEL_H
