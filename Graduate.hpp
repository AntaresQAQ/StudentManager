//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_GRADUATE_HPP
#define STUDENTMANAGER_GRADUATE_HPP

#include <string>

#include "Student.hpp"

class Graduate : virtual public Student {
   protected:
    std::string direction;
    std::string adviserName;

   public:
    std::string getDirection() { return direction; }
    std::string getAdviserName() { return adviserName; }

    void setDirection(std::string d) { direction = std::move(d); }
    void setAdviserName(std::string an) { adviserName = std::move(an); }

   public:
    Graduate() = default;
    Graduate(std::string name, std::string id, std::string gender,
             const std::string& birthday, std::string studentNo,
             std::string schoolName, std::string classIn, std::string direction,
             std::string adviserName)
        : Person(std::move(name), std::move(id), std::move(gender), birthday)
        , Student(name, id, gender, birthday, std::move(studentNo),
                  std::move(schoolName), std::move(classIn))
        , direction(std::move(direction))
        , adviserName(std::move(adviserName)) {}

    void displayDetails(bool end) override {
        Student::displayDetails(false);
        std::cout << "Direction: " << direction << "\n"
                  << "Adviser Name: " << adviserName;
        if (end) std::cout << "\n";
    }

    void inputData() override {
        Student::inputData();
        std::cout << "Please Input Direction: ";
        std::cin >> direction;
        std::cout << "Please Input Adviser Name: ";
        std::cin >> adviserName;
    }
};

#endif  // STUDENTMANAGER_GRADUATE_HPP
