#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stamp.h"

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ping();
private:
    Packet key;
    Ui::MainWindow *ui;
    bool auth_mode = false;
    unsigned int timeout = 2000;

    inline void showMessage(const QString &message);
    Packet generatePacket(int n);
    double computingDelay(const Packet &received);
    void changeMode(const QString& mode);
    void changeKey(const QString& key);
};
#endif // MAINWINDOW_H
