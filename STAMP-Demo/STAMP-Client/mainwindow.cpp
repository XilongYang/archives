#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUdpSocket>
#include <QScrollBar>
#include <QNetworkDatagram>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), key(0)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setText("STAMP Client Runing....\n");
    connect(ui->ping, &QPushButton::clicked, this, &MainWindow::ping);
    connect(ui->key, &QLineEdit::textChanged, this, &MainWindow::changeKey);
    connect(ui->mode, &QComboBox::currentTextChanged, this, &MainWindow::changeMode);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 与服务端通信
void MainWindow::ping()
{
    showMessage("\nStart Testing..........\n");
    QUdpSocket socket;
    socket.bind(QHostAddress(ui->ipEdit->text()));
    int testTime = ui->testTime->value();
    int successTime = 0;
    for (int i = 0; i < testTime; ++i) {
        Packet test = generatePacket(i);
        showMessage("Sending packet...\n");
        size_t n = socket.writeDatagram((char*)test.get(), test.size(), QHostAddress(ui->ipEdit->text())
                                         , ui->portEdit->text().toInt());
        if (n != test.size()) {
            showMessage(socket.errorString() + "\n");
        }
        showMessage("Waiting response...\n");

        if (socket.waitForReadyRead(timeout)) {
            Packet back((auth_mode) ? 112 : 44);
            socket.readDatagram((char*)back.get(), back.size());
            // memcmp匹配成功返回0
            if (!memcmp(back.get(), "Verify Failed", 14)) {
                showMessage("Verify Failed\n");
                break;
            }
            auto delay = computingDelay(back);
            showMessage("Success: " + QString::number(delay) + " (ms)\n");
            ++successTime;
        } else {
            showMessage("Timeout\n");
        }
    }
    showMessage("Testing finish: received " + QString::number(successTime) + " packets of "
                + QString::number(testTime) + " packets. "
                + QString::number(100.0 * (testTime - successTime) / testTime)
                + "% packets lose.\n");
}

// 生成发送包
Packet MainWindow::generatePacket(int n)
{
    showMessage("Buliding Test Packet(" + QString::number(n) + "): ");
    showMessage((auth_mode) ? "Authenticated Mode\n" : "Unauthenticated Mode\n");
    Packet pkt((auth_mode) ? 112 : 44);
    uint32_t squenceNum = hton_any(n);
    char *cur = reinterpret_cast<char*>(pkt.get());

    // Squence Number
    memcpy(cur, &squenceNum, sizeof(squenceNum));
    cur += sizeof(squenceNum);

    // MBZ1
    if (auth_mode) {
        cur += 12;
    }

    // Timestamp
    Packet timestamp = get_timestamp();
    memcpy(cur, timestamp.get(), timestamp.size());
    cur += timestamp.size();

    // Error Estimate
    // S = 0, Z = 0, Scale = 0, Multiple = 1
    uint16_t errorEstimate = 0x0001;
    errorEstimate = hton_any(errorEstimate);
    memcpy(cur, &errorEstimate, sizeof(errorEstimate));
    cur += sizeof(errorEstimate);

    //MBZ2
    cur += (auth_mode) ? 70 : 30;

    //HMAC
    if (auth_mode) {
        Packet hmac(96);
        memcpy(hmac.get(), pkt.get(), 96);
        hmac = hmac_sha256(hmac, key);
        memcpy(cur, hmac.get(), 16);
    }
    return pkt;
}

// 跟据返回包计算时延
double MainWindow::computingDelay(const Packet &received)
{
    auto get_time = [received](uint32_t pos) {
        uint32_t num;
        memcpy(&num, received.get() + pos, sizeof(num));
        num = ntoh_any(num);
        return num;
    };

    // STAMP Reflector Receive Timestamp
    const uint32_t rtime_pos = (auth_mode) ? 32 : 16;
    uint32_t receive_sec = get_time(rtime_pos);
    uint32_t receive_nsec = get_time(rtime_pos + sizeof(receive_sec));

    // STAMP Sender Timestamp
    const uint32_t stime_pos = (auth_mode) ? 64 : 28;
    uint32_t send_sec = get_time(stime_pos);
    uint32_t send_nsec = get_time(stime_pos + sizeof(send_sec));

    return (receive_sec - send_sec) * 1000 + (receive_nsec - send_nsec) / 1000000.0;
}

// 显示消息
void MainWindow::showMessage(const QString &message)
{
    auto textEdit = ui->textEdit;
    textEdit->setText(textEdit->toPlainText() + message);
    textEdit->verticalScrollBar()->setValue(textEdit->verticalScrollBar()->maximum());
}

// 改变密钥
void MainWindow::changeKey(const QString &k)
{
    Packet newKey(k.size());
    memcpy(newKey.get(), k.toStdString().c_str(), sizeof(k));
    key = newKey;
}

// 改变验证模式
void MainWindow::changeMode(const QString &mode)
{
    if (mode == "Unauthenticated") {
        auth_mode = false;
    } else {
        auth_mode = true;
    }
}
