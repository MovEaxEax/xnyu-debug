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

std::vector<std::string> splitStringVector(std::string str, std::string del)
{
    std::vector<std::string> result;
    while (str.find(del) != std::string::npos)
    {
        int index = str.find(del);
        result.push_back(str.substr(0, index));
        str = str.substr(index + 1, str.length() - 1);
    }
    result.push_back(str);
    return result;
}

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
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

void stringReplaceAll(std::string& source, std::string find, std::string replace)
{
    int pos = 0;
    while ((pos = source.find(find, pos)) != std::string::npos)
    {
        source.replace(pos, find.length(), replace);
        pos += replace.length();
    }
}

std::string generateRandomID()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    std::uniform_int_distribution<> dis2(8, 11);
    std::stringstream ss;

    ss << std::hex;
    ss << "id";
    for (int i = 0; i < 16; i++) ss << dis2(gen);

    return ss.str();
}


