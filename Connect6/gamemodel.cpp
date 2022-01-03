#include <utility>
#include <stdlib.h>
#include <time.h>
#include <QVector>
#include <QPair>
#include <QDebug>

#include "gamemodel.h"


int GameModel::pos(int row, int col) {
    return gameMapVec[row][col];
}

int GameModel::flag() {
    return playerFlag;
}

void GameModel::startGame() {
    // 初始棋盘
    gameMapVec.clear();
    gameMapVec = QVector<QVector<int>>(boardSize, QVector<int>(boardSize, 0));

    emit changed(0);

    // 开始时黑方只下一手，所以从黑2开始。
    playerFlag = BLACK2;

    onStart = true;

    AIAction();
}

void GameModel::humanAction(int row, int col) {
    if ((AIFlag == AI_BLACK && playerFlag <= BLACK2)
            || (AIFlag == AI_WHITE && playerFlag >= WHITE1)) {
        return;
    }
    action(row, col);
}

void GameModel::AIAction() {
    // 开局下在天元
    if (AIFlag == AI_BLACK && onStart) {
        action(9, 9);
        return;
    }

    if((AIFlag != AI_BLACK || playerFlag != BLACK1)
            && (AIFlag != AI_WHITE || playerFlag != WHITE1)) {
        return;
    }


    AI ai(gameMapVec);

    auto pair = ai.nextStep(AIFlag);
    auto fst = pair.first;
    auto snd = pair.second;
    qDebug() << Pos{fst.X + 1, fst.Y + 1};
    qDebug() << Pos{snd.X + 1, snd.Y + 1};
    action(fst.Y, fst.X);
    action(snd.Y, snd.X);
}

void GameModel::takeBack() {
    if (gameStack.empty()) {
        return;
    }
    int row = gameStack.top().first;
    int col = gameStack.top().second;
    gameMapVec[row][col] = CHESS_NONE;
    AI ai(gameMapVec);
    emit changed(ai.value());
    changePlayer(false);
    gameStack.pop();
    if (gameStack.empty()) {
        onStart = true;
        AIAction();
    }
    if (AIFlag == AI_WHITE && playerFlag >= WHITE1) {
        takeBack();
    }
    if (AIFlag == AI_BLACK && playerFlag <= BLACK2) {
        takeBack();
    }
}

void GameModel::setAI(AIFlags flag) {
    AIFlag = flag;
    AIAction();
}

void GameModel::changePlayer(bool forward) {
    if (forward) {
        playerFlag = (playerFlag + 1) % 4;
    } else {
        playerFlag -= 1;
        if (playerFlag < 0) {
            playerFlag += 4;
        }
    }
}

void GameModel::action(int row, int col) {
    auto vaild = [](int x) {
        return x >= 0 && x < boardSize;
    };
    if(!vaild(row) || !vaild(col) || gameMapVec[row][col] != CHESS_NONE) {
        return;
    }
    onStart = false;

    gameMapVec[row][col] = (playerFlag <= BLACK2) ? CHESS_BLACK : CHESS_WHITE;
    gameStack.push({row, col});
    AI ai(gameMapVec);
    emit changed(ai.value());
    // check前一定先changePlayer，否则会导致下一局异常。
    changePlayer();
    check(row, col);
    AIAction();
}

void GameModel::check(int row, int col) {
    // 竖,左斜,右斜三种情况,方向向量取左上，上，右上
    for (int i = -1; i <= 1; ++i) {
        if (checkWin(row, col, -1, i)) {
            return;
        }
    }
    // 横向情况，方向向量取左
    checkWin(row, col, 0, -1);
    checkDead();
}

void GameModel::checkDead() {
    // 所有空格全部填满
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++)
        {
            if (gameMapVec[i][j] == CHESS_NONE)
                return;
        }
    }
    emit dead();
}

bool GameModel::checkWin(int row, int col, int x, int y) {
    auto vaild = [](int row, int col) {
        return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
    };
    // 当判定点朝给定方向移动到底，然后反方向判断连子数是否达到numOfChess
    int flag = gameMapVec[row][col];
    if (vaild(row + y, col + x) && gameMapVec[row + y][col + x] == flag) {
        return checkWin(row + y, col + x, x, y);
    }
    for (int i = 1; i < numOfConnect; ++i) {
        if (!vaild(row - y * i, col - x * i)
            || gameMapVec[row - y * i][col - x * i] != flag) {
            return false;
        }
    }
    emit win(flag == CHESS_BLACK);
    return true;
}
