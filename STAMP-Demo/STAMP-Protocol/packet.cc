#include "stamp.h"
#include <stdexcept>
#include <cstdio>

Packet::Packet(size_t size) : size_(size), data_(nullptr) {
    create_data(size_);
}

Packet::~Packet() {
    if (data_ != nullptr) {
        delete[] data_;
    }
}

Packet::Packet(const Packet &packet) : size_(packet.size_), data_(nullptr) {
    create_data(size_);
    memcpy(data_, packet.data_, size_);
}

Packet::Packet(Packet &&packet) : size_(packet.size_), data_(nullptr) {
    if (data_ != nullptr) {
        delete[] data_;
    }
    data_ = std::move(packet.data_);
    packet.data_ = nullptr;
    size_ = packet.size_;
}

Packet& Packet::operator=(const Packet &packet) {
    create_data(packet.size_);
    memcpy(data_, packet.data_, size_);
    return *this;
}

Packet& Packet::operator=(Packet &&packet) {
    if (data_ != nullptr) {
        delete[] data_;
    }
    data_ = std::move(packet.data_);
    packet.data_ = nullptr;
    size_ = packet.size_;
    return *this;
}

size_t Packet::size() const {
    return size_;
}

uint8_t *Packet::get() {
    return data_;
}

const uint8_t *Packet::get() const {
    return data_;
}

void Packet::print() const {
    for (size_t i = 0; i < size_; ++i) {
        uint8_t value = data_[i];
        printf("%.2x ", value);
        if ((i + 1) % 4 == 0) {
            putchar('\n');
        }
    }
    putchar('\n');
}

void Packet::create_data(size_t size) {
    if (data_ != nullptr) {
        delete[] data_;
    }
    data_ = new uint8_t[size];
    if (data_ == nullptr) {
        throw std::runtime_error("Fail to create data");
    }
    size_ = size;
    memset(data_, 0, size_);
}
