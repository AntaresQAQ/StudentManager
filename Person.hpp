//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_PERSON_HPP
#define STUDENTMANAGER_PERSON_HPP

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "Date.hpp"

class Person {
   protected:
    std::string name;
    std::string id;
    std::string gender;
    std::unique_ptr<Date> birthday;

   public:
    std::string getName() { return name; }
    std::string getId() { return id; }
    std::string getGender() { return gender; }
    std::string getBirthday() { return birthday->toString(); }

    void setName(std::string n) { name = std::move(n); }
    void setGender(std::string g) { gender = std::move(g); }
    void setBirthday(unsigned int y, unsigned int m, unsigned int d) {
        birthday->setDate(y, m, d);
    }

   public:
    Person() : birthday(new Date()) {}
    Person(std::string name, std::string id, std::string gender,
           const std::string& birthday)
        : name(std::move(name))
        , id(std::move(id))
        , gender(std::move(gender))
        , birthday(new Date(birthday)) {
    }

    virtual void displayDetails(bool end) {
        std::cout << "Name: " << name << "\n"
                  << "Id: " << id << "\n"
                  << "Gender: " << gender << "\n"
                  << "Birthday: " << birthday->toString() << "\n";
        if (end) std::cout << "\n";
    };

    virtual void inputData() {
        std::cout << "Please Input Name: ";
        std::cin >> name;
        std::cout << "Please Input Id: ";
        std::cin >> id;
        std::cout << "Please Input Gender: ";
        std::cin >> gender;
        std::cout << "Please Input Birthday (year month day): ";
        unsigned int y, m, d;
        std::cin >> y >> m >> d;
        birthday->setDate(y, m, d);
    };
};

#endif  // STUDENTMANAGER_PERSON_HPP
