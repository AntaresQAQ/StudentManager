//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_UNDERGRADUATEMANAGER_HPP
#define STUDENTMANAGER_UNDERGRADUATEMANAGER_HPP

#include <list>

#include "FileMapper.hpp"
#include "Undergraduate.hpp"

class UndergraduateManager {
    using UndergraduatePointer = std::shared_ptr<Undergraduate>;

   private:
    const std::string FILENAME = "undergraduate";
    std::list<UndergraduatePointer> undergraduates;

   public:
    UndergraduateManager() { loadDataFromFile(); }
    ~UndergraduateManager() { saveDataToFile(); }

    UndergraduatePointer findUndergraduateById(const std::string &id) {
        for (auto &undergraduate : undergraduates) {
            if (undergraduate->getId() == id) {
                return undergraduate;
            }
        }
        return nullptr;
    }

    UndergraduatePointer findUndergraduateByStudentNo(
        const std::string &studentNo) {
        for (auto &undergraduate : undergraduates) {
            if (undergraduate->getStudentNo() == studentNo) {
                return undergraduate;
            }
        }
        return nullptr;
    }

    std::pair<bool, std::string> addUndergraduate() {
        UndergraduatePointer undergraduate = std::make_shared<Undergraduate>();
        undergraduate->inputData();
        if (findUndergraduateById(undergraduate->getId()) != nullptr) {
            return {false, "Person ID has been existed"};
        }
        if (findUndergraduateByStudentNo(undergraduate->getStudentNo()) !=
            nullptr) {
            return {false, "Student No has been existed"};
        }
        undergraduates.push_back(undergraduate);
        return {true, ""};
    }

    void deleteUndergraduateById(const std::string &id) {
        for (auto it = undergraduates.begin(); it != undergraduates.end();
             it++) {
            if ((*it)->getId() == id) {
                undergraduates.erase(it);
                break;
            }
        }
    }

    void loadDataFromFile() {
        auto fileData = FileMapper::readFile(FILENAME);
        for (auto &line : *fileData) {
            UndergraduatePointer undergraduate =
                std::make_shared<Undergraduate>(line[0], line[1], line[2],
                                                line[3], line[4], line[5],
                                                line[6], line[7]);
            undergraduates.push_back(undergraduate);
        }
    }

    // name,id,gender,birthday,studentNo,schoolName,classIn,major
    void saveDataToFile() {
        std::list<std::vector<std::string>> lines;
        for (auto &undergraduate : undergraduates) {
            std::vector<std::string> line{
                undergraduate->getName(),      undergraduate->getId(),
                undergraduate->getGender(),    undergraduate->getBirthday(),
                undergraduate->getStudentNo(), undergraduate->getSchoolName(),
                undergraduate->getClassIn(),   undergraduate->getMajor()};
            lines.push_back(line);
        }
        FileMapper::writeFile(FILENAME, lines);
    }
};

#endif  // STUDENTMANAGER_UNDERGRADUATEMANAGER_HPP
