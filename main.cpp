#include <iostream>
#include <algorithm>

#include "student.h"
#include "operation.h"

int main() {
    FILE* file = fopen("student.bat", "w+");
    if (file == nullptr) {
        std::cout << "Failed to read data, please restart the program" << std::endl;
        return -1;
    }

    std::cout << "===== Welcome to use Student System =====" << std::endl;
    std::cout << std::endl << "Enter a number to choose next step:" << std::endl;
    std::cout << "[1]Search  [2]Add  [3]Get All  [0]Exit" << std::endl;

    int basic_choice;
    while (1) {
        std::cin >> basic_choice;
        Students students(file);

        switch (basic_choice) {
        case 0:
            std::cout << "Bye!" << std::endl;
            fclose(file);
            return 0;

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

        case 2:
            students.addStudent();

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
            students.sortSearchList(sor_choice);
        }

    }
    return 0;
}