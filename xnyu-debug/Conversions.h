#pragma once

// --- Functions ---
int splitStringVector(std::vector<std::string>& vector, std::string str, std::string del);
std::vector<std::string> splitStringVector(std::string str, std::string del);
std::wstring s2ws(const std::string& s);
bool containsDouble(const std::string& str);
std::string GetCurrentDateTime();
bool stringVectorContains(const std::vector<std::string>& vec, const std::string& value);
std::string subtringFromTo(const std::string& s, size_t startIdx, size_t endIdx);
std::string subtringBetween(const std::string& s, size_t startIdx, size_t endIdx);
bool isDigit(char c);
bool isLetter(char c);
void stringReplaceAll(std::string& source, std::string& find, std::string& replace);
std::string generateRandomID();
