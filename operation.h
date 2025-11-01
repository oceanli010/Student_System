#pragma once

#include <cstdio>
#include <vector>

#include "student.h"

class Students {
public:
    Students(std::FILE *fp) {
        file = fp;
        int stu_num;
        std::fread(&stu_num, sizeof(int), 1, fp);
        std::fread(&students_, sizeof(Student), stu_num, fp);
    }

    void addStudent() {
        std::string id;
        std::cout << "Enter ID of the student to add: ";
        std::cin >> id;
        std::cout << std::endl;

        std::string name;
        std::cout << "Enter name of the student to add: ";
        std::cin >> name;
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
        std::cout << "Enter class of the student to add: ";
        scanf("%d", &class_type);
        std::cout << std::endl;

        Student stu;
        stu.stu_id = id;
        stu.stu_name = name;
        stu.stu_age = age;
        stu.stu_score = score;
        stu.stu_class = class_type;
        students_.push_back(stu);
        std::cout << "Student added!" << std::endl;
    }

    void searchStudentAsName() {
        search_list_.clear();
        std::string name;
        std::cout << "Enter name of the student to search: ";
        std::cin >> name;
        for (auto& student : students_) {
            if (student.stu_name.find(name) != std::string::npos) {
                search_list_.push_back(student);
            }
        }

        if (search_list_.empty()) {
            std::cout << "No Student found!" << std::endl;
        } else {
            std::cout << search_list_.size() << " result(s)" << "have been found:" << std::endl;
            showSearchList();
        }
    }

    void searchStudentAsID() {
        search_list_.clear();
        std::string id;
        std::cout << "Enter name of the student to search: ";
        std::cin >> id;
        for (auto& student : students_) {
            if (student.stu_id.find(id) != std::string::npos) {
                search_list_.push_back(student);
            }
        }

        if (search_list_.empty()) {
            std::cout << "No Student found!" << std::endl;
        } else {
            std::cout << search_list_.size() << " result(s)" << "have been found:" << std::endl;
            showSearchList();
        }
    }

    void sortSearchList(const int mode) {
        switch (mode) {
        case 1:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Up_as_ID);
        case 2:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Down_as_ID);
        case 3:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Up_as_Name);
        case 4:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Down_as_Name);
        case 0:
            std::cout << "Sort Cancled" << std::endl;
            return;
        }
        std::cout << "Sort canceled:" << std::endl;
        showSearchList();
    }

    void sortStudentList(const int mode) {
        switch (mode) {
        case 1:
            std::sort(students_.begin(), students_.end(), cmp_Up_as_ID);
        case 2:
            std::sort(students_.begin(), students_.end(), cmp_Down_as_ID);
        case 3:
            std::sort(students_.begin(), students_.end(), cmp_Up_as_Name);
        case 4:
            std::sort(students_.begin(), students_.end(), cmp_Up_as_Name);
        case 0:
            std::cout << "Sort canceled" << std::endl;
            return;
        }
        std::cout << "Sort Complete:" << std::endl;
        showStudents();
    }

    void showSearchList() {
        std::cout << "ID          " << "Name          " << "Age    " << "Score   " << "Class"<< std::endl;
        for (auto& student : search_list_) {
            std::cout << student.stu_id << "          " << student.stu_name <<"          " << student.stu_age << "    "
                      << student.stu_score << "   " << student.stu_class << std::endl;
        }
    }

    void showStudents() {
        std::cout << "ID          " << "Name          " << "Age    " << "Score   " << "Class"<< std::endl;
        for (auto& student : students_) {
            std::cout << student.stu_id << "          " << student.stu_name <<"          " << student.stu_age << "    "
                      << student.stu_score << "   " << student.stu_class << std::endl;
        }
    }

    ~Students() {
        std::rewind(file);
        int stu_size = students_.size();
        std::fwrite(&stu_size, sizeof(int), 1, file);
        std::fwrite(&students_, sizeof(Student), stu_size, file);
        std::fclose(file);
    }
private:
    std::vector<Student> students_;
    std::vector<Student> search_list_;
    FILE *file;
};