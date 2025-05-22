#include "IDGenerator.h"
#include <sstream>
#include <iomanip>
#include <string>

std::string generateSequentialID(const std::string& prefix, int number) {
    int digits = std::to_string(number).length();
    std::ostringstream oss;
    oss << prefix << std::setfill('0') << std::setw(digits) << number;
    return oss.str();
}

int getMaxIDNumber(const std::vector<std::string>& ids, char prefix) {
    int maxID = 0;
    for (const auto& id : ids) {
        if (!id.empty() && id[0] == prefix) {
            try {
                int num = std::stoi(id.substr(1));
                if (num > maxID) maxID = num;
            }
            catch (...) {
                // skip malformed IDs
            }
        }
    }
    return maxID;
}
