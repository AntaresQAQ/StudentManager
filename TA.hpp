//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_TA_HPP
#define STUDENTMANAGER_TA_HPP

#include <utility>

#include "Graduate.hpp"
#include "Teacher.hpp"

class TA : virtual public Teacher, virtual public Graduate {
   public:
    TA() = default;
    TA(std::string name, std::string id, std::string gender,
       const std::string& birthday, std::string teacherNo,
       const std::string& schoolName, std::string department,
       std::string studentNo, std::string classIn, std::string direction,
       std::string adviserName)
        : Person(std::move(name), std::move(id), std::move(gender), birthday)
        , Teacher(name, id, gender, birthday, std::move(teacherNo), schoolName,
                  std::move(department))
        , Graduate(name, id, gender, birthday, std::move(studentNo), schoolName,
                   std::move(classIn), std::move(direction),
                   std::move(adviserName)) {}

    void displayDetails(bool end) override {
        Teacher::displayDetails(false);
        std::cout << "Student No: " << studentNo << "\n"
                  << "Class: " << classIn << "\n"
                  << "Direction: " << direction << "\n"
                  << "Adviser Name: " << adviserName;
        if (end) std::cout << "\n";
    }

    void inputData() override {
        Teacher::inputData();
        std::cout << "Please Input Student No: ";
        std::cin >> studentNo;
        std::cout << "Please Input Class: ";
        std::cin >> classIn;
        std::cout << "Please Input Direction: ";
        std::cin >> direction;
        std::cout << "Please Input Adviser Name: ";
        std::cin >> adviserName;
    }
};

#endif  // STUDENTMANAGER_TA_HPP
