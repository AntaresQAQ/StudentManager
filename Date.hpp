//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_DATE_HPP
#define STUDENTMANAGER_DATE_HPP

#include <string>

class Date {
   private:
    unsigned int year;
    unsigned int month;
    unsigned int day;

   public:
    Date() : year(1970), month(1), day(1) {}
    Date(unsigned int year, unsigned int month, unsigned int day)
        : year(year), month(month), day(day) {}
    explicit Date(const std::string& dateString) {
        size_t start = 0;
        size_t end = dateString.find('-', start);
        year = std::stoi(dateString.substr(start, end - start));
        start = end + 1;
        end = dateString.find('-', start);
        month = std::stoi(dateString.substr(start, end - start));
        start = end + 1;
        day = std::stoi(dateString.substr(start));
    }

    void setDate(unsigned int y, unsigned int m, unsigned int d) {
        this->year = y;
        this->month = m;
        this->day = d;
    }

    [[nodiscard]] std::string toString() const {
        return std::to_string(year) + "-" + std::to_string(month) + "-" +
               std::to_string(day);
    }
};

#endif  // STUDENTMANAGER_DATE_HPP
