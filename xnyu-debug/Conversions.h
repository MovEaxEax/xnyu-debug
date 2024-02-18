#pragma once

// --- Functions ---
int splitStringVector(std::vector<std::string>& vector, std::string str, std::string del);
bool containsDouble(const std::string& str);
std::string GetCurrentDateTime();
bool stringVectorContains(const std::vector<std::string>& vec, const std::string& value);
bool variableVectorContainsName(const std::vector<Variable>* vec, const std::string& name);
std::string subtringFromTo(const std::string& s, size_t startIdx, size_t endIdx);
std::string subtringBetween(const std::string& s, size_t startIdx, size_t endIdx);
bool isDigit(char c);
bool isLetter(char c);


