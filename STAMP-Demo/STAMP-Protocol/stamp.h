#ifndef STAMP_H
#define STAMP_H

#include <cstring>
#include <cstdint>
#include <cstdio>

/********************************************
** 数据管理类，对一个字节数组的生命周期进行管理
** Packet
** Packet::size() 获取资源大小
** Packet::get() 获取资源指针
*********************************************/
class Packet {
public:
    explicit Packet(size_t size);
    ~Packet();
    Packet(const Packet &packet);
    Packet(Packet &&Packet);
    Packet &operator=(const Packet &packet);
    Packet &operator=(Packet &&packet);
    size_t size() const;
    uint8_t *get();
    const uint8_t *get() const;
    void print() const;
private:
    size_t size_;
    uint8_t *data_;

    void create_data(size_t size);
};

/***********************************************************
** HMAC-SHA245算法
**********************************************************/
// 对数据包使用sha256算法生成一个256bit的信息摘要，以数据包的方式返回
Packet sha256(const Packet &message);

// 使用hmac_sha256生成一个256bit的信息摘要，以数据包的方式返回
Packet hmac_sha256(const Packet &message, const Packet &key_raw);

/***********************************************************
** 字节序转换
***********************************************************/
// 判断系统是大端序还是小端序
inline bool big_endian() {
    uint16_t value = 0x1234;
    uint8_t  low_value = *(reinterpret_cast<uint8_t*>(&value));
    return (low_value == 0x12);
}

// 对值进行大小端转换
template<typename T>
T hnswitch(const T &input) {
    T output(0);
    constexpr std::size_t size = sizeof(input);
    uint8_t *data = reinterpret_cast<uint8_t*>(&output);

    for (size_t i = 0; i < size; ++i) {
        data[i] = input >> ((size - i - 1) * 8);
    }

    return output;
}

// 小端转大端
template<typename T>
T hton_any(const T &input) {
    if (big_endian()) {
        return input;
    }
    return hnswitch(input);
}

// 大端转小端
template<typename T>
T ntoh_any(const T &input) {
    return hton_any(input);
}

// 以16进制逐字节打印值, 始终以大端序打印，无论机器使用大端或小端。
template<typename T>
void print_byte(const T &input) {
    const uint8_t *data
        = reinterpret_cast<const uint8_t*>(&input);
    auto show = [data, input](bool big_endian){
        size_t i = (big_endian) ? 0 : sizeof(input) - 1;
        while (i != ((big_endian) ? sizeof(input) : -1)) {
            uint8_t value = data[i];
            printf("%.2x ", value);
            size_t newline = (big_endian) ? i + 1 : i;
            if (newline % 8 == 0 && newline != 0) {
                putchar('\n');
            }
            i += (big_endian) ? 1 : -1;
        }
    };
    show(false);
    putchar('\n');
}

/*****************************************************
** 获取当前NTP格式时间戳
*****************************************************/
Packet get_timestamp();

#endif
