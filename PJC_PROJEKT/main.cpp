#include <iostream>
#include <fstream>
#include "Functions.hpp"

auto main() -> int{
        Functions functions = Functions();
        functions.ChoosingFile();
        functions.loadFile();


    int choice;
    do {
        std::cout << "Menu: " << "\n";
        std::cout << "1. Find password : " << "\n";
        std::cout << "2. Sort password: " << "\n";
        std::cout << "3. Add password: " << "\n";
        std::cout << "4. Edit password: " << "\n";
        std::cout << "5. Delete password: " << "\n";
        std::cout << "6. Add new category: " << "\n";
        std::cout << "7. Delete category: " << "\n";
        std::cout << "8. Print latest timestamps: " << "\n";
        std::cout << "9. exit: " << "\n";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                functions.searchPassword();
                break;
            }
            case 2: {
                functions.sortPasswords();
                break;
            }
            case 3:
                functions.addPassword();
                break;
            case 4:
                functions.editPassword();
                break;
            case 5:
                functions.removePassword();
                break;
            case 6:
                functions.addCategory();
                break;
            case 7:
                functions.removeCategory();
                break;
            case 8:
                functions.printTime();
                break;
            case 9:
                std::cout << "Saving changes and closing program..." << "\n";
                break;
            default:
                std::cout << "Wrong choice, try again" << "\n";
                break;
        }
        std::cout << "\n";
    } while (choice != 9);

    return 0;
}
