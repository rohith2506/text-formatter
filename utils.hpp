#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <numeric>

namespace formatter_utils
{

static std::vector<std::string> SplitString(const std::string& str) {
    std::vector<std::string> words;
    std::stringstream ss(str);
    std::string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

static bool IsAsciiLetterOrSpace(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch == ' ');
}

static bool IsValid(const std::string& input) {
    for (auto ch : input) {
        if (!IsAsciiLetterOrSpace(ch))
            return false;
    }
    return true;
}

} // namespace formatter_utils