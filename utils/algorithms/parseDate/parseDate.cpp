#include "parseDate.h"

time_t parseDate(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);

    ss >> std::get_time(&tm, "%d-%m-%Y");
    if (ss.fail()) {
        return -1; // Invalid format
    }
    return std::mktime(&tm);
}
