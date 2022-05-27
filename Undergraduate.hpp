//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_UNDERGRADUATE_HPP
#define STUDENTMANAGER_UNDERGRADUATE_HPP

#include <iostream>
#include <utility>

#include "Student.hpp"

class Undergraduate : virtual public Student {
   protected:
    std::string major;

   public:
    std::string getMajor() { return major; }

    void setMajor(std::string m) { major = std::move(m); }

   public:
    Undergraduate() = default;
    Undergraduate(std::string name, std::string id, std::string gender,
                  const std::string& birthday, std::string studentNo,
                  std::string schoolName, std::string classIn,
                  std::string major)
        : Person(std::move(name), std::move(id), std::move(gender), birthday)
        , Student(name, id, gender, birthday, std::move(studentNo),
                  std::move(schoolName), std::move(classIn))
        , major(std::move(major)) {}

    void displayDetails(bool end) override {
        Student::displayDetails(false);
        std::cout << "Major: " << major;
        if (end) std::cout << "\n";
    }

    void inputData() override {
        Student::inputData();
        std::cout << "Please Input Major: ";
        std::cin >> major;
    }
};

#endif  // STUDENTMANAGER_UNDERGRADUATE_HPP
