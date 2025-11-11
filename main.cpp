#include <iostream>
#include <algorithm>

#include "student.h"
#include "operation.h"

int main() {
    std::cout << "===== Welcome to use Student System =====" << std::endl;
    Students students;

    while (true) {
        std::cout << std::endl << "Enter a number to choose next step:" << std::endl;
        std::cout << "[1]Search  [2]Add  [3]Show All  [0]Exit" << std::endl;
        int basic_choice;

        std::cin >> basic_choice;

        switch (basic_choice) {
        case 0:
            std::cout << "Bye!" << std::endl;
            return 0;
            break;

        case 1:
            std::cout << "Search by: [1]name  [2]ID" << std::endl;
            int search_choice;
            std::cin >> search_choice;
            if (search_choice == 1) {
                students.searchStudentAsName();
            } else {
                students.searchStudentAsID();
            }
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

        case 2:
            students.addStudent();
            break;

        case 3:
            students.showStudents();
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
        }
    }
}