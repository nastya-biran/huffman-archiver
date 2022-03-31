#pragma once

#include "BitReader.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>


class Decoder {
public:
    Decoder(const BitReader &bit_reader);

    bool WriteInitialFile(const std::unordered_map<std::vector<bool>, int32_t> &canonical_codes_for_decoding,
                          const std::vector<bool> &file_name_end, const std::vector<bool> &one_more_file,
                          const std::vector<bool> &archive_end);

    std::vector<bool> GetBuffer();
    const std::vector<int32_t> &GetCanonicalCodesLengths() const;
    const std::vector<int32_t> &GetAlphabet() const;

private:
    int32_t BoolToInt(const std::vector<bool> &bites);

    BitReader bit_reader_;
    std::vector<int32_t> alphabet_;
    std::vector<int32_t> canonical_codes_lengths_;
    const size_t BYTE_SIZE = 8;
    const size_t CHAR9_SIZE = 9;
};