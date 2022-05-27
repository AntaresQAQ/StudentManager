//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_TEACHER_HPP
#define STUDENTMANAGER_TEACHER_HPP

#include <iostream>
#include <utility>

#include "Person.hpp"

class Teacher : virtual public Person {
   protected:
    std::string teacherNo;
    std::string schoolName;
    std::string department;

   public:
    std::string getTeacherNo() { return teacherNo; }
    std::string getSchoolName() { return schoolName; }
    std::string getDepartment() { return department; }

    void setSchoolName(std::string sn) { schoolName = std::move(sn); }
    void setDepartment(std::string d) { department = std::move(d); }

   public:
    Teacher() = default;
    Teacher(std::string name, std::string id, std::string gender,
            const std::string& birthday, std::string teacherNo,
            std::string schoolName, std::string department)
        : Person(std::move(name), std::move(id), std::move(gender), birthday)
        , teacherNo(std::move(teacherNo))
        , schoolName(std::move(schoolName))
        , department(std::move(department)) {}

    void displayDetails(bool end) override {
        Person::displayDetails(false);
        std::cout << "Teacher No: " << teacherNo << "\n"
                  << "School Name: " << schoolName << "\n"
                  << "Department: " << department;
        if (end) std::cout << "\n";
    }

    void inputData() override {
        Person::inputData();
        std::cout << "Please Input Teacher No: ";
        std::cin >> teacherNo;
        std::cout << "Please Input School Name: ";
        std::cin >> schoolName;
        std::cout << "Please Input Department: ";
        std::cin >> department;
    }
};

#endif  // STUDENTMANAGER_TEACHER_HPP
