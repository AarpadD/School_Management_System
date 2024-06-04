#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
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
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
        if (id == readId && password == readPassword) {
            return std::make_pair(true, name + " " + surname);
        }
    }

    return std::make_pair(false, "");
}



std::pair<bool, std::string> verify_login_justid(std::string id, std::string basicString) {
    std::ifstream file(id);
    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return std::make_pair(false, "");
    }

    std::string name_surname, grade_actual_year, dob;
    int readId;
    //std::string readPassword;

    while (std::getline(file, name_surname)
           && std::getline(file, grade_actual_year)
           && file >> readId)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
        if (id == std::to_string(readId)) {
            return std::make_pair(true, "");
        }
    }

    return std::make_pair(false, "");
}


void add_grade(){




}