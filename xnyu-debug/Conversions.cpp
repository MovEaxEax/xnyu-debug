#include "pch.h"
#include "Conversions.h"
#include "Variable.h"



// --- Functions ---
int splitStringVector(std::vector<std::string>& vector, std::string str, std::string del)
{
    while (str.find(del) != std::string::npos)
    {
        int index = str.find(del);
        vector.push_back(str.substr(0, index));
        str = str.substr(index + 1, str.length() - 1);
    }

    vector.push_back(str);

    return 1;
}

bool containsDouble(const std::string& str)
{
    std::regex double_regex(R"([-+]?[0-9]*\.?[0-9]+)");
    return std::regex_match(str, double_regex);
}

std::string GetCurrentDateTime() {
    std::stringstream ss;
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H-%M-%S");
    return ss.str();
}

bool stringVectorContains(const std::vector<std::string>& vec, const std::string& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

bool variableVectorContainsName(const std::vector<Variable>* vec, const std::string& name) {
    if (name.find("_arg") != std::string::npos || name.find("_ret") != std::string::npos || name.find("repeatertmpvarindicies") != std::string::npos) return true;
    for (int i = 0; i < vec->size(); i++) if (vec->data()[i].name == name) return true;
    return false;
}

std::string subtringFromTo(const std::string& s, size_t startIdx, size_t endIdx) {
    if (endIdx <= startIdx || startIdx >= s.size() || endIdx > s.size()) {
        throw std::out_of_range("Invalid indices provided.");
    }
    return s.substr(startIdx, (endIdx - startIdx) - 1);
}

std::string subtringBetween(const std::string& s, size_t startIdx, size_t endIdx) {
    if (endIdx <= startIdx || startIdx >= s.size() || endIdx > s.size()) {
        throw std::out_of_range("Invalid indices provided.");
    }
    return s.substr(startIdx + 1, (endIdx - startIdx) - 1);
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}


