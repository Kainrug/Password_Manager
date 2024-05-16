#pragma once
#include <string>
#include <filesystem>

class Passwords{
private:
    std::string name;
    std::string password;
    std::string category;
    std::string service;
    std::string login;
public:
    Passwords(const std::string& name, const std::string& password, const std::string& category,
             const std::string& service, const std::string& login);

    Passwords(const std::string& line);

    Passwords();

    const std::string &getCategory() const;

    const std::string &getName() const;

    const std::string &getPassword() const;

    const std::string &getService() const;

    const std::string &getLogin() const;

    void setName(const std::string &name);

    void setPassword(const std::string &password);

    void setCategory(const std::string &category);

    void setService(const std::string &service);

    void setLogin(const std::string &login);

    auto toString() const-> std::string;

    auto toFile() const-> std::string;

    bool operator==(const Passwords& other) const {
        return name == other.name;
    }

};