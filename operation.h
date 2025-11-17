#pragma once

#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

#include "student.h"
#include "logger.h"

class Students {
public:
    //构造函数：创建文件指针，并拷贝文件数据至私有成员变量
    //此后操作都基于私有成员变量vector进行，直到程序终止运行
    Students() {
        LOG_EVENT("[Notice] Create class 'Students' successfully");
        FILE *file = fopen("student.dat", "rb");
        if (!file) {
            LOG_EVENT("[Notice] Create a new file 'student.dat'");
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
            LOG_EVENT("[Notice] " + std::to_string(size) + " students data read successfully");
        } else {
            LOG_EVENT("[Notice] Ready:Data file is empty");
        }
        fclose(file);
    }

    //检查是否为重复ID
    bool isIdExists(const char* id) {
        for (const auto& student : students_) {
            if (strcmp(student.stu_id, id) == 0) {
                return true;
            }
        }
        return false;
    }

    //成员函数：添加学生信息
    void addStudent() {
        char id[MAX_ID_LEN];
        bool valid_id = false;
        while (!valid_id) {
            std::cout << "Enter ID of the student to add: ";
            std::cin.ignore();
            std::cin.getline(id, MAX_ID_LEN);

            //合法性检查：输入不为空
            if (strlen(id) == 0) {
                std::cout << "Error: enter cannot be empty!";
                LOG_EVENT("[Warning] Input error: empty value");
                continue;
            }

            //合法性检查：输入不超过指定长度
            if (strlen(id) >= MAX_ID_LEN - 1) {
                std::cout << "Error: input is too long! the max input size of id is 20" << std::endl;
                LOG_EVENT("[Warning] Input error: input is too long");
                continue;
            }

            //合法性检查：保持Id唯一性
            bool id_exists = isIdExists(id);
            if (id_exists) {
                std::cout << "Error: id is already exists!";
                LOG_EVENT("[Warning] Input error: id is already exists");
                continue;
            }
            valid_id = true;
        }
        LOG_EVENT("[Notice] ID get successfully");
        std::cout << std::endl;

        //后面的合法性检查基本上和前面一样
        //cin.fail()用于检查输入类型是否正确
        bool valid_name = false;
        char name[MAX_NAME_LEN];
        while (!valid_name) {
            std::cout << "Enter name of the student to add: ";
            std::cin.getline(name, MAX_NAME_LEN);
            if (strlen(name) == 0) {
                std::cout << "Error: enter cannot be empty!";
                LOG_EVENT("[Warning] Input error: empty value");
                continue;
            }

            if (strlen(name) >= MAX_NAME_LEN - 1) {
                std::cout << "Error: input is too long! the max input size of name is 50" << std::endl;
                LOG_EVENT("[Warning] Input error: input is too long");
                continue;
            }
            valid_name = true;
        }
        std::cout << std::endl;
        LOG_EVENT("[Notice] Name get successfully");

        int age;
        bool valid_age = false;
        while (!valid_age) {
            std::cout << "Enter age of the student to add: ";
            std::cin >> age;

            if (std::cin.fail()) {
                std::cout << "Error: Please enter a valid number for age!" << std::endl;
                LOG_EVENT("[Warning] Input error: entered a not valid number for age");
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            if (age < 0 || age > 100) {
                std::cout << "Error: invalid age!" << std::endl;
                LOG_EVENT("[Warning] Input error: invalid age");
                continue;
            }
            valid_age = true;
        }
        std::cout << std::endl;
        LOG_EVENT("[Notice] Age get successfully");

        double score;
        bool valid_score = false;
        while (!valid_score) {
           std::cout << "Enter score of the student to add: ";
           std::cin >> score;

           if (std::cin.fail()) {
               std::cout << "Error: Please enter a valid score!" << std::endl;
               LOG_EVENT("[Warning] Input error: entered a not valid score");
               std::cin.clear();
               std::cin.ignore(10000, '\n');
               continue;
           }

           if (score < 0) {
               std::cout << "Error: invalid score!" << std::endl;
               LOG_EVENT("[Warning] Input error: invalid score");
               continue;
           }
           valid_score = true;
       }
        std::cout << std::endl;
        LOG_EVENT("[Notice] Score get successfully");

        int class_input;
        ClassType class_type;
        bool valid_class_type = false;
        while (!valid_class_type) {
            std::cout << "Enter class type of the student to add (0=Class1, 1=Class2, 2=Class3): ";
            std::cin >> class_input;

            if (std::cin.fail()) {
                std::cout << "Error: Please enter a valid class type!" << std::endl;
                LOG_EVENT("[Warning] Input error: entered a not valid class type");
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            if (class_input < 0 || class_input > 2) {
                std::cout << "Error: invalid class type!" << std::endl;
                LOG_EVENT("[Warning] Input error: invalid class type");
                continue;
            }
            valid_class_type = true;
        }
        std::cout << std::endl;
        class_type = static_cast<ClassType>(class_input);
        LOG_EVENT("[Notice] Class get successfully");

        //在此处将数据写入结构体并保存
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
        LOG_EVENT("[Notice] ID with " + std::string(id) + " student added successfully");
    }

    //搜索函数（按名字）
    void searchStudentAsName() {
        search_list_.clear();
        char name[MAX_NAME_LEN];
        std::cout << "Enter name of the student to search: ";
        std::cin.ignore();
        std::cin >> name;
        for (auto& student : students_) {
            //通过匹配方式模糊查询
            if (strstr(student.stu_name, name) != nullptr) {
                search_list_.push_back(student);
            }
        }
        LOG_EVENT("[Notice] Search Request(by name): " + std::to_string(search_list_.size()) + " result searched successfully");
        if (search_list_.empty()) {
            std::cout << "Cannot find any result!" << std::endl;
        } else {
            std::cout << search_list_.size() << " result(s) " << "have been found:" << std::endl;
            showSearchList();
        }
    }

    //搜索函数（按id）
    void searchStudentAsID() {
        search_list_.clear();
        char id[MAX_ID_LEN];
        std::cout << "Enter ID of the student to search: ";
        std::cin.ignore();
        std::cin >> id;
        for (auto& student : students_) {
            //同上，模糊查询
            if (strstr(student.stu_id, id) != nullptr) {
                search_list_.push_back(student);
            }
        }
        LOG_EVENT("[Notice] Search Request(by ID): " + std::to_string(search_list_.size()) + " result searched successfully");
        if (search_list_.empty()) {
            std::cout << "Cannot find any result!" << std::endl;
        } else {
            std::cout << search_list_.size() << " result(s) " << "have been found:" << std::endl;
            showSearchList();
        }
    }

    //排序函数（一共两个，除了排序对象外其余部分完全一致）
    void sortSearchList(const int mode) {
        std::string msg;
        switch (mode) {
        case 1:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Up_as_ID);
            msg = "Sorted by ID from high to low";
            break;
        case 2:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Down_as_ID);
            msg = "Sorted by ID from low to high";
            break;
        case 3:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Up_as_Name);
            msg = "Sorted by name from high to low";
            break;
        case 4:
            std::sort(search_list_.begin(), search_list_.end(), cmp_Down_as_Name);
            msg = "Sorted by name from low to high";
            break;
        case 0:
            std::cout << "Sort Canceled" << std::endl;
            LOG_EVENT("[Notice] Sorted canceled");
            return;
        default:
            LOG_EVENT("[Warning] User try to use a not illegal operation");
            std::cout << "Invalid option! Please try again." << std::endl;
            break;
        }
        LOG_EVENT("[Notice] " + msg);
        std::cout << "Sort Complete:" << std::endl;
        showSearchList();
    }

    void sortStudentList(const int mode) {
        std::string msg;
        switch (mode) {
        case 1:
            std::sort(students_.begin(), students_.end(), cmp_Up_as_ID);
            msg = "Sorted by ID from high to low";
            break;
        case 2:
            std::sort(students_.begin(), students_.end(), cmp_Down_as_ID);
            msg = "Sorted by ID from low to high";
            break;
        case 3:
            std::sort(students_.begin(), students_.end(), cmp_Up_as_Name);
            msg = "Sorted by name from high to low";
            break;
        case 4:
            std::sort(students_.begin(), students_.end(), cmp_Down_as_Name);
            msg = "Sorted by name from low to high";
            break;
        case 0:
            std::cout << "Sort canceled" << std::endl;
            LOG_EVENT("[Notice] Sorted canceled");
            return;
        default:
            LOG_EVENT("[Warning] User try to use a not illegal operation");
            std::cout << "Invalid option! Please try again." << std::endl;
            break;
        }
        LOG_EVENT("[Notice] " + msg);
        std::cout << "Sort Complete:" << std::endl;
        showStudents();
    }

    //两个打印函数，对应上面两个排序函数
    void showSearchList() const {
        LOG_EVENT("[Notice] Search List showed");
        std::cout << "ID          " << "Name          " << "Age    " << "Score   " << "Class"<< std::endl;
        for (auto& student : search_list_) {
            std::cout << student.stu_id << "      " << student.stu_name <<"        " << student.stu_age << "    "
                      << student.stu_score << "     " << student.stu_class << std::endl;
        }
    }

    void showStudents() const {
        LOG_EVENT("[Notice] Student List showed");
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

    //析构函数，回收相关资源并保存数据
    ~Students() {
        LOG_EVENT("[Notice] System closed and save students data");
        FILE *file = fopen("student.dat", "wb");
        if (file == nullptr) {
            LOG_EVENT("[Error] Cannot open data file");
            return;
        }
        size_t size = students_.size();
        if (size > 0) {
            fwrite(students_.data(), sizeof(Student), size, file);
            LOG_EVENT("[Notice] Students saved successfully");
        }
        fclose(file);
        LOG_EVENT("[Notice] System closed successfully");
    }
private:
    std::vector<Student> students_;
    std::vector<Student> search_list_;
};