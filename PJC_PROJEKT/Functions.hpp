#pragma once
#include "Passwords.hpp"
#include <filesystem>

class Functions{
    std::filesystem::path filePath;
    std::string passwd;
    std::vector<std::string> category;//load this
    std::vector<Passwords> passwords;
    std::string hh, mm, ss;

public:
    Functions();
    /**
     * @brief Asking to choose a file and to enter the password
     * This function is asking to choose a file and then to enter the password to open it
     */
    auto ChoosingFile() ->void;

    /**
     * @brief Adding the password to the vector of the passwords
     * This function is adding a new password, checking if it is safe and if we want to generate a new password
     */
    auto addPassword()->void;

    /**
        * @brief Adding a new Category to the vector of categories
        * This function is adding a new category to the vector of categories
        */
    auto addCategory()->void;

    /**
        * @brief Removes a category that we choose
        * This function is removing a category from our input
        */
    auto removeCategory()->void;

    /**
        * @brief Saves category, password and timestamp
        * This function is saving category, password and timestamp to the file
        */
    auto saveFile()->void;

    /**
        * @brief Loads category, password and timestamp
        * This function is loading category, password and timestamp from the file
        */
    auto loadFile()->void;

    /**
        * @brief Generates a new password
        * This function is generating a new password, it is used in Function addPassword
        * @return A string that is our generated password
        */
    auto passwordGenerator()->std::string;

    /**
        *@param  input of user
        * @brief Checks if password is safe
        * This function is checking password: length, if contains upper or lower cases and special signs
        */
    auto isPasswordSecure(const std::string& input3)-> void;

    /**
        * @brief Sorts alphabetically by selected parameters
        * This function is sorting chosen parameters alphabetically
        */
    auto sortPasswords()->void;
    /**
        * @brief Checks if it matches the given parameters
        * This function is checking if given parameters are matching
        * @return a matching vector of passwords
        */
    auto checkingIfMatches()const -> std::vector<Passwords>;

    /**
        * @brief Checking if given category exists
        * This function is checking if given category exists in vector of categories
        * @return a user input
        */
    auto matchingCategory() const -> std::string;

    /**
        * @brief Editing password
        * This function is editing existing password in the file
        */
    auto editPassword() -> void;

    /**
        * @brief Removing password from the file
        * This function is removing given password from the file
        */
    auto removePassword() -> void;

    /**
        * @brief Finding a given password
        * This function is searching for the file and then printing it
        */
    auto searchPassword() const -> void;

    /**
        * @brief Printing a actual timestamps
        * This function is printing an actual timestamps
        */
    auto printTime() -> void;

};