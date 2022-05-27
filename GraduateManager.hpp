//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_GRADUATEMANAGER_HPP
#define STUDENTMANAGER_GRADUATEMANAGER_HPP

#include <list>
#include <vector>

#include "FileMapper.hpp"
#include "Graduate.hpp"

class GraduateManager {
   private:
    using GraduatePointer = std::shared_ptr<Graduate>;

    const std::string FILENAME = "graduate";
    std::list<GraduatePointer> graduates;

   public:
    GraduateManager() { loadDataFromFile(); }
    ~GraduateManager() { saveDataToFile(); }

    GraduatePointer findGraduateById(const std::string &id) {
        for (auto &graduate : graduates) {
            if (graduate->getId() == id) {
                return graduate;
            }
        }
        return nullptr;
    }

    GraduatePointer findGraduateByStudentNo(const std::string &studentNo) {
        for (auto &graduate : graduates) {
            if (graduate->getStudentNo() == studentNo) {
                return graduate;
            }
        }
        return nullptr;
    }

    std::pair<bool, std::string> addGraduate() {
        GraduatePointer graduate = std::make_shared<Graduate>();
        graduate->inputData();
        if (findGraduateById(graduate->getId()) != nullptr) {
            return {false, "Person ID has been existed"};
        }
        if (findGraduateByStudentNo(graduate->getStudentNo()) != nullptr) {
            return {false, "Student No has been existed"};
        }
        graduates.push_back(graduate);
        return {true, ""};
    }

    void deleteGraduateById(const std::string &id) {
        for (auto it = graduates.begin(); it != graduates.end(); it++) {
            if ((*it)->getId() == id) {
                graduates.erase(it);
                break;
            }
        }
    }

    void loadDataFromFile() {
        auto fileData = FileMapper::readFile(FILENAME);
        for (auto &line : *fileData) {
            GraduatePointer graduate = std::make_shared<Graduate>(
                line[0], line[1], line[2], line[3], line[4], line[5], line[6],
                line[7], line[8]);
            graduates.push_back(graduate);
        }
    }

    // name,id,gender,birthday,studentNo,schoolName,classIn,direction,adviserName
    void saveDataToFile() {
        std::list<std::vector<std::string>> lines;
        for (auto &graduate : graduates) {
            std::vector<std::string> line{
                graduate->getName(),       graduate->getId(),
                graduate->getGender(),     graduate->getBirthday(),
                graduate->getStudentNo(),  graduate->getSchoolName(),
                graduate->getClassIn(),    graduate->getDirection(),
                graduate->getAdviserName()};
            lines.push_back(line);
        }
        FileMapper::writeFile(FILENAME, lines);
    }
};

#endif  // STUDENTMANAGER_GRADUATEMANAGER_HPP
