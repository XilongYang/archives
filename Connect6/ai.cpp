#include <QDebug>
#include <QRandomGenerator>
#include <climits>


#include "ai.h"

namespace {

};

AI::AI(QVector<QVector<int>> gameMap) : numOf(3, 0)
    , os{0, 0, 2, 20, 65535, 65535, 65535}, ms{0, 0, 1, 10, 35, 35, 999999}{
    gameMapVec = gameMap;

}

int AI::value() {
    return getTotalScore(AI_WHITE);
}

QPair<Pos, Pos> AI::nextStep(int color) {
    Pos fst = {-1, -1};
    Pos snd = {-1, -1};
    int maxScore = INT_MIN;
    int num = 0;
    for (int y1 = 0; y1 < boardSize; ++y1) {
        for (int x1 = 0; x1 < boardSize; ++x1) {
            for (int y2 = 0; y2 < boardSize; ++y2) {
                for (int x2 = 0; x2 < boardSize; ++x2) {
                    // 第一个点始终在第二个点之前
                    if (y1 * boardSize + x1 >= y2 * boardSize + x2) {
                        continue;
                    }
                    // 目标点有棋子，或周围两圈都没有棋子则跳过该点
                    if (gameMapVec[y1][x1] != CHESS_NONE
                            || gameMapVec[y2][x2] != CHESS_NONE
                            || !hasChessAround(Pos{x1, y1})
                            || !hasChessAround(Pos{x2, y2})){
                        continue;
                    }
                    // 在目标点下子，计算评分，若评分大于最大评分则采用。若评分等于最大评分则随机采用其中一种。
                    gameMapVec[y1][x1] = (color == AI_WHITE) ? CHESS_WHITE : CHESS_BLACK;
                    gameMapVec[y2][x2] = (color == AI_WHITE) ? CHESS_WHITE : CHESS_BLACK;
                    int curScore = getTotalScore(color);
                    if (curScore > maxScore) {
                        maxScore = curScore;
                        // num为可评分等于最大评分的情况数
                        num = 1;
                        fst.X = x1;
                        fst.Y = y1;
                        snd.X = x2;
                        snd.Y = y2;
                    } else if (curScore == maxScore) {
                        // 随机采用
                        ++num;
                        int rand = QRandomGenerator::global()->bounded(1, num);
                        if (rand == 1) {
                            fst.X = x1;
                            fst.Y = y1;
                            snd.X = x2;
                            snd.Y = y2;
                        }
                    }
                    // 复原棋盘
                    gameMapVec[y1][x1] = CHESS_NONE;
                    gameMapVec[y2][x2] = CHESS_NONE;
                } // for x2
            } // for y2
        } // for x1
    } // for y1
    return QPair<Pos, Pos>{fst, snd};
}

void AI::push(int flag) {
    // 元素多于6个时，推出
    while (queue.size() >= 6) {
        --numOf[queue.front()];
        queue.pop_front();
    }
    // 推入元素
    queue.push_back(flag);
    numOf[flag]++;
}

int AI::getTotalScore(int color) {
    int score = 0;
    score += forwardScore(VERTICAL, color);
    score += forwardScore(HORIZON, color);
    score += forwardScore(LEFT_TOP_TO_RIGHT_BOTTOM, color);
    score += forwardScore(RIGHT_TOP_TO_LEFT_BOTTOM, color);
    return score;
}

int AI::forwardScore(int forward, int color) {
    int score = 0;
    if (forward == VERTICAL) {
        score += search(color, [](int, int j){return j;}
        , [](int i, int){return i;});
    } else if (forward == HORIZON) {
        score += search(color, [](int i, int){return i;}
        ,[](int, int j){return j;});
    } else if (forward == LEFT_TOP_TO_RIGHT_BOTTOM) {
        score += search(color, [](int, int j){return j;}
        ,[](int i, int j){return i + j;});
        score += search(color, [](int i, int j){return i + j;}
        ,[](int, int j){return j;}, {0, 1});
    } else if (forward == RIGHT_TOP_TO_LEFT_BOTTOM) {
        score += search(color, [](int, int j){return j;}
        ,[](int i, int j){return i - j;});
        score += search(color, [](int i, int j){return i + j;}
        ,[](int, int j){return boardSize - 1 - j;}, {0, 1});
    }
    return score;
}

int AI::search(int color, function<int (int, int)> y
                , function<int (int, int)> x, Pos startPos) {
    auto isVaild = [](int a) {
        return a >= 0 && a < boardSize;
    };
    int score = 0;
    int otherColor = (color == AI_BLACK) ? AI_WHITE : AI_BLACK;
    for (int i = startPos.Y; i < boardSize; ++i) {
        queue.clear();
        numOf = {0, 0, 0};
        for (int j = startPos.X; j < boardSize; ++j) {
            int curX = x(i, j);
            int curY = y(i, j);
            if (!isVaild(curX) || !isVaild(curY)) {
                continue;
            }
            push(gameMapVec[curY][curX]);
            if (queue.size() < 6) {
                continue;
            }
            score += ms[getScore(color)];
            score -= os[getScore(otherColor)];
        }
    }
    return score;
}

int AI::getScore(int color) {
    if (color == AI_BLACK && numOf[CHESS_WHITE] == 0) {
        return numOf[CHESS_BLACK];
    } else if (color == AI_WHITE && numOf[CHESS_BLACK] == 0) {
        return numOf[CHESS_WHITE];
    }
    return 0;
}

bool AI::hasChessAround(Pos pos) {
    // 使x,y属于区间[2,boardSize - 2]
    int x = (pos.X > 2) ? pos.X : 2;
    x = (x < boardSize - 3) ? x : boardSize - 3;

    int y = (pos.Y > 2) ? pos.Y : 2;
    y = (y < boardSize - 3) ? y : boardSize - 3;

    // 将(x,y)及包围它的两圈点值相加，结果为0则区域为空
    int sum = 0;
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            sum += gameMapVec[y + i][x + j];
        }
    }
    return sum != 0;
}
