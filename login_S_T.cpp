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
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (id == readId && password == readPassword) {
            return std::make_pair(true, name + " " + surname);
        }
    }

    return std::make_pair(false, "");
}



std::string get_prof_subject(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return "";
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

        return extra;

    }
    return extra;

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


    return std::make_pair(true, "");
}


void add_grade(std::string subject, std::string student_file){

    float grade;
    std::cout<<"Please enter the grade";
    std::cin>>grade;

    std::ofstream out;

    out.open(student_file, std::ios::app);

    out << subject << ":" << grade << "\n";

    std::cout<<"The student has received a " << grade << " at " << subject;
}

void see_all_grades(std::string student_file)
{
    std::ifstream file(student_file);
    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
    }

    std::string name, surname, dob, extra;
    int readId;
    std::string readPassword;

    std::cout<<"\nGrades are:\n";

    std::getline(file, name)
    && std::getline(file, surname)
    && std::getline(file, dob);
    while (std::getline(file, extra)) {

        std::cout<<extra<<"\n";

    }
}


void see_student(){

}

