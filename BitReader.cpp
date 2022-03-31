#include "BitReader.h"
#include <algorithm>
#include <fstream>


std::vector<bool> BitReader::ReadNBits(int32_t n) {
    if (static_cast<size_t>(n) > buffer_.size()) {
        while (buffer_.size() < MAX_BUFFER_SIZE_ && in_.peek() != EOF) {
            unsigned char c = in_.get();
            std::vector<bool> more_bits = CharToBool(c);
            buffer_.insert(buffer_.end(), more_bits.begin(), more_bits.end());
        }
    }
    std::vector<bool> bits;
    std::copy(buffer_.begin(), buffer_.begin() + n, std::back_inserter(bits));
    buffer_.erase(buffer_.begin(), buffer_.begin() + n);
    return bits;
}

std::vector<bool> BitReader::CharToBool(unsigned char c) {
    std::vector<bool> bits;
    for (size_t i = 0; i < BYTE_SIZE; ++i) {
        bits.push_back((c & (1 << i)));
    }
    std::reverse(bits.begin(), bits.end());
    return bits;
}

const std::vector<bool> &BitReader::GetBuffer() const {
    return buffer_;
}

void BitReader::ReviveBuffer(std::vector<bool> buff) {
    buffer_ = buff;
}
