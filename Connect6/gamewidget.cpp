#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QMouseEvent>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <math.h>

#include "gamewidget.h"

namespace  {
    #define WIN_SOUND ":/win.wav"
    #define DEAD_SOUND ":/dead.wav"
    #define CHESS_SOUND ":/chess.wav"
    // 棋盘边缘空隙
    const int boardMargin = 45;
    // 棋子半径
    const int radius = 14;
    const int posRadius = 3;
    // 落子标记边长
    const int markSize = 6;
    // 格子的大小
    const int blockSize = 35;
    // 鼠标点击的模糊距离上限
    const int posDelta = 20;
}

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    setFixedSize(boardMargin * 2 + blockSize * (boardSize - 1)
                 , boardMargin * 2 + blockSize * (boardSize - 1));
    setMouseTracking(true);

    game = new GameModel;
    connect(game, &GameModel::win, this, &GameWidget::win);
    connect(game, &GameModel::dead, this, &GameWidget::dead);
    connect(game, &GameModel::changed, this, &GameWidget::generateChange);
    // 开始游戏
    initGame();
}

GameWidget::~GameWidget() {
    if (game)
    {
        delete game;
        game = nullptr;
    }
}

void GameWidget::initGame() {
    // 初始化游戏模型
    game->startGame();
    update();
}

void GameWidget::takeBack() {
    game->takeBack();
}

void GameWidget::setAI(const QString& AI) {
    if (AI == "None") {
        game->setAI(AI_NONE);
    } else if (AI == "Black") {
        game->setAI(AI_BLACK);
    } else if (AI == "White") {
        game->setAI(AI_WHITE);
    }
}

void GameWidget::generateChange(int score) {
    emit scoreChanged(QString::number(score));
    QSound::play(CHESS_SOUND);
    update();
}

void GameWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    drawBoard(painter);
    drawMark(painter);
    drawChess(painter);
}

void GameWidget::mouseMoveEvent(QMouseEvent *event)
{
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 鼠标不能出界
    if (x >= 0 && x < size().width() && y >= 0 && y < size().height()) {
        // 获取最近的左上角的点
        int col = (x - boardMargin) / blockSize;
        int row = (y - boardMargin) / blockSize;

        int leftTopPosX = boardMargin + blockSize * col;
        int leftTopPosY = boardMargin + blockSize * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        clickPosRow = -1; // 初始化最终的值
        clickPosCol = -1;

        // 确定一个误差在范围内的点，且只可能确定一个出来
        int minLen = posDelta;
        for (int i = 0; i <= 1; ++i) {
            for (int j = 0; j <= 1; ++j) {
                int deltaX = x - leftTopPosX - i * blockSize;
                int deltaY = y - leftTopPosY - j * blockSize;
                int len = sqrt(deltaX * deltaX + deltaY	* deltaY);
                if (len < minLen) {
                    minLen = len;
                    clickPosCol = col + i;
                    clickPosRow = row + j;
                }
            } // for j
        } // for i
    } // if x,y
    update();
}

void GameWidget::mouseReleaseEvent(QMouseEvent *)
{
    game->humanAction(clickPosRow, clickPosCol);
}

void GameWidget::drawBoard(QPainter& painter) {
    // 绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    for (int i = 0; i < boardSize; i++) {
        painter.drawLine(boardMargin + blockSize * i, boardMargin
                         , boardMargin + blockSize * i, size().height() - boardMargin);
        painter.drawLine(boardMargin, boardMargin + blockSize * i
                         , size().width() - boardMargin, boardMargin + blockSize * i);

        painter.drawText(boardMargin * 0.8 + blockSize * i, boardMargin / 2,  QString::number(i + 1));
        painter.drawText(5, boardMargin + blockSize * i , QString::number(i + 1));
    }

    // 绘制星位
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int row = 3 + 6 * i;
            int col = 3 + 6 * j;
            brush.setColor(Qt::black);
            painter.setBrush(brush);
            painter.drawEllipse(boardMargin + blockSize * col - posRadius
                                , boardMargin + blockSize * row - posRadius
                                , 2 * posRadius, 2 * posRadius);
        } // for j
    } // for i
}

void GameWidget::drawMark(QPainter& painter) {
    // 绘制落子标记
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (clickPosRow >= 0 && clickPosRow < boardSize &&
            clickPosCol >= 0 && clickPosCol < boardSize &&
            game->pos(clickPosRow, clickPosCol) == 0) {
        if (game->flag() < 2) {
            brush.setColor(Qt::black);
        } else {
            brush.setColor(Qt::white);
        }
        painter.setBrush(brush);
        painter.drawRect(boardMargin + blockSize * clickPosCol - markSize
                         , boardMargin + blockSize * clickPosRow - markSize
                         , markSize * 2, markSize * 2);
    }
}

void GameWidget::drawChess(QPainter& painter) {
    // 绘制棋子
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++){
            if (game->pos(i, j) == CHESS_BLACK) {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(boardMargin + blockSize * j - radius
                                    , boardMargin + blockSize * i - radius
                                    , radius * 2, radius * 2);
            }
            else if (game->pos(i, j) == CHESS_WHITE) {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(boardMargin + blockSize * j - radius
                                    , boardMargin + blockSize * i - radius
                                    , radius * 2, radius * 2);
            }
        } // for j
    } // for i
}

void GameWidget::win(bool flag) {
    QSound::play(WIN_SOUND);
    QString str;
    if (flag) {
        str = "black player";
    } else {
        str = "white player";
    }
    QMessageBox::StandardButton btnValue = QMessageBox::information(this, "congratulations", str + "win!");
    if (btnValue == QMessageBox::Ok) {
        game->startGame();
        update();
    }
}

void GameWidget::dead() {
    QSound::play(DEAD_SOUND);
    QMessageBox::StandardButton btnValue = QMessageBox::information(this, "oops", "dead game!");
    if (btnValue == QMessageBox::Ok) {
        game->startGame();
        update();
    }
}
