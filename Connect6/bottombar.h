#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QWidget>

#include "gamewidget.h"

class BottomBar : public QWidget
{
    Q_OBJECT
public:
    explicit BottomBar(GameWidget* gameWidget, QWidget *parent = nullptr);
};

#endif // BOTTOMBAR_H
