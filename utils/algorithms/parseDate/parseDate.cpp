#include "parseDate.h"

time_t strToDate(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);

    ss >> std::get_time(&tm, "%d-%m-%Y");
    if (ss.fail()) {
        return -1; // Invalid format
    }
    return std::mktime(&tm);
}

std::string dateToStr(time_t date) {
    std::tm* tm = std::localtime(&date);
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", tm);
    return std::string(buffer);
}
