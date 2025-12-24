#include "Helper.hpp"

#include <iomanip>

static const std::string WHITESPACE = " \n\r\t\f\v";

std::string indenter(int n) {
    if (n < 0) n = 0;
    return std::string(n, '\t');
}
std::string toString(int num) {
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

void leftTrim(std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    if (start == std::string::npos) {
        s.clear();
    } else {
        s.erase(0, start);
    }
}

void rightTrim(std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    if (end == std::string::npos) {
        s.clear();
    } else {
        s.erase(end + 1);
    }
}

void trim(std::string &s) {
    rightTrim(s);
    leftTrim(s);
}
std::basic_istream<char> &readAndTrim(std::istream &is, std::string &str) {
    auto &ret = getline(is, str);
    trim(str);
    return ret;
}

bool isInRange(int val, int min, int max) {
    return val >= min && val <= max;
}
