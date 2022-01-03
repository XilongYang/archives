#ifndef AI_H
#define AI_H

#include <QVector>
#include <QPair>
#include <QQueue>

#include <functional>
using std::function;

// 棋盘尺寸
const int boardSize = 19;
//几子为胜
const int numOfConnect = 6;

#define X first
#define Y second

enum ChessFlags {
    CHESS_NONE = 0,
    CHESS_BLACK = 1,
    CHESS_WHITE = 2
};

enum AIFlags {
    AI_NONE = 0,
    AI_BLACK = 1,
    AI_WHITE = 2,
};

enum ForwardFlags {
    VERTICAL = 0,
    HORIZON = 1,
    LEFT_TOP_TO_RIGHT_BOTTOM = 2,
    RIGHT_TOP_TO_LEFT_BOTTOM = 3
};

using Pos = QPair<int, int>;

class AI {
public:
    explicit AI(QVector<QVector<int>> gameMap);
    int value();
    QPair<Pos, Pos> nextStep(int color);
private:
    QVector<QVector<int>> gameMapVec;

    // 搜索用窗口, 是一个最大大小为6的队列
    QQueue<int> queue;
    // 存储窗口中上各棋子和空位的数目
    QVector<int> numOf;

    // 评分依据
    const QVector<int> os;
    const QVector<int> ms;

    // 将某点推入当前窗口中
    void push(int chess);

    // 使用滑动窗口计算各方向得分, 加和得到棋盘得分
    int getTotalScore(int color);
    int forwardScore(int forward, int color);
    int search(int color, function<int(int, int)> x
               , function<int(int, int)> y, Pos startPos = {0, 0});

    // 计算当前窗口评分
    int getScore(int color);

    // 查看某点附近两圈内是否有棋子
    bool hasChessAround(Pos pos);
};

#endif // AI_H
