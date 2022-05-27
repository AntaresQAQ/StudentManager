//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_TEACHERMANAGER_HPP
#define STUDENTMANAGER_TEACHERMANAGER_HPP

#include <list>
#include <string>

#include "FileMapper.hpp"
#include "Teacher.hpp"

class TeacherManager {
   private:
    using TeacherPointer = std::shared_ptr<Teacher>;

    const std::string FILENAME = "teacher";
    std::list<TeacherPointer> teachers;

   public:
    TeacherManager() { loadDataFromFile(); }
    ~TeacherManager() { saveDataToFile(); }

    TeacherPointer findTeacherById(const std::string &id) {
        for (auto &teacher : teachers) {
            if (teacher->getId() == id) {
                return teacher;
            }
        }
        return nullptr;
    }

    TeacherPointer findTeacherByTeacherNo(const std::string &teacherNo) {
        for (auto &teacher : teachers) {
            if (teacher->getTeacherNo() == teacherNo) {
                return teacher;
            }
        }
        return nullptr;
    }

    std::pair<bool, std::string> addTeacher() {
        TeacherPointer teacher = std::make_shared<Teacher>();
        teacher->inputData();
        if (findTeacherById(teacher->getId()) != nullptr) {
            return {false, "Person ID has been existed"};
        }
        if (findTeacherByTeacherNo(teacher->getTeacherNo()) != nullptr) {
            return {false, "Teacher No has been existed"};
        }
        teachers.push_back(teacher);
        return {true, ""};
    }

    void deleteTeacherById(const std::string &id) {
        for (auto it = teachers.begin(); it != teachers.end(); it++) {
            if ((*it)->getId() == id) {
                teachers.erase(it);
                break;
            }
        }
    }

    void loadDataFromFile() {
        auto fileData = FileMapper::readFile(FILENAME);
        for (auto &line : *fileData) {
            TeacherPointer teacher = std::make_shared<Teacher>(
                line[0], line[1], line[2], line[3], line[4], line[5], line[6]);
            teachers.push_back(teacher);
        }
    }

    // name,id,gender,birthday,teacherNo,schoolName,department
    void saveDataToFile() {
        std::list<std::vector<std::string>> lines;
        for (auto &teacher : teachers) {
            std::vector<std::string> line{
                teacher->getName(),      teacher->getId(),
                teacher->getGender(),    teacher->getBirthday(),
                teacher->getTeacherNo(), teacher->getSchoolName(),
                teacher->getDepartment()};
            lines.push_back(line);
        }
        FileMapper::writeFile(FILENAME, lines);
    }
};

#endif  // STUDENTMANAGER_TEACHERMANAGER_HPP
