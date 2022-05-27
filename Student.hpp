//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_STUDENT_HPP
#define STUDENTMANAGER_STUDENT_HPP

#include <iostream>
#include <utility>

#include "Person.hpp"

class Student : virtual public Person {
   protected:
    std::string studentNo;
    std::string schoolName;
    std::string classIn;

   public:
    std::string getStudentNo() { return studentNo; }
    std::string getSchoolName() { return schoolName; }
    std::string getClassIn() { return classIn; }

    void setSchoolName(std::string sn) { schoolName = std::move(sn); }
    void setClassIn(std::string ci) { classIn = std::move(ci); }

   public:
    Student() = default;
    Student(std::string name, std::string id, std::string gender,
            const std::string& birthday, std::string studentNo,
            std::string schoolName, std::string classIn)
        : Person(std::move(name), std::move(id), std::move(gender), birthday)
        , studentNo(std::move(studentNo))
        , schoolName(std::move(schoolName))
        , classIn(std::move(classIn)) {
    }

    void displayDetails(bool end) override {
        Person::displayDetails(false);
        std::cout << "Student No: " << studentNo << "\n"
                  << "School Name: " << schoolName << "\n"
                  << "Class: " << classIn;
        if (end) std::cout << "\n";
    }

    void inputData() override {
        Person::inputData();
        std::cout << "Please Input Student No: ";
        std::cin >> studentNo;
        std::cout << "Please Input School Name: ";
        std::cin >> schoolName;
        std::cout << "Please Input Class: ";
        std::cin >> classIn;
    }
};

#endif  // STUDENTMANAGER_STUDENT_HPP
