#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "BitWriter.h"


class Encoder {
public:
    Encoder( const std::vector<std::string> &files_for_archiving,
            BitWriter &bit_writer);

    const std::unordered_map<int32_t, int32_t> &GetFrequency() const;

    void WriteArchivedFile(const std::unordered_map<int32_t, std::vector<bool>> &canonical_codes,
                           const std::vector<int32_t> &canonical_code_lengths, const std::vector<int32_t> &alphabet,
                           size_t k);

    void FindFrequency(size_t k);

private:
    BitWriter &bit_writer_;
    std::vector<std::string> files_for_archiving_;
    std::unordered_map<int32_t, int32_t> symbol_frequency_;
    const int32_t FILE_NAME_END = 256;
    const int32_t ONE_MORE_FILE = 257;
    const int32_t ARCHIVE_END = 258;
};