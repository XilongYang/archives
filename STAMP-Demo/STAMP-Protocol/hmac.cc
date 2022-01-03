#include "stamp.h"

namespace {
    constexpr uint8_t ipad = 0x36;
    constexpr uint8_t opad = 0x5C;

    constexpr size_t unit_size = 64;

    // 对密钥规整化处理
    inline Packet key_padding(const Packet &key_raw) {
        if (key_raw.size() > unit_size) {
            return sha256(key_raw);
        }
        Packet result(unit_size);
        memcpy(result.get(), key_raw.get(), key_raw.size());
        return result;
    }

    // 返回key与pad的循环序列进行xor运算的结果。
    inline Packet key_xor(const Packet &key, const uint8_t pad) {
        Packet result(key);
        auto begin = reinterpret_cast<uint8_t*>(result.get());
        for (size_t i = 0; i < result.size(); ++i) {
            begin[i] ^= pad;
        }
        return result;
    }

    inline Packet combine(const Packet &pad_key, const Packet &message) {
        Packet result(pad_key.size() + message.size());
        memcpy(result.get(), pad_key.get(), pad_key.size());
        memcpy(result.get() + pad_key.size(), message.get(), message.size());
        return result;
    }
}

// 使用密钥key_raw通过HMAC_SHA256算法生成message的信息摘要
Packet hmac_sha256(const Packet &message, const Packet &key_raw) {
    const auto key = key_padding(key_raw);
    const auto ipad_key = key_xor(key, ipad);
    const auto opad_key = key_xor(key, opad);
    auto result = combine(ipad_key, message);
    result = sha256(result);
    result = combine(opad_key, result);
    result = sha256(result);
    return result;
}
