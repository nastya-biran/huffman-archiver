#pragma once

#include <iostream>
#include <vector>


class BitWriter {
public:
    BitWriter(std::ostream &out) : out_(out) {
    }


    void AddBits(std::vector<bool> more_bites, bool convert_to_9bytes);

    void AddBits(size_t number, bool convert_to_9bytes);

    void CheckBuffer();

private:
    std::ostream &out_;
    std::vector<bool> buffer_;
    const size_t BYTE_SIZE = 8;
    const size_t CHAR9_SIZE = 9;

    void Write();

    unsigned char BoolToChar(const std::vector<bool> &bits);

    std::vector<bool> IntToBool(size_t c);


};