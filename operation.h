#pragma once

#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

#include "student.h"

class Students {
public:
    Students() {
        FILE *file = fopen("student.dat", "rb");
        if (!file) {
            file = fopen("student.dat", "wb");
            if (!file) {
                fclose(file);
            }
            return;
        }
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        if (file_size > 0) {
            size_t size = file_size / sizeof(Student);
            students_.resize(size);
            fread(students_.data(), sizeof(Student), size, file);
        }
        fclose(file);
    }

    void addStudent() {
        char id[MAX_ID_LEN];
        std::cout << "Enter ID of the student to add: ";
        std::cin.ignore();
        std::cin.getline(id, MAX_ID_LEN);
        std::cout << std::endl;

        char name[MAX_NAME_LEN];
        std::cout << "Enter name of the student to add: ";
        std::cin.getline(name, MAX_NAME_LEN);
        std::cout << std::endl;

        int age;
        std::cout << "Enter age of the student to add: ";
        std::cin >> age;
        std::cout << std::endl;

        double score;
        std::cout << "Enter score of the student to add: ";
        std::cin >> score;
        std::cout << std::endl;

        ClassType class_type;
        std::cout << "Enter class of the student to add(0=Class1, 1=Class2, 2=Class3): ";
        int class_id;
        std::cin >> class_id;
        class_type = static_cast<ClassType>(class_id);
        std::cout << std::endl;

        Student stu;
        strncpy(stu.stu_id, id, MAX_ID_LEN - 1);
        stu.stu_id[MAX_ID_LEN - 1] = '\0';
        strncpy(stu.stu_name, name, MAX_NAME_LEN - 1);
        stu.stu_name[MAX_NAME_LEN - 1] = '\0';
        stu.stu_age = age;
        stu.stu_score = score;
        stu.stu_class = class_type;
        students_.push_back(stu);
        std::cout << "Student added!" << std::endl;
    }

    void searchStudentAsName() {
        search_list_.clear();
        char name[MAX_NAME_LEN];
        std::cout << "Enter name of the student to search: ";
        std::cin.ignore();
        std::cin >> name;
        for (auto& student : students_) {
            if (strstr(student.stu_name, name) != nullptr) {
                search_list_.push_back(student);
            }
        }

        if (search_list_.empty()) {
            std::cout << "Cannot find any result!" << std::endl;
        } else {
            std::cout << search_list_.size() << " result(s) " << "have been found:" << std::endl;
            showSearchList();
        }
    }

    void searchStudentAsID() {
        search_list_.clear();
        char id[MAX_ID_LEN];
        std::cout << "Enter ID of the student to search: ";
        std::cin.ignore();
        std::cin >> id;
        for (auto& student : students_) {
            if (strstr(student.stu_id, id) != nullptr) {
                search_list_.push_back(student);
            }
        }

        if (search_list_.empty()) {
            std::cout << "Cannot find any result!" << std::endl;
        } else {
            std::cout << search_list_.size() << " result(s) " << "have been found:" << std::endl;
            showSearchList();
        }
    }

    void sortSearchList(const int mode) {
        switch (mode) {
        case 1:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Up_as_ID);
            break;
        case 2:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Down_as_ID);
            break;
        case 3:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Up_as_Name);
            break;
        case 4:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Down_as_Name);
            break;
        case 0:
            std::cout << "Sort Canceled" << std::endl;
            return;
        }
        //std::cout << "Sort canceled:" << std::endl;
        showSearchList();
    }

    void sortStudentList(const int mode) {
        switch (mode) {
        case 1:
            std::sort(students_.begin(), students_.end(), cmp_Up_as_ID);
            break;
        case 2:
            std::sort(students_.begin(), students_.end(), cmp_Down_as_ID);
            break;
        case 3:
            std::sort(students_.begin(), students_.end(), cmp_Up_as_Name);
            break;
        case 4:
            std::sort(students_.begin(), students_.end(), cmp_Down_as_Name);
            break;
        case 0:
            std::cout << "Sort canceled" << std::endl;
            return;
        }
        std::cout << "Sort Complete:" << std::endl;
        showStudents();
    }

    void showSearchList() const {
        std::cout << "ID          " << "Name          " << "Age    " << "Score   " << "Class"<< std::endl;
        for (auto& student : search_list_) {
            std::cout << student.stu_id << "      " << student.stu_name <<"        " << student.stu_age << "    "
                      << student.stu_score << "     " << student.stu_class << std::endl;
        }
    }

    void showStudents() const {
        if (students_.empty()) {
            std::cout << "No Student found!" << std::endl;
            return;
        } else {
            std::cout << "ID          " << "Name          " << "Age    " << "Score   " << "Class"<< std::endl;
            for (auto& student : students_) {
                std::cout << student.stu_id << "      " << student.stu_name <<"        " << student.stu_age << "    "
                          << student.stu_score << "     " << student.stu_class << std::endl;
            }
        }
    }

    ~Students() {
        FILE *file = fopen("student.dat", "wb");
        if (file == nullptr) {
            return;
        }
        size_t size = students_.size();
        if (size > 0) {
            fwrite(students_.data(), sizeof(Student), size, file);
        }
        fclose(file);
    }
private:
    std::vector<Student> students_;
    std::vector<Student> search_list_;
};