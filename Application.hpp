//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_APPLICATION_HPP
#define STUDENTMANAGER_APPLICATION_HPP

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "Graduate.hpp"
#include "GraduateManager.hpp"
#include "TA.hpp"
#include "TAManager.hpp"
#include "Teacher.hpp"
#include "TeacherManager.hpp"
#include "Undergraduate.hpp"
#include "UndergraduateManager.hpp"

class Application {
   private:
    std::unique_ptr<TeacherManager> teacherManager;
    std::unique_ptr<GraduateManager> graduateManager;
    std::unique_ptr<UndergraduateManager> undergraduateManager;
    std::unique_ptr<TAManager> taManager;

    static void clearScreen() {
#ifdef _WIN32
        system("cls");
#elif __linux__
        system("clear");
#elif __APPLE__
        system("clear");
#endif
    }

    static void showWelcomeMessage() {
        std::cout << "\n"
                  << "    Welcome To Student Manager System    \n"
                  << "\n";
    }

    static void showErrorMessage(const std::string& message) {
        clearScreen();
        std::cout << "\n"
                  << "-----------------------------------------\n"
                  << "                 ERROR                   \n"
                  << "-----------------------------------------\n"
                  << "  " << message << "\n"
                  << "-----------------------------------------\n"
                  << "\n";
        std::string t;
        std::getline(std::cin, t);
        std::getline(std::cin, t);
    }

    static std::string showAndGetMenuOption(
        const std::string& title, std::initializer_list<std::string> options,
        bool cls = true) {
        if (cls) clearScreen();
        std::cout << "-----------------------------------------\n"
                  << "    " << title << "\n"
                  << "-----------------------------------------\n";
        int idx = 0;
        for (auto& option : options) {
            std::cout << "    " << ++idx << ". " << option << "\n";
        }
        std::cout << "-----------------------------------------\n"
                  << "\n"
                  << "Please input your option: ";
        std::string opt;
        std::cin >> opt;
        return opt;
    }

    static bool deletingConfirm() {
        std::string confirm;
        std::cout << "You are deleting a person...\n"
                  << "Are you absolutely sure?\n"
                  << "\n"
                  << "Please input word \"delete\" to confirm: ";
        std::cin >> confirm;
        return confirm == "delete";
    }

    static void updateTeacherUI(const std::shared_ptr<Teacher>& teacher) {
        std::string option = showAndGetMenuOption(
            "Columns of Teacher",
            {"Name", "Gender", "Birthday", "School Name", "Department"});
        if (option == "1") {
            std::string name;
            std::cout << "Please Input New Name: ";
            std::cin >> name;
            teacher->setName(name);
        } else if (option == "2") {
            std::string gender;
            std::cout << "Please Input New Gender: ";
            std::cin >> gender;
            teacher->setGender(gender);
        } else if (option == "3") {
            unsigned int y, m, d;
            std::cout << "Please Input New Birthday (year month day): ";
            std::cin >> y >> m >> d;
            teacher->setBirthday(y, m, d);
        } else if (option == "4") {
            std::string schoolName;
            std::cout << "Please Input School Name: ";
            std::cin >> schoolName;
            teacher->setSchoolName(schoolName);
        } else if (option == "5") {
            std::string department;
            std::cout << "Please Input Department: ";
            std::cin >> department;
            teacher->setDepartment(department);
        } else {
            showErrorMessage("Error Option");
        }
    }

    void queryTeacherUI() {
        std::string option = showAndGetMenuOption(
            "Teacher Query Types", {"Person ID", "Teacher No", "Go Back"});
        std::shared_ptr<Teacher> teacher;
        if (option == "1") {
            clearScreen();
            std::string personId;
            std::cout << "Please Input Person ID: ";
            std::cin >> personId;
            teacher = teacherManager->findTeacherById(personId);
        } else if (option == "2") {
            clearScreen();
            std::string teacherNo;
            std::cout << "Please Input Teacher No: ";
            std::cin >> teacherNo;
            teacher = teacherManager->findTeacherByTeacherNo(teacherNo);
        } else if (option == "3") {
            return;
        } else {
            showErrorMessage("Error Option");
            return;
        }
        if (teacher == nullptr) {
            showErrorMessage("Not Found");
            return;
        }
        while (true) {
            clearScreen();
            std::cout << "-----------------------------------------\n";
            teacher->displayDetails(true);
            std::cout << "-----------------------------------------\n"
                      << "   1. Update    2.Delete    3. Go Back   \n"
                      << "-----------------------------------------\n"
                      << "Please input your option: ";
            std::cin >> option;
            if (option == "1") {
                updateTeacherUI(teacher);
            } else if (option == "2") {
                if (deletingConfirm()) {
                    teacherManager->deleteTeacherById(teacher->getId());
                    return;
                } else {
                    showErrorMessage("Deleting Canceled");
                }
            } else if (option == "3") {
                return;
            } else {
                showErrorMessage("Error Option");
                return;
            }
        }
    }

    void teacherUI() {
        while (true) {
            std::string option = showAndGetMenuOption(
                "Teacher Manager Options",
                {"Add a New teacher", "Query Teacher Details", "Go Back"});
            if (option == "1") {
                clearScreen();
                auto res = teacherManager->addTeacher();
                if (!res.first) {
                    showErrorMessage(res.second);
                }
            } else if (option == "2") {
                queryTeacherUI();
            } else if (option == "3") {
                break;
            } else {
                showErrorMessage("Error Option");
            }
        }
    }

    static void updateGraduateUI(const std::shared_ptr<Graduate>& graduate) {
        std::string option = showAndGetMenuOption(
            "Columns of Graduate", {"Name", "Gender", "Birthday", "School Name",
                                    "Class", "Direction", "Adviser Name"});
        if (option == "1") {
            std::string name;
            std::cout << "Please Input New Name: ";
            std::cin >> name;
            graduate->setName(name);
        } else if (option == "2") {
            std::string gender;
            std::cout << "Please Input New Gender: ";
            std::cin >> gender;
            graduate->setGender(gender);
        } else if (option == "3") {
            unsigned int y, m, d;
            std::cout << "Please Input New Birthday (year month day): ";
            std::cin >> y >> m >> d;
            graduate->setBirthday(y, m, d);
        } else if (option == "4") {
            std::string schoolName;
            std::cout << "Please Input New School Name: ";
            std::cin >> schoolName;
            graduate->setSchoolName(schoolName);
        } else if (option == "5") {
            std::string classIn;
            std::cout << "Please Input New Class: ";
            std::cin >> classIn;
            graduate->setClassIn(classIn);
        } else if (option == "6") {
            std::string direction;
            std::cout << "Please Input Direction: ";
            std::cin >> direction;
            graduate->setDirection(direction);
        } else if (option == "7") {
            std::string adviserName;
            std::cout << "Please Input Adviser Name: ";
            std::cin >> adviserName;
            graduate->setAdviserName(adviserName);
        } else {
            showErrorMessage("Error Option");
        }
    }

    void queryGraduateUI() {
        std::string option = showAndGetMenuOption(
            "Graduate Query Types", {"Person ID", "Student No", "Go Back"});
        std::shared_ptr<Graduate> graduate;
        if (option == "1") {
            clearScreen();
            std::string personId;
            std::cout << "Please Input Person ID: ";
            std::cin >> personId;
            graduate = graduateManager->findGraduateById(personId);
        } else if (option == "2") {
            clearScreen();
            std::string studentNo;
            std::cout << "Please Input Student No: ";
            std::cin >> studentNo;
            graduate = graduateManager->findGraduateByStudentNo(studentNo);
        } else if (option == "3") {
            return;
        } else {
            showErrorMessage("Error Option");
            return;
        }
        if (graduate == nullptr) {
            showErrorMessage("Not Found");
            return;
        }
        while (true) {
            clearScreen();
            std::cout << "-----------------------------------------\n";
            graduate->displayDetails(true);
            std::cout << "-----------------------------------------\n"
                      << "   1. Update    2.Delete    3. Go Back   \n"
                      << "-----------------------------------------\n"
                      << "Please input your option: ";
            std::cin >> option;
            if (option == "1") {
                clearScreen();
                updateGraduateUI(graduate);
            } else if (option == "2") {
                if (deletingConfirm()) {
                    graduateManager->deleteGraduateById(graduate->getId());
                    return;
                } else {
                    showErrorMessage("Deleting Canceled");
                }
            } else if (option == "3") {
                return;
            } else {
                showErrorMessage("Error Option");
                return;
            }
        }
    }

