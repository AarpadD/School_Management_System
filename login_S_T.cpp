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

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string name, surname, dob, extra;
        int readId;
        std::string readPassword;

        ss >> name >> surname >> dob >> extra >> readId >> readPassword;

        if (id == readId && password == readPassword) {
            return std::make_pair(true, name + " " + surname);
        }
    }

    return std::make_pair(false, "");
}