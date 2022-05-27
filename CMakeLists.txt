cmake_minimum_required(VERSION 3.22)
project(StudentManager LANGUAGES CXX)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_STANDARD 17)

set (STUDENT_MANGER_BASE_SOURCES Date.hpp FileMapper.hpp)

set (STUDENT_MANGER_UI_SOURCES Application.hpp)

set (STUDENT_MANGER_DATA_SOURCES
        Person.hpp
        Student.hpp
        Teacher.hpp
        Undergraduate.hpp
        Graduate.hpp
        TA.hpp)

set (STUDENT_MANGER_SERVICE_SOURCES
        UndergraduateManager.hpp
        GraduateManager.hpp
        TAManager.hpp
        TeacherManager.hpp)

set (STUDENT_MANGER_FULL_SOURCES
        main.cpp
        ${STUDENT_MANGER_BASE_SOURCES}
        ${STUDENT_MANGER_DATA_SOURCES}
        ${STUDENT_MANGER_SERVICE_SOURCES}
        ${STUDENT_MANGER_UI_SOURCES})

add_executable(StudentManager ${STUDENT_MANGER_FULL_SOURCES})
