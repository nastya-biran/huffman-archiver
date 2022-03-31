#pragma once

#include <iostream>
#include <vector>

class BitReader {
public:
    BitReader(std::istream &in) : in_(in) {
    }

    std::vector<bool> ReadNBits(int32_t n);

    const std::vector<bool> &GetBuffer() const;

    void ReviveBuffer(std::vector<bool> buff);

private:
    std::vector<bool> buffer_;
    const size_t MAX_BUFFER_SIZE_ = 50;
    std::istream &in_;
    const size_t BYTE_SIZE = 8;

    std::vector<bool> CharToBool(unsigned char c);
};