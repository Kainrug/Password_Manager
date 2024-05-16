#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include "Functions.hpp"
#include "fmt/core.h"
#include "Passwords.hpp"


Functions::Functions() {
    filePath = "C:\\Users\\Mateusz\\CLionProjects\\PJC_PROJEKT\\cmake-build-debug\\fileMain.txt";
    passwd = "papiez123";

}

auto Functions::searchPassword() const -> void {
    auto matchingPasswords = checkingIfMatches();
    if (matchingPasswords.empty())
        fmt::print(" * No matching passwords found. :< \n");
    else {
        fmt::print(" * {} passwords match ;> : \n", matchingPasswords.size());
        for (const auto &pass: matchingPasswords) {
            fmt::print("{}\n", pass.toString());
        }
    }
}

auto Functions::sortPasswords() -> void {
    auto sortingOptions = std::vector<int>();
    while (true) {
        fmt::print("{}\n", "Choose the number of the term you want to sort by:");
        fmt::print("{}\n{}\n{}\n{}\n{}\n",
                   "1. Name",
                   "2. Category",
                   "3. Passwords",
                   "4. Service/www",
                   "5. Login");

        int choice;
        std::cin >> choice;

        if (choice < 1 || choice > 5) {
            fmt::print("{}\n", "Invalid choice. Please select a valid option.");
            continue;
        }

        sortingOptions.push_back(choice);

        fmt::print("{}\n", "Want to add another sorting parameter? (y/n)");

        std::string answer;
        std::cin >> answer;

        if (answer != "y" && answer != "Y") {
            break;
        }
    }

    std::ranges::stable_sort(passwords, [&](const Passwords& a, const Passwords& b) {
        for (auto it = sortingOptions.rbegin(); it != sortingOptions.rend(); ++it) {
            switch (*it) {
                case 1: // Sort by Name
                    if (a.getName() != b.getName()) {
                        return a.getName() < b.getName();
                    }
                    break;
                case 2: // Sort by Category
                    if (a.getCategory() != b.getCategory()) {
                        return a.getCategory() < b.getCategory();
                    }
                    break;
                case 3: // Sort by Password
                    if (a.getPassword() != b.getPassword()) {
                        return a.getPassword() < b.getPassword();
                    }
                    break;
                case 4: // Sort by Service
                    if (a.getService() != b.getService()) {
                        return a.getService() < b.getService();
                    }
                    break;
                case 5: // Sort by Login
                    if (a.getLogin() != b.getLogin()) {
                        return a.getLogin() < b.getLogin();
                    }
                    break;
            }
        }

        return false;
    });
    saveFile();

}





auto Functions::addCategory()-> void {
    fmt::print("{}\n", "Your actual categories:");
    for(auto s : category){
        fmt::print("{}\n", s);
    }
    while (true) {
        fmt::print("{}\n", "Enter the category that you want to add:");
        auto input = std::string();
        std::cin.sync();
        std::getline(std::cin, input);
        bool flag = false;
        for(auto s : category){
            if(input == s){
                flag = true;
                break;
            }
        }
        if(flag){
            fmt::print("{}\n", "This category exists, try to add a new one");
            continue;
        } else {
            category.push_back(input);
            fmt::print("{}\n", "Category has been added");
            saveFile();
            break;
        }
    }
}

auto Functions::removeCategory()-> void {
    while (true) {
        fmt::print("{}\n", "Your actual categories:");
        for(auto s : category){
            fmt::print("{}\n", s);
        }
        fmt::print("{}\n", "Enter the category name that you want to remove:");
        auto input = std::string();
        std::cin.sync();
        std::getline(std::cin, input);
        bool flag = false;
        int index = -1;
        for(int i=0;i<category.size();i++){
            if(input == category.at(i)){
                flag = true;
                index = i;
                break;
            }
        }
        if(flag){
            fmt::print("{} {} {}\n", "Category",input,"has been removed!");
            category.erase(category.begin()+index);
            saveFile();
            break;
        } else {
            category.push_back(input);
            fmt::print("{} {}\n", "There's no category",input);
        }
        if (std::ranges::find(category, input) != category.end()) {
            fmt::print("{}\n", "This category exists, try to add a new one");
            continue;
        }else{
            category.push_back(input);
            fmt::print("{}\n", "Category has been added");
            saveFile();
            break;
        }
    }
}

