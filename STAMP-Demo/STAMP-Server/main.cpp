#include <QCoreApplication>
#include <QDebug>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>
#include <cstring>
#include <unistd.h>
#include "stamp.h"
#include "config.h"

QUdpSocket udpSocket;

bool vailify(const Packet &received_packet);
Packet generatePacket(int n, const Packet &received_packet, const Packet &receive_timestamp);

Packet key(sizeof(key_str));

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    memcpy(key.get(), key_str, sizeof(key_str));

    if (!udpSocket.bind(QHostAddress::LocalHost, port)) {
        perror("Error while bind port");
        a.exit(-1);
    }
    while(true) {
        while(udpSocket.waitForReadyRead(-1)) {
            // 接收时间戳，刻不容缓
            Packet receive_timestamp = get_timestamp();
            // 构建包
            Packet receive((auth_mode) ? 112 : 44);
            QHostAddress *sender_addr = new QHostAddress();
            quint16 *sender_port = new quint16(0);
            udpSocket.readDatagram((char*)receive.get(), receive.size(), sender_addr, sender_port);

            qDebug() << "Received Packet From:" << sender_addr->toString() << *sender_port;

            // 验证并返回包
            if (vailify(receive)) {
                Packet back = generatePacket(0, receive, receive_timestamp);
                udpSocket.writeDatagram((char*)back.get(), back.size(), *sender_addr, *sender_port);
            } else {
                udpSocket.writeDatagram("Verify Failed", *sender_addr, *sender_port);
            }
        }
    }
    return a.exec();
}

// 验证收到的包
bool vailify(const Packet &received_packet)
{
    // Error Estimate校验, Multiple为0的包需要丢弃
    const uint32_t multiple_pos = (auth_mode) ? 25 : 13;
    if (received_packet.get()[multiple_pos] == 0) {
        return false;
    }
    // HMAC校验
    if (auth_mode) {
        if (received_packet.size() != 112) {
            return false;
        }
        Packet hmac(96);
        memcpy(hmac.get(), received_packet.get(), 96);
        hmac = hmac_sha256(hmac, key);

        Packet received_hmac(16);
        memcpy(received_hmac.get() ,received_packet.get() + 96, 16);
        for (int i = 0; i < 16; ++i) {
            if (received_hmac.get()[i] != hmac.get()[i]) {
                return false;
            }
        }
    }
    return true;
}

// 生成返回包
Packet generatePacket(int n, const Packet &received_packet, const Packet &receive_timestamp)
{
    Packet pkt((auth_mode) ? 112 : 44);
    char *cur = reinterpret_cast<char*>(pkt.get());
    // Sequence Number
    uint32_t sequence = (state_mode) ? n : ntoh_any(*reinterpret_cast<const uint32_t*>(received_packet.get()));
    memcpy(cur, &sequence, sizeof(sequence));
    cur += sizeof(sequence);
    // MBZ1
    if (auth_mode) {
        cur += 12;
    }
    // Timestamp
    Packet timestamp = get_timestamp();
    memcpy(cur, timestamp.get(), timestamp.size());
    cur += timestamp.size();
    // ErrorEstimate
    // S = 0, Z = 0, Scale = 0, Multiple = 1
    uint16_t error_estimate = 0x0001;
    memcpy(cur, &error_estimate, sizeof(error_estimate));
    cur += sizeof(error_estimate) + 2;
    // MBZ2
    if (auth_mode) {
        cur += 4;
    }
    // Receive Timestamp
    memcpy(cur, receive_timestamp.get(), receive_timestamp.size());
    cur += receive_timestamp.size();
    // MBZ3
    if (auth_mode) {
        cur += 8;
    }
    // Receive Packet
    if (auth_mode) {
        memcpy(cur, received_packet.get(), 32);
        cur += 32;
    } else {
        memcpy(cur, received_packet.get(),14);
        cur += 14;
    }
    // TTL
    cur[0] = 1;
    // MBZ4
    if (auth_mode) {
        cur += 16;
    }
    // HMAC
    if (auth_mode) {
        Packet hmac(96);
        memcpy(hmac.get(), pkt.get(), 96);
        hmac = hmac_sha256(hmac, key);
        memcpy(cur, hmac.get(), 16);
    }
    return pkt;
}

