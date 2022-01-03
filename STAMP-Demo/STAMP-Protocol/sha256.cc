#include "stamp.h"

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <array>

using std::array;

namespace {
    // 循环左移
    template<typename T>
    inline T CROL(const T &input, size_t bits) {
        size_t size = sizeof(input) * 8;
        return ((input << bits) | (input >> (size - bits)));
    }

    // 循环右移
    template<typename T>
    inline T CROR(const T &input, size_t bits) {
        size_t size = sizeof(input) * 8;
        return ((input >> bits) | (input << (size - bits)));
    }

    // SHA256算法的8个哈希初值。
    // 这些初值是对自然数中的前8个质数(2,3,5,7,11,13,17,19)的平方根小数部分取前32bit得到的
    const array<uint32_t, 8> h_init =
        {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a
        ,0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

    // SHA256算法中用到的64个常数。
    // 这些常数是对自然数中的前64个质数(2,3,...,311)的立方根小数部分取前32bit得到的
    const array<uint32_t, 64> k =
        {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b
        ,0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01
        ,0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7
        ,0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc
        ,0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152
        ,0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147
        ,0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc
        ,0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85
        ,0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819
        ,0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08
        ,0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f
        ,0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208
        ,0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

    // 对数据包进行预处理，以满足算法需要。
    Packet pretreat(const Packet &packet) {
        // 对数据包末尾进行填充，使得数据包大小对512取模后余数为448。
        // 填充部分第一个位是1，其后全为0。
        // 注意1: 即使数据包大小对512取模已经是448了，仍要进行填充，这种情况下填充512位。
        // 注意2: 为什么是448？因为这步完成后下一步会填充一个64bit的值，64+448正好等于512。
        // 这里实际上进行的是以字节为单位的运算, 因此将上述bit转为相应字节
        // 512 / 8
        constexpr uint32_t unit_byte = 64;
        // 448 / 8
        constexpr uint32_t target_byte = 56;
        // 第一个填充的字节，值为10000000
        constexpr uint8_t first_append = 0x80;

        int32_t need_size = target_byte - (packet.size() % unit_byte);
        need_size += (need_size <= 0) ? unit_byte : 0;

        // 进行上述填充后还需在数据包末尾添加一个64bit的数字，表示填充前大小
        const uint64_t origin_size = packet.size() * 8;

        Packet result(packet.size() + need_size + sizeof(origin_size));
        memcpy(result.get(), packet.get(), packet.size());
        result.get()[packet.size()] = first_append;
        // 以大端序填充
        *(uint64_t*)(result.get() + result.size() - sizeof(origin_size))
            = hton_any(origin_size);
        return result;
    }
    // 定义相关函数
    inline uint32_t EP0(uint32_t x) {
        return CROR(x, 2) ^ CROR(x, 13) ^ CROR(x, 22);
    };
    inline uint32_t EP1(uint32_t x) {
        return CROR(x, 6) ^ CROR(x, 11) ^ CROR(x, 25);
    };
    inline uint32_t CH(uint32_t x, uint32_t y, uint32_t z) {
        return ((x & y) ^ ((~x) & z));
    };
    inline uint32_t MAJ(uint32_t x, uint32_t y, uint32_t z) {
        return ((x & y) ^ (x & z) ^ (y & z));
    };
}

// 对数据包使用sha256算法生成一个256bit的信息摘要，以数据包的方式返回
Packet sha256(const Packet &message) {
    auto packet = pretreat(message);
    // 将包分割成512bit大的chunk
    auto chunk_num = packet.size() / 64;
    auto H = h_init;
    for (size_t i = 0; i < chunk_num; ++i) {
        auto begin = i * 64;
        // 将chunk分割成64个32bit的块
        array<uint32_t, 64> w;
        for (size_t i = 0; i < 16; ++i) {
            uint32_t value = *(reinterpret_cast<uint32_t*>(packet.get()
                + begin + i * 4));
            // 转换为机器字节序。
            w[i] = ntoh_any(value);
        }
        for (size_t i = 16; i < 64; ++i) {
            auto s0 = CROR(w[i - 15], 7) ^ CROR(w[i - 15], 18) ^ (w[i - 15] >> 3);
            auto s1 = CROR(w[i - 2], 17) ^ CROR(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        // 初始化hash值
        auto h = H;
        // 根据64个块与k值更新hash值
        for (size_t i = 0; i < 64; ++i) {
            auto t1 = h[7] + EP1(h[4]) + CH(h[4], h[5], h[6]) + k[i] + w[i];
            auto t2 = EP0(h[0]) + MAJ(h[0], h[1], h[2]);
            for (size_t i = 7; i > 0; --i) {
                h[i] = h[i - 1];
                if (i == 4) {
                    h[i] += t1;
                }
            }
            h[0] = t1 + t2;
        }
        // 为下一个chunk更新hash值
        for (size_t i = 0; i < 8; ++i) {
            H[i] += h[i];
        }
    }
    Packet result(32);
    for (size_t i = 0; i < 8; ++i) {
        uint32_t* target = reinterpret_cast<uint32_t*>(result.get() + i * 4);
        *target = hton_any(H[i]);
    }
    return result;
}
