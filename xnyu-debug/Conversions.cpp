#include "pch.h"
#include "Conversions.h"



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


