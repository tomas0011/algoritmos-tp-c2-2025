#ifndef PARSE_DATE_H
#define PARSE_DATE_H

#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

time_t strToDate(const std::string& dateStr);

std::string dateToStr(time_t date);

#endif // PARSE_DATE_H