    void graduateUI() {
        while (true) {
            std::string option = showAndGetMenuOption(
                "Graduate Manager Options",
                {"Add a New Graduate", "Query Graduate Details", "Go Back"});
            if (option == "1") {
                clearScreen();
                auto res = graduateManager->addGraduate();
                if (!res.first) {
                    showErrorMessage(res.second);
                }
            } else if (option == "2") {
                queryGraduateUI();
            } else if (option == "3") {
                break;
            } else {
                showErrorMessage("Error Option");
            }
        }
    }

    static void updateUndergraduateUI(
        const std::shared_ptr<Undergraduate>& undergraduate) {
        std::string option = showAndGetMenuOption(
            "Columns of Undergraduate",
            {"Name", "Gender", "Birthday", "School Name", "Class", "Major"});
        if (option == "1") {
            std::string name;
            std::cout << "Please Input New Name: ";
            std::cin >> name;
            undergraduate->setName(name);
        } else if (option == "2") {
            std::string gender;
            std::cout << "Please Input New Gender: ";
            std::cin >> gender;
            undergraduate->setGender(gender);
        } else if (option == "3") {
            unsigned int y, m, d;
            std::cout << "Please Input New Birthday (year month day): ";
            std::cin >> y >> m >> d;
            undergraduate->setBirthday(y, m, d);
        } else if (option == "4") {
            std::string schoolName;
            std::cout << "Please Input New School Name: ";
            std::cin >> schoolName;
            undergraduate->setSchoolName(schoolName);
        } else if (option == "5") {
            std::string classIn;
            std::cout << "Please Input New Class: ";
            std::cin >> classIn;
            undergraduate->setClassIn(classIn);
        } else if (option == "6") {
            std::string major;
            std::cout << "Please Input Major: ";
            std::cin >> major;
            undergraduate->setMajor(major);
        } else {
            showErrorMessage("Error Option");
        }
    }

    void queryUndergraduateUI() {
        std::string option =
            showAndGetMenuOption("Undergraduate Query Types",
                                 {"Person ID", "Student No", "Go Back"});
        std::shared_ptr<Undergraduate> undergraduate;
        if (option == "1") {
            clearScreen();
            std::string personId;
            std::cout << "Please Input Person ID: ";
            std::cin >> personId;
            undergraduate =
                undergraduateManager->findUndergraduateById(personId);
        } else if (option == "2") {
            clearScreen();
            std::string studentNo;
            std::cout << "Please Input Student No: ";
            std::cin >> studentNo;
            undergraduate =
                undergraduateManager->findUndergraduateByStudentNo(studentNo);
        } else if (option == "3") {
            return;
        } else {
            showErrorMessage("Error Option");
            return;
        }
        if (undergraduate == nullptr) {
            showErrorMessage("Not Found");
            return;
        }
        while (true) {
            clearScreen();
            std::cout << "-----------------------------------------\n";
            undergraduate->displayDetails(true);
            std::cout << "-----------------------------------------\n"
                      << "   1. Update    2.Delete    3. Go Back   \n"
                      << "-----------------------------------------\n"
                      << "Please input your option: ";
            std::cin >> option;
            if (option == "1") {
                clearScreen();
                updateUndergraduateUI(undergraduate);
            } else if (option == "2") {
                if (deletingConfirm()) {
                    undergraduateManager->deleteUndergraduateById(
                        undergraduate->getId());
                    return;
                } else {
                    showErrorMessage("Deleting Canceled");
                }
            } else if (option == "3") {
                return;
            } else {
                showErrorMessage("Error Option");
                return;
            }
        }
    }

    void undergraduateUI() {
        while (true) {
            std::string option = showAndGetMenuOption(
                "Undergraduate Manager Options",
                {"Add a New Undergraduate", "Query Undergraduate Details",
                 "Go Back"});
            if (option == "1") {
                clearScreen();
                auto res = undergraduateManager->addUndergraduate();
                if (!res.first) {
                    showErrorMessage(res.second);
                }
            } else if (option == "2") {
                queryUndergraduateUI();
            } else if (option == "3") {
                break;
            } else {
                showErrorMessage("Error Option");
            }
        }
    }

