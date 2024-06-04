#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#ifndef SCHOOL_MANAGEMENT_SYSTEM_DATA_STRUCTURES_H
#define SCHOOL_MANAGEMENT_SYSTEM_DATA_STRUCTURES_H


struct User {
    int ID;
    std::string password;

    User(int ID, const std::string& password) : ID(ID), password(password) {}
};


std::pair<bool, std::string> verify_login(int id, const std::string& password, const std::string& filename);
void create_acc();
void delete_acc();
void view_accounts();
void edit_acc();
void display_account(const std::string& name, const std::string& surname, const std::string& dob, const std::string& extra,
                     const std::string& idString, const std::string& password, int option);
std::string get_prof_subject(const std::string& filename);

void add_grade(std::string subject, std::string student_file);
void see_all_grades(std::string student_file);

void see_student();

std::pair<bool, std::string>  verify_login_justid(std::string id, std::string basicString);
#endif //SCHOOL_MANAGEMENT_SYSTEM_DATA_STRUCTURES_H
