
#include "Encoder.h"
#include <fstream>
#include <iostream>

Encoder::Encoder(const std::vector<std::string> &files_for_archiving,
                 BitWriter &bit_writer) : bit_writer_(bit_writer) {
    files_for_archiving_ = files_for_archiving;
}

void Encoder::FindFrequency(size_t k) {
    std::ifstream initial_file(files_for_archiving_[k], std::ios::binary);
    if (!initial_file.is_open()) {
        std::cerr << "can't open the file " << files_for_archiving_[k];
        exit(1);
    }
    for (size_t i = 0; i < files_for_archiving_[k].size(); ++i) {
        symbol_frequency_[static_cast<int32_t>(files_for_archiving_[k][i])] += 1;
    }
    while (!initial_file.eof()) {
        unsigned char c = initial_file.get();
        int32_t symbol = static_cast<int32_t>(c);
        if (!initial_file.eof()) {
            ++symbol_frequency_[symbol];
        }
    }
    ++symbol_frequency_[ARCHIVE_END];
    ++symbol_frequency_[ONE_MORE_FILE];
    ++symbol_frequency_[FILE_NAME_END];
    initial_file.close();
}

const std::unordered_map<int32_t, int32_t> &Encoder::GetFrequency() const {
    return symbol_frequency_;
}


void Encoder::WriteArchivedFile(const std::unordered_map<int32_t, std::vector<bool>> &canonical_codes,
                                const std::vector<int32_t> &canonical_code_lengths,
                                const std::vector<int32_t> &alphabet,
                                size_t k) {
    bit_writer_.AddBits(alphabet.size(), true);
    for (size_t i = 0; i < alphabet.size(); ++i) {
        int32_t a = alphabet[i];
        bit_writer_.AddBits(a, true);
    }
    for (size_t i = 0; i < canonical_code_lengths.size(); ++i) {
        bit_writer_.AddBits(static_cast<int32_t>(canonical_code_lengths[i]), true);
    }
    for (size_t i = 0; i < files_for_archiving_[k].size(); ++i) {
        unsigned char c = files_for_archiving_[k][i];
        bit_writer_.AddBits(canonical_codes.at(static_cast<int32_t>(c)), false);
    }
    bit_writer_.AddBits(canonical_codes.at(FILE_NAME_END), false);
    std::ifstream initial_file(files_for_archiving_[k], std::ios::binary);
    while (!initial_file.eof()) {
        unsigned char c = initial_file.get();
        int32_t symbol = static_cast<int32_t>(c);
        if (!initial_file.eof()) {
            bit_writer_.AddBits(canonical_codes.at(symbol), false);
        }
    }
    if (k + 1 == files_for_archiving_.size()) {
        bit_writer_.AddBits(canonical_codes.at(ARCHIVE_END), false);
        bit_writer_.CheckBuffer();

    } else {
        bit_writer_.AddBits(canonical_codes.at(ONE_MORE_FILE), false);
    }
    initial_file.close();
}