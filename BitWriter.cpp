#include "BitWriter.h"



void BitWriter::AddBits(size_t number, bool convert_to_9bytes) {
    std::vector<bool> more_bits = IntToBool(number);
    if (convert_to_9bytes) {
        more_bits.insert(more_bits.end(), CHAR9_SIZE - more_bits.size(), false);
    }
    buffer_.insert(buffer_.end(), more_bits.begin(), more_bits.end());
    Write();
}

void BitWriter::AddBits(std::vector<bool> more_bits, bool convert_to_9bytes) {
    if (convert_to_9bytes) {
        more_bits.insert(more_bits.end(), CHAR9_SIZE - more_bits.size(), false);
    }
    buffer_.insert(buffer_.end(), more_bits.begin(), more_bits.end());
    Write();
}

void BitWriter::Write() {
    if (buffer_.size() >= BYTE_SIZE) {
        std::vector<bool> byte;
        std::copy(buffer_.begin(), buffer_.begin() + BYTE_SIZE, std::back_inserter(byte));
        buffer_.erase(buffer_.begin(), buffer_.begin() + BYTE_SIZE);
        unsigned char c = BoolToChar(byte);
        out_.write(reinterpret_cast<const char *>(&c), 1);
        out_.flush();
    }
}

void BitWriter::CheckBuffer() {
    while (buffer_.size() >= BYTE_SIZE) {
        Write();
    }
    if (!buffer_.empty()) {
        buffer_.insert(buffer_.end(), BYTE_SIZE - buffer_.size(), false);
        Write();
    }
}

unsigned char BitWriter::BoolToChar(const std::vector<bool> &bits) {
    int32_t c = bits[0];
    for (size_t i = 1; i < BYTE_SIZE; ++i) {
        c = (c << 1);
        c = c + bits[i];
    }
    unsigned char cc = static_cast<unsigned char>(c);
    return cc;
}

std::vector<bool> BitWriter::IntToBool(size_t c) {
    std::vector<bool> more_bits;
    for (size_t i = 0; i < CHAR9_SIZE && c > 0; ++i) {
        more_bits.push_back((c & 1));
        c = (c >> 1);
    }
    return more_bits;
}
