#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>

#include "bottombar.h"

BottomBar::BottomBar(GameWidget* gameWidget, QWidget *parent) : QWidget(parent) {
    QHBoxLayout* barLayout = new QHBoxLayout(this);
    setLayout(barLayout);

    QLabel* chooseLabel = new QLabel("Choose AI: ", this);
    chooseLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    barLayout->addWidget(chooseLabel);

    QComboBox* chooseAI = new QComboBox(this);
    chooseAI->addItem("None");
    chooseAI->addItem("White");
    chooseAI->addItem("Black");
//    connect(chooseAI, &QComboBox::currentTextChanged, gameWidget, &GameWidget::setAI);
    barLayout->addWidget(chooseAI);

    QLabel* depthLabel = new QLabel("Search Depth", this);
    depthLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    barLayout->addWidget(depthLabel);

    QSpinBox* searchDepth = new QSpinBox(this);
    searchDepth->setValue(2);
    searchDepth->setRange(1, 3);
    barLayout->addWidget(searchDepth);
}