auto Functions::editPassword() -> void {
    fmt::print("{}\n", "Enter the application name to edit password:");
    auto input = std::string();
    std::cin.ignore();
    std::getline(std::cin, input);
    int x = -1;
    for(int i=0;i<passwords.size();i++){
        if(passwords.at(i).getName() == input){
            x = i;
        }
    }
    if(x != -1){
        auto input2 = std::string();
        std::cin.ignore();
        std::getline(std::cin, input2);

        isPasswordSecure(input2);
        passwords.at(x).setPassword(input2);
        fmt::print("{}\n", "Password updated successfully");
    }else{
        fmt::print("{}\n", "Name of application not found");
    }
    saveFile();
}


//add password do zmiany bo nie mozna wybrac kategorii
auto Functions::addPassword()-> void {
    Passwords psw = Passwords();
    fmt::print("{}\n", "Enter the application name :");
    auto input = std::string();
    std::cin.sync();
    std::getline(std::cin, input);
    psw.setName(input);
    while(true){
        fmt::print("{}\n", "Enter the category number from given:");
        fmt::print("{}\n", "Your actual categories:");
        int x = 0;
        for(auto s : category){
            fmt::print("[{}] {}\n", x, s);
            x++;
        }
        auto input2 = std::string();
        std::cin.sync();
        std::getline(std::cin, input2);
        try{
            int x = stoi(input2);
            if(x < category.size() and x >= 0) {
                psw.setCategory(category.at(x));
                break;
            }else{
                fmt::print("{}\n", "Bad data given!!");
            }
        }catch(std::exception e){
            fmt::print("{}\n", "Bad data given!!");
        }
    }
    bool chosen = false;
    auto input3 = std::string();
    while (!chosen) {
        fmt::print("{}\n", "Do you want to enter your own password (type yes) or you want to generate it? (type no):");
        std::string choice;
        std::cin >> choice;
        if (choice == "Yes" || choice == "yes") {
            fmt::print("{}\n", "Then, type your own password :");
            std::cin.sync();
            std::getline(std::cin, input3); //tutaj chyba powinien być zwykły cin, zrob to pozniej

            auto it = std::find(passwords.begin(), passwords.end(), input3);
            if (it != passwords.end()) {
                fmt::print("{}\n", "This password already exists");
            } else {
                isPasswordSecure(input3);
                psw.setPassword(input3);
                chosen = true;
            }
        } else if (choice == "No" || choice == "no") {
           auto generatedPsw = passwordGenerator();
           psw.setPassword(generatedPsw);
            chosen = true;
        }
    }

    fmt::print("{}\n", "Enter the service name/www:");
    auto input4 = std::string();
    std::cin.sync();
    std::getline(std::cin, input4);
    psw.setService(input4);
    fmt::print("{}\n", "Enter the login:");
    auto input5 = std::string();
    std::cin.sync();
    std::getline(std::cin, input5);
    psw.setService(input5);
    passwords.push_back(psw);
    saveFile();
    fmt::print("{}\n", "Given data saved!");


}





// Funkcja saveFile
auto Functions::saveFile() ->void {
    int lineNum = 0;
    std::ofstream fileStream(filePath);
    if (fileStream.is_open()) {
        fileStream << passwd << "\n";
        lineNum++;
        // Zapisz kategorie do pliku
        for (const auto& cat : category) {
            if(lineNum == 1){
                fileStream<<hh;
            }else if(lineNum == 2){
                fileStream<<mm;
            }else if(lineNum == 3){
                fileStream<<ss;
            }
            fileStream << cat << "\n";
            lineNum++;
        }
        if(lineNum == 1){
            fileStream<<hh;
        }else if(lineNum == 2){
            fileStream<<mm;
        }else if(lineNum == 3){
            fileStream<<ss;
        }
        fileStream << "!!!!!\n";
        lineNum++;
        //zapisz haslo do pliku
        for (const auto& psw : passwords) {
            if(lineNum == 1){
                fileStream<<hh;
            }else if(lineNum == 2){
                fileStream<<mm;
            }else if(lineNum == 3){
                fileStream<<ss;
            }
            fileStream << psw.toFile() << "\n";
            lineNum++;
        }
        fileStream.close();
    } else {
        fmt::print("{}\n", "Unable to open file");
    }
    fileStream.close();
}

