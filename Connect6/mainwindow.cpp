#include <QIcon>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>

#include "mainwindow.h"
#include "gamewidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowIcon(QIcon(":/icon.jpg"));

    GameWidget* gameWidget = new GameWidget(this);
    setCentralWidget(gameWidget);
    setFixedSize(gameWidget->width(), gameWidget->height() + menuBar()->height() + statusBar()->height());

    QAction* restart = new QAction("Restart", this);
    connect(restart, &QAction::triggered, gameWidget, &GameWidget::initGame);
    menuBar()->addAction(restart);

    QAction* back = new QAction("Take back", this);
    connect(back, &QAction::triggered, gameWidget, &GameWidget::takeBack);
    menuBar()->addAction(back);

    QLabel* chooseLabel = new QLabel("Choose AI", this);
    statusBar()->addPermanentWidget(chooseLabel);

    QComboBox* chooseAI = new QComboBox(this);
    chooseAI->addItem("None");
    chooseAI->addItem("White");
    chooseAI->addItem("Black");
    connect(chooseAI, &QComboBox::currentTextChanged, gameWidget, &GameWidget::setAI);
    statusBar()->addPermanentWidget(chooseAI);

    QLabel* scoreLabel = new QLabel("Score: ", this);
    statusBar()->addWidget(scoreLabel);

    QLabel* score = new QLabel("0", this);
    connect(gameWidget, &GameWidget::scoreChanged, score, &QLabel::setText);
    statusBar()->addWidget(score);
}
