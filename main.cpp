#include <iostream>
#include <algorithm>

#include "operation.h"

int main() {
    std::cout << "===== Welcome to use Student System =====" << std::endl;
    LOG_EVENT("[Notice] System started successfully");
    //Create a student class
    Students students;

    //程序入口，通过无限循环进行轮询操作，输入0可退出循环并终止程序运行
    while (true) {
        std::cout << std::endl << "Enter a number to choose next step:" << std::endl;
        std::cout << "[1]Search  [2]Add  [3]Show All  [0]Exit" << std::endl;
        int basic_choice;

        std::cin >> basic_choice;

        switch (basic_choice) {
        case 0: //退出程序
            std::cout << "Bye!" << std::endl;
            LOG_EVENT("[Notice] User choose to exit");
            return 0;

        case 1: //查找操作
            LOG_EVENT("[Notice] User choose to search");
            std::cout << "Search by: [1]name  [2]ID" << std::endl;  //查找类型询问
            int search_choice;
            std::cin >> search_choice;
            if (search_choice == 1) {
                students.searchStudentAsName();
            } else {
                students.searchStudentAsID();
            }
            //排序操作询问
            std::cout << "Do you want to sort these students as: " << std::endl;
            std::cout << "[1]From High to Low with ID" << std::endl;
            std::cout << "[2]From Low to High with ID" << std::endl;
            std::cout << "[3]From High to Low with name" << std::endl;
            std::cout << "[4]From Low to High with name" << std::endl;
            std::cout << "[0]Exit" << std::endl;
            int sort_choice;
            std::cin >> sort_choice;
            students.sortSearchList(sort_choice);
            break;

        case 2: //添加操作
            LOG_EVENT("[Notice] User choose to add data");
            students.addStudent();
            break;

        case 3: //查看所有学生信息
            LOG_EVENT("[Notice] User choose to show data");
            students.showStudents();
            //排序操作询问
            std::cout << "Do you want to sort these students as: " << std::endl;
            std::cout << "[1]From High to Low with ID" << std::endl;
            std::cout << "[2]From Low to High with ID" << std::endl;
            std::cout << "[3]From High to Low with name" << std::endl;
            std::cout << "[4]From Low to High with name" << std::endl;
            std::cout << "[0]Exit" << std::endl;
            int sor_choice;
            std::cin >> sor_choice;
            students.sortStudentList(sor_choice);
            break;

        default:
            LOG_EVENT("[Warning] User try to use a not illegal operation");
            std::cout << "Invalid option! Please try again." << std::endl;
            break;
        }

    }
}