auto Functions::loadFile() ->void {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    passwords.erase(passwords.begin(), passwords.end());
    category.erase(category.begin(), category.end());
    std::ifstream fileStream(filePath);
    auto input = std::string();
    bool flag = true;
    int lineNum = 0;
    if (fileStream.is_open()) {
        std::getline(fileStream, passwd);
        lineNum++;
        //load category to the file
        while(std::getline(fileStream, input)){
            if(lineNum == 1){
                hh = input.substr(0,2);
                input = input.substr(2,input.length()-2);
            } else if(lineNum == 2){
                mm = input.substr(0,2);
                input = input.substr(2,input.length()-2);
            }else if(lineNum == 3){
                ss = input.substr(0,2);
                input = input.substr(2,input.length()-2);
            }
            if(flag){
                if(input == "!!!!!"){
                    flag = false;
                } else {
                    category.push_back(input);
                }
            }else{
                Passwords psw = Passwords(input);
                passwords.push_back(psw);
            }
            lineNum++;
        }
        fileStream.close();
        fmt::print("{}\n", "File has been read");
    } else {
        fmt::print("{}\n", "Unable to open file");
    }
    hh = std::to_string(ltm->tm_hour);
    while(hh.length()<2){
        hh = "0"+hh;
    }
    mm = std::to_string(ltm->tm_min);
    while(mm.length()<2){
        mm = "0"+hh;
    }
    ss = std::to_string(ltm->tm_sec);
    while(ss.length()<2){
        ss = "0"+hh;
    }
    fileStream.close();
    saveFile();
}

auto Functions::passwordGenerator()-> std::string {
    std::string generatedPassword;
    std::string specialChars = "!@#$^&*";

    std::string lowercaseChars;
    for (char c = 'a'; c <= 'z'; c++) {
        lowercaseChars += c;
    }

    std::string upperCase;

    for (char c = 'A'; c <= 'Z'; c++) {
        upperCase += c;
    }
    int length;
    while (true) {
        fmt::print("{}\n", "How many characters your password should have?:");
        std::cin >> length;
        if (length != 0) {
            break;
        }
        fmt::print("{}\n", "Wrong choice, try again");
    }

    std::string availableChars;


    fmt::print("{}\n", "Do you want to use lowercase letters in your password? (type yes or no):");
    std::string choice;
    std::cin >> choice;
    if (choice == "Yes" || choice == "yes") {
        availableChars += lowercaseChars;
    }
    std::string answer;
    fmt::print("{}\n", "Do you want to use uppercase letters in your password? (type yes or no):");
    std::cin >> answer;
    if (answer == "Yes" || answer == "yes") {
        availableChars += upperCase;
    }

    std::string choice2;
    fmt::print("{}\n", "Do you want to use special characters in your password? (type yes or no):");
    std::cin >> choice2;
    if (choice2 == "Yes" || choice2 == "yes") {
        availableChars += specialChars;
    }

    std::mt19937 rng(time(nullptr)); // inicjalizuje generator liczb pseoudolosowych
    std::uniform_int_distribution<int> distribution(0, availableChars.size() - 1); //tworzy rozkład jednorodny dla liczb calkowitych z zakresu 0
    //do availableChars size -1

    for (int i = 0; i <length; ++i) {
        int randomIndex = distribution(rng);
        generatedPassword += availableChars[randomIndex];
    }
    fmt::print("{}\n{}\n", "This is your generated password: " , generatedPassword);
    return generatedPassword;
}
auto Functions::isPasswordSecure(const std::string &input3) -> void {

    // Sprawdź długość hasła
    if (input3.length() < 8) {
        fmt::print("{}\n", "Your password is too short, but it's you business");
    }

    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    // Check every letter
    for (char c : input3) {
        if (std::isupper(c)) {
            hasUppercase = true;
        } else if (std::islower(c)) {
            hasLowercase = true;
        } else if (std::isdigit(c)) {
            hasDigit = true;
        } else if (std::ispunct(c) || std::isspace(c)) {
            hasSpecialChar = true;
        }
    }


    if (!hasUppercase || !hasLowercase || !hasDigit || !hasSpecialChar) {
        fmt::print("{}\n", "Your password is not safe, but OK");

    }
    fmt::print("{}\n", "Success!!! Your password is safe");

}

/*auto Functions::listPasswords() const -> void {
    fmt::print(" * Passwords in this file:\n");
    for (const auto &pass: passwords) {
        fmt::print("\t- {}\n", pass.getPassword());
    }
}*/

auto Functions::checkingIfMatches()const-> std::vector<Passwords> {
    auto userAnswer = []() -> int {
        auto answer = std::string();
        do {
            std::cin.sync();
            std::cin >> answer;
            std::ranges::transform(answer, answer.begin(), ::toupper);
            if (answer != "NAME" && answer != "CATEGORY" && answer != "SERVICE")
                fmt::print("* Wrong choice. Try again.\n");
        } while (answer != "NAME" && answer != "CATEGORY" && answer != "SERVICE");
        if (answer == "NAME") return 1;
        else if (answer == "CATEGORY") return 2;
        else if (answer == "SERVICE") return 3;
    };

    fmt::print("* You can search by:\n"
               "\t - name\n"
               "\t - category\n"
               "\t - service\n"
               "* Choose one option and enter it.\n");
    auto answ = userAnswer();
    auto toFind = std::string();
    switch (answ) {
        case 1:
            fmt::print(" * Enter a name to find.\n");
            break;
        case 2:
            fmt::print(" * Enter a category to find.\n");
            toFind = matchingCategory();
            break;
        case 3:
            fmt::print(" * Enter a service to find.\n");
            break;
        default: {
        }
    }
    if (toFind.empty()) {
        std::cin.sync();
        std::getline(std::cin, toFind);
    }
    auto matchingPasswords = std::vector<Passwords>();
    switch (answ) {
        case 1:
            for (const auto &pass: passwords)
                if (pass.getName() == toFind) matchingPasswords.push_back(pass);
            break;
        case 2:
            for (const auto &pass: passwords)
                if (pass.getCategory() == toFind) matchingPasswords.push_back(pass);
            break;
        case 3:
            for (const auto &pass: passwords)
                if (pass.getService() == toFind) matchingPasswords.push_back(pass);
            break;
        default: {
        }
    }
    return matchingPasswords;
}

auto Functions::matchingCategory() const-> std::string {
    while (true) {
        for(auto s : category){
            fmt::print("{}\n", s);
        }
        fmt::print(" * Select one of the above categories for your new password.\n");
        std::cin.sync();
        auto input = std::string();
        std::getline(std::cin, input);
        if (std::ranges::find(category, input) == category.end()) {
            fmt::print(" * There is no such category in this file. Try it again.\n");
            continue;
        }
        return input;
    }
}



/*auto Functions::encode(std::string data) -> std::string{
    return data;

    auto str = std::string();
    int index = 0;
    for(int i=0;i<data.length();i++){
        if(data[i]!='%'){
            str += (data[i] + index);
            index++;
        } else {
            str += '%';
        }
    }
    return data;
     auto codedLine = std::string();
    for (auto i = 0; i < data.size(); i++) {
        auto codedChar = char(((data[i] ^ passwd[i % passwd.size()]) + passwd.size()));
        codedLine += codedChar;
    }
    return codedLine;

}*/

/*auto Functions::decode(std::string data) -> std::string{
    return data;

    auto str = std::string();
    int index = 0;
    for(int i=0;i<data.length();i++) {
        if (data[i] != '%') {
            str += (data[i] - index);
            index++;
        } else {
            str += '%';
        }
    }
    return data;
    auto codedLine = std::string();
    for (auto i = 0; i < line.size(); i++) {
    }
    auto codedChar = char(((line[i] ^ password[i % password.size()]) + password.size())); codedLine += codedChar;
    return codedLine;


}*/

auto Functions::removePassword() -> void {
    fmt::print("Your actual passwords:\n");
    int x = 0;
    for (auto psw : passwords){
        fmt::print("[{}] {}\n",x,psw.toString());
        x++;
    }
    fmt::print("Type number of password you want to delete:\n");
    int input = 0;
    std::cin>>input;
    fmt::print("Password has been removed:\n");
    passwords.erase(passwords.begin()+input);
    saveFile();
}

void Functions::printTime() {
    fmt::print("Last time file was open in {}:{}:{}\n",hh,mm,ss);
}

auto Functions::ChoosingFile() ->void {
    std::string password;
    fmt::print("{}\n", "Choose file that you like to open: ");
    fmt::print("{}\n", "1. file1.txt");
    fmt::print("{}\n", "2. file2.txt");
    fmt::print("{}\n", "3. file3.txt");
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1: {

            fmt::print("{}\n", "Enter the password to the file: ");
            std::cin >> password;
            if (password == "papiez123") {
                fmt::print("{}\n", "Success! Password is correct");
            } else {
                fmt::print("{}\n", "Wrong password");
                break;
            }

            break;
        }
        case 2: {

            fmt::print("{}\n", "Enter the password to the file: ");
            std::cin >> password;
            if (password == "ala123") {
                fmt::print("{}\n", "Success! Password is correct");
            } else {
                fmt::print("{}\n", "Wrong password");
                break;
            }

            break;
        }
        case 3: {

            fmt::print("{}\n", "Enter the password to the file: ");
            std::cin >> password;
            if (password == "idk123") {
                fmt::print("{}\n", "Success! Password is correct");
            } else {
                fmt::print("{}\n", "Wrong password");
                break;
            }

            break;
        }
        default:
            fmt::print("{}\n", "Invalid option. Please try again");
    }


}




