#include "BitWriter.h"
#include "Decoder.h"


Decoder::Decoder(const BitReader &bit_reader) : bit_reader_(bit_reader) {
    size_t alphabet_size = BoolToInt(bit_reader_.ReadNBits(CHAR9_SIZE));
    for (size_t i = 0; i < alphabet_size; ++i) {
        alphabet_.push_back(BoolToInt(bit_reader_.ReadNBits(CHAR9_SIZE)));
    }
    size_t symbols_count = 0;
    while (symbols_count < alphabet_.size()) {
        int32_t code_length_count = BoolToInt(bit_reader_.ReadNBits(CHAR9_SIZE));
        canonical_codes_lengths_.push_back(code_length_count);
        symbols_count += code_length_count;
    }
}

bool Decoder::WriteInitialFile(const std::unordered_map<std::vector<bool>, int32_t> &canonical_codes_for_decoding,
                               const std::vector<bool> &file_name_end, const std::vector<bool> &one_more_file,
                               const std::vector<bool> &archive_end) {
    std::vector<bool> bits;
    std::string file_name_string;
    while (bits != file_name_end) {
        std::vector<bool> byte = bit_reader_.ReadNBits(1);
        bits.insert(bits.end(), byte.begin(), byte.end());
        if (bits != file_name_end) {
            if (canonical_codes_for_decoding.count(bits)) {
                unsigned char c = static_cast<unsigned char>(canonical_codes_for_decoding.at(bits));
                file_name_string += c;
                bits.clear();
            }
        }
    }
    bits.clear();
    std::ofstream initial_file;
    initial_file.open(file_name_string, std::ios::binary);
    while (bits != one_more_file && bits != archive_end) {
        std::vector<bool> bit = bit_reader_.ReadNBits(1);
        bits.insert(bits.end(), bit.begin(), bit.end());
        if (bits != one_more_file && bits != archive_end) {
            if (canonical_codes_for_decoding.count(bits) > 0) {
                unsigned char c = static_cast<unsigned char>(canonical_codes_for_decoding.at(bits));
                initial_file << c;
                bits.clear();
            }
        }
    }
    initial_file.close();
    return bits != archive_end;
}

int32_t Decoder::BoolToInt(const std::vector<bool> &bites) {
    int32_t c = bites[BYTE_SIZE];
    for (size_t i = BYTE_SIZE; i > 0; --i) {
        c = (c << 1);
        c = c + bites[i - 1];
    }
    return c;
}

std::vector<bool> Decoder::GetBuffer() {
    return bit_reader_.GetBuffer();
}

const std::vector<int32_t> &Decoder::GetAlphabet() const {
    return alphabet_;
}

const std::vector<int32_t> &Decoder::GetCanonicalCodesLengths() const {
    return canonical_codes_lengths_;
}
