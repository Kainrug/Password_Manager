#include <vector>
#include <sstream>
#include "Passwords.hpp"


Passwords::Passwords(const std::string &name, const std::string &password, const std::string &category,
                   const std::string &service, const std::string &login) {
    this->name = name;
    this->password = password;
    this->category = category;
    if(service.empty()) this->service = "Unassigned";
    else this->service = service;
    if(login.empty()) this->login = "Unassigned";
    else this->login = login;
}

Passwords::Passwords(const std::string &line) {
    auto iss = std::istringstream(line);
    auto words = std::vector<std::string>();
    auto word = std::string();
    while (std::getline(iss, word, '%'))
        words.push_back(word);
    name = words[0];
    password = words[2];
    category = words[1];
    if(words[3] == "") service = "Unassigned";
    else service = words[3];
    if(words[4] == "")  login = "Unassigned";
    else login = words[4];
}

Passwords::Passwords(){}

const std::string &Passwords::getCategory() const {
    return category;
}

const std::string &Passwords::getName() const {
    return name;
}

const std::string &Passwords::getPassword() const {
    return password;
}

const std::string &Passwords::getService() const {
    return service;
}

const std::string &Passwords::getLogin() const {
    return login;
}

void Passwords::setName(const std::string &name) {
    Passwords::name = name;
}

void Passwords::setPassword(const std::string &password) {
    Passwords::password = password;
}

void Passwords::setCategory(const std::string &category) {
    Passwords::category = category;
}

void Passwords::setService(const std::string &service) {
    Passwords::service = service;
}

void Passwords::setLogin(const std::string &login) {
    Passwords::login = login;
}

auto Passwords::toString() const -> std::string {
    return  "NAME: " + this->name + " PASSWORD : " + this->password + " CATEGORY : " + this->category + " SERVICE: " + this->service
            + " LOGIN: " + this->login;
}

auto Passwords::toFile() const -> std::string {
    return  this->name + "%" + this->category + "%" + this->password + "%" + this->service
            + "%" + this->login;
}
