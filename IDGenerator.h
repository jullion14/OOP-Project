#pragma once
#include <string>
#include <vector>

std::string generateSequentialID(const std::string& prefix, int number);
int getMaxIDNumber(const std::vector<std::string>& ids, char prefix);
