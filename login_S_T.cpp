#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "data_structures.h"

std::pair<bool, std::string> verify_login(int id, const std::string& password, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return std::make_pair(false, "");
    }

    std::string name, surname, dob, extra;
    int readId;
    std::string readPassword;

    while (std::getline(file, name)
           && std::getline(file, surname)
           && std::getline(file, dob)
           && std::getline(file, extra)
           && file >> readId
           && file >> readPassword) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (id == readId && password == readPassword) {
            return std::make_pair(true, name + " " + surname);
        }
    }

    return std::make_pair(false, "");
}