#include "CanonicalForm.h"

CanonicalForm::CanonicalForm(const std::vector<int32_t> &alphabet, const std::vector<int32_t> &canonical_codes_length) {
    alphabet_ = alphabet;
    canonical_code_lengths_ = canonical_codes_length;
    CreateCanonicalCodes();
}

void CanonicalForm::CreateCanonicalForm(std::unordered_map<int32_t, int32_t> &symbol_length) {
    auto symbol = symbol_length.begin();
    while (symbol != symbol_length.end()) {
        alphabet_.push_back(symbol->first);
        ++symbol;
    }
    auto compare_symbols = [&symbol_length](int32_t a, int32_t b){return std::tie(symbol_length[a], a) < std::tie(symbol_length[b], b);};
    std::sort(alphabet_.begin(), alphabet_.end(), compare_symbols);
    int32_t max_code_length = 0;
    for (const auto& it : symbol_length) {
        if (it.second > max_code_length) {
            max_code_length = it.second;
        }
    }
    canonical_code_lengths_.resize(max_code_length);
    symbol = symbol_length.begin();
    while (symbol != symbol_length.end()) {
        ++canonical_code_lengths_[symbol->second - 1];
        ++symbol;
    }
    CreateCanonicalCodes();
}

void CanonicalForm::CreateCanonicalCodes() {
    std::vector<bool> canonical_code;
    std::vector<int32_t> canonical_symbol_length(alphabet_.size());
    size_t j = 0;
    for (size_t i = 0; i < canonical_code_lengths_.size(); ++i) {
        int32_t k = 0;
        while (k < canonical_code_lengths_[i]) {
            canonical_symbol_length[j] = i + 1;
            ++j;
            ++k;
        }
    }
    for (size_t i = 0; i < static_cast<size_t>(canonical_symbol_length[0]); ++i) {
        canonical_codes_[alphabet_[0]].push_back(false);
    }
    for (size_t i = 1; i < canonical_symbol_length.size(); ++i) {
        canonical_code = canonical_codes_[alphabet_[i - 1]];
        if (!canonical_code[0]) {
            canonical_code[0] = true;
        } else {
            size_t k = 1;
            canonical_code[0] = false;
            while (canonical_code[k] == 1 && k < canonical_code.size()) {
                canonical_code[k] = false;
                ++k;
            }
            if (k == canonical_code.size()) {
                canonical_code.push_back(true);
            } else {
                canonical_code[k] = true;
            }
        }
        canonical_code.insert(canonical_code.begin(), canonical_symbol_length[i] - canonical_symbol_length[i - 1],
                              false);
        canonical_codes_[alphabet_[i]] = canonical_code;
    }
    for (size_t i = 0; i < alphabet_.size(); ++i) {
        std::reverse(canonical_codes_[alphabet_[i]].begin(), canonical_codes_[alphabet_[i]].end());
    }
}


const std::unordered_map<int32_t, std::vector<bool>> &CanonicalForm::GetCanonicalCodes() const {
    return canonical_codes_;
}

 std::unordered_map<std::vector<bool>, int32_t> CanonicalForm::GetCanonicalCodesForDecoding()  {
    std::unordered_map<std::vector<bool>, int32_t> canonical_codes_for_decoding;
    for (const auto &it: canonical_codes_) {
        canonical_codes_for_decoding[it.second] = it.first;
    }
    return canonical_codes_for_decoding;
}

const std::vector<int32_t> &CanonicalForm::GetCanonicalCodeLengths() const {
    return canonical_code_lengths_;
}

const std::vector<int32_t> &CanonicalForm::GetAlphabet() const {
    return alphabet_;
}

const std::vector<bool> &CanonicalForm::GetArchiveEndCode() const {
    return canonical_codes_.at(ARCHIVE_END);
}

const std::vector<bool> &CanonicalForm::GetFileNameEndCode() const {
    return canonical_codes_.at(FILE_NAME_END);
}

const std::vector<bool> &CanonicalForm::GetOneMoreFileCode() const {
    return canonical_codes_.at(ONE_MORE_FILE);
}