    static void updateTAUI(const std::shared_ptr<TA>& ta) {
        std::string option = showAndGetMenuOption(
            "Columns of TA",
            {"Name", "Gender", "Birthday", "School Name", "Department", "Class",
             "Direction", "Adviser Name"});
        if (option == "1") {
            std::string name;
            std::cout << "Please Input New Name: ";
            std::cin >> name;
            ta->setName(name);
        } else if (option == "2") {
            std::string gender;
            std::cout << "Please Input New Gender: ";
            std::cin >> gender;
            ta->setGender(gender);
        } else if (option == "3") {
            unsigned int y, m, d;
            std::cout << "Please Input New Birthday (year month day): ";
            std::cin >> y >> m >> d;
            ta->setBirthday(y, m, d);
        } else if (option == "4") {
            std::string schoolName;
            std::cout << "Please Input New School Name: ";
            std::cin >> schoolName;
            ta->Student::setSchoolName(schoolName);
            ta->Teacher::setSchoolName(schoolName);
        } else if (option == "5") {
            std::string department;
            std::cout << "Please Input Department: ";
            std::cin >> department;
            ta->setDepartment(department);
        } else if (option == "6") {
            std::string classIn;
            std::cout << "Please Input New Class: ";
            std::cin >> classIn;
            ta->setClassIn(classIn);
        } else if (option == "7") {
            std::string direction;
            std::cout << "Please Input Direction: ";
            std::cin >> direction;
            ta->setDirection(direction);
        } else if (option == "8") {
            std::string adviserName;
            std::cout << "Please Input Adviser Name: ";
            std::cin >> adviserName;
            ta->setAdviserName(adviserName);
        } else {
            showErrorMessage("Error Option");
        }
    }

    void queryTAUI() {
        std::string option = showAndGetMenuOption(
            "TA Query Types",
            {"Person ID", "Student No", "Teacher No", "Go Back"});
        std::shared_ptr<TA> ta;
        if (option == "1") {
            clearScreen();
            std::string personId;
            std::cout << "Please Input Person ID: ";
            std::cin >> personId;
            ta = taManager->findTAById(personId);

        } else if (option == "2") {
            clearScreen();
            std::string studentNo;
            std::cout << "Please Input Student No: ";
            std::cin >> studentNo;
            ta = taManager->findTAByStudentNo(studentNo);
        } else if (option == "3") {
            clearScreen();
            std::string teacherNo;
            std::cout << "Please Input Teacher No: ";
            std::cin >> teacherNo;
            ta = taManager->findTAByTeacherNo(teacherNo);
        } else if (option == "4") {
            return;
        } else {
            showErrorMessage("Error Option");
            return;
        }
        if (ta == nullptr) {
            showErrorMessage("Not Found");
            return;
        }
        while (true) {
            clearScreen();
            std::cout << "-----------------------------------------\n";
            ta->displayDetails(true);
            std::cout << "-----------------------------------------\n"
                      << "   1. Update    2.Delete    3. Go Back   \n"
                      << "-----------------------------------------\n"
                      << "Please input your option: ";
            std::cin >> option;
            if (option == "1") {
                updateTAUI(ta);
            } else if (option == "2") {
                if (deletingConfirm()) {
                    taManager->deleteTAById(ta->getId());
                    return;
                } else {
                    showErrorMessage("Deleting Canceled");
                }
            } else if (option == "3") {
                return;
            } else {
                showErrorMessage("Error Option");
                return;
            }
        }
    }

    void taUI() {
        while (true) {
            std::string option = showAndGetMenuOption(
                "TA Manager Options",
                {"Add a new TA", "Query Teacher Details", "Go Back"});
            if (option == "1") {
                clearScreen();
                auto res = taManager->addTA();
                if (!res.first) {
                    showErrorMessage(res.second);
                }
            } else if (option == "2") {
                queryTAUI();
            } else if (option == "3") {
                break;
            } else {
                showErrorMessage("Error Option");
            }
        }
    }

    void mainUI() {
        clearScreen();
        showWelcomeMessage();
        bool clsFlag = false;
        while (true) {
            std::string opt = showAndGetMenuOption(
                "Main Options Menu",
                {"Teacher Manager", "Graduate Manager", "Undergraduate Manager",
                 "TA Manager", "Exit"},
                clsFlag);
            if (opt == "1") {
                teacherUI();
            } else if (opt == "2") {
                graduateUI();
            } else if (opt == "3") {
                undergraduateUI();
            } else if (opt == "4") {
                taUI();
            } else if (opt == "5") {
                break;
            } else {
                showErrorMessage("Error Option");
            }
            clsFlag = true;
        }
    }

   public:
    Application()
        : teacherManager(new TeacherManager())
        , graduateManager(new GraduateManager())
        , undergraduateManager(new UndergraduateManager())
        , taManager(new TAManager()) {}

    void start() { mainUI(); }
};

#endif  // STUDENTMANAGER_APPLICATION_HPP
