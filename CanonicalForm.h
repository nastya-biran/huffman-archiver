#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>


class CanonicalForm {
public:
    CanonicalForm() = default;

    CanonicalForm(const std::vector<int32_t> &alphabet, const std::vector<int32_t> &canonical_codes_length);

    void CreateCanonicalForm(std::unordered_map<int32_t, int32_t> &symbol_length);

    void CreateCanonicalCodes();

    const std::vector<int32_t> &GetCanonicalCodeLengths() const;

    const std::vector<int32_t> &GetAlphabet() const;

    std::unordered_map<std::vector<bool>, int32_t> GetCanonicalCodesForDecoding();

    const std::unordered_map<int32_t, std::vector<bool>> &GetCanonicalCodes() const;

    const std::vector<bool> &GetArchiveEndCode() const;

    const std::vector<bool> &GetFileNameEndCode() const;

    const std::vector<bool> &GetOneMoreFileCode() const;

private:
    std::unordered_map<int32_t, std::vector<bool>> canonical_codes_;
    std::vector<int32_t> canonical_code_lengths_;
    std::vector<int32_t> alphabet_;
    const int32_t FILE_NAME_END = 256;
    const int32_t ONE_MORE_FILE = 257;
    const int32_t ARCHIVE_END = 258;
};
