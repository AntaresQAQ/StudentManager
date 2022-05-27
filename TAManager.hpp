//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_TAMANAGER_HPP
#define STUDENTMANAGER_TAMANAGER_HPP

#include <list>

#include "FileMapper.hpp"
#include "TA.hpp"

class TAManager {
   private:
    using TAPointer = std::shared_ptr<TA>;
    const std::string FILENAME = "ta";
    std::list<TAPointer> tas;

   public:
    TAManager() { loadDataFromFile(); }
    ~TAManager() { saveDataToFile(); }

    TAPointer findTAById(const std::string &id) {
        for (auto &ta : tas) {
            if (ta->getId() == id) {
                return ta;
            }
        }
        return nullptr;
    }

    TAPointer findTAByStudentNo(const std::string &studentNo) {
        for (auto &ta : tas) {
            if (ta->getStudentNo() == studentNo) {
                return ta;
            }
        }
        return nullptr;
    }

    TAPointer findTAByTeacherNo(const std::string &teacherNo) {
        for (auto &ta : tas) {
            if (ta->getTeacherNo() == teacherNo) {
                return ta;
            }
        }
        return nullptr;
    }

    std::pair<bool, std::string> addTA() {
        TAPointer ta = std::make_shared<TA>();
        ta->inputData();
        if (findTAById(ta->getId()) != nullptr) {
            return {false, "Person ID has been existed"};
        }
        if (findTAByTeacherNo(ta->getTeacherNo()) != nullptr) {
            return {false, "Teacher No has been existed"};
        }
        if (findTAByStudentNo(ta->getStudentNo()) != nullptr) {
            return {false, "Student No has been existed"};
        }
        tas.push_back(ta);
        return {true, ""};
    }

    void deleteTAById(const std::string &id) {
        for (auto it = tas.begin(); it != tas.end(); it++) {
            if ((*it)->getId() == id) {
                tas.erase(it);
                break;
            }
        }
    }

    void loadDataFromFile() {
        auto fileData = FileMapper::readFile(FILENAME);
        for (auto &line : *fileData) {
            TAPointer ta = std::make_shared<TA>(
                line[0], line[1], line[2], line[3], line[4], line[5], line[6],
                line[7], line[8], line[9], line[10]);
            tas.push_back(ta);
        }
    }

    // name,id,gender,birthday,teacherNo,schoolName,department,studentNo,classIn,direction,adviserName
    void saveDataToFile() {
        std::list<std::vector<std::string>> lines;
        for (auto &ta : tas) {
            std::vector<std::string> line{
                ta->getName(),       ta->getId(),
                ta->getGender(),     ta->getBirthday(),
                ta->getTeacherNo(),  ta->Teacher::getSchoolName(),
                ta->getDepartment(), ta->getStudentNo(),
                ta->getClassIn(),    ta->getDirection(),
                ta->getAdviserName()};
            lines.push_back(line);
        }
        FileMapper::writeFile(FILENAME, lines);
    }
};

#endif  // STUDENTMANAGER_TAMANAGER_HPP
