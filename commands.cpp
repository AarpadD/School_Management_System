#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <sstream>
#include "data_structures.h"




void create_acc() {
    std::cout << "\n\tAccount type:\n"
              << "\t1. Student Account\n"
              << "\t2. Teacher Account\n"
              << "\tEnter your option: ";

    int option;
    std::cin >> option;


    switch(option) {
        case 1: {  // Create Student Account
            std::string name, surname, dob;
            int grade;

            std::cout << "\n\tEnter name: ";
            std::cin >> name;
            std::cout << "\tEnter surname: ";
            std::cin >> surname;
            std::cout << "\tEnter date of birth (dd/mm/yyyy): ";
            std::cin >> dob;
            std::cout << "\tEnter grade: ";
            std::cin >> grade;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1000, 9999);

            int ID = dis(gen);
            int password = dis(gen);

            std::ofstream file("student_acc.txt", std::ios::app);  // open file in append mode
            if (!file.is_open()) {
                std::cout << "\t<Error opening file>\n";
                return;
            }

            file << name << '\n'
                 << surname << '\n'
                 << dob << '\n'
                 << grade << '\n'
                 << ID << '\n'
                 << password << '\n';

            file.close();

            std::string studentFileName = "student_" + std::to_string(ID) + ".txt";
            std::ofstream studentFile(studentFileName);

            if (!studentFile.is_open()) {
                std::cout << "\t<Error creating student's file>\n";
                return;
            }

            studentFile <<  name << " " << surname << '\n'
                        <<  grade << '\n'
                        << ID << '\n';

            studentFile.close();

            std::cout << "\tStudent account created successfully. ID: " << ID << ", Password: " << password << "\n";

            break;
        }

        case 2: {
            std::string name, surname, dob, subject;

            std::cout << "\n\tEnter name: ";
            std::cin >> name;
            std::cout << "\tEnter surname: ";
            std::cin >> surname;
            std::cout << "\tEnter date of birth (dd/mm/yyyy): ";
            std::cin >> dob;
            std::cout << "\tEnter subject: ";
            std::cin >> subject;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1000, 9999);

            int ID = dis(gen);
            int password = dis(gen);

            std::ofstream file("teacher_acc.txt", std::ios::app);  // open file in append mode
            if (!file.is_open()) {
                std::cout << "\t<Error opening file>\n";
                return;
            }

            file << name << '\n'
                 << surname << '\n'
                 << dob << '\n'
                 << subject << '\n'
                 << ID << '\n'
                 << password << '\n';

            file.close();

            std::string teacherFileName = "teacher_" + subject + ".txt";
            std::ofstream teacherFile(teacherFileName);

            if (!teacherFile.is_open()) {
                std::cout << "\t<Error creating teacher's file>\n";
                return;
            }

            teacherFile << "Name: " << name << " " << surname << '\n'
                        << "Subject: " << subject << '\n'
                        << "ID: " << ID << '\n';

            teacherFile.close();

            std::cout << "\tTeacher account created successfully. ID: " << ID << ", Password: " << password << "\n";

            break;
        }
        default:
            std::cout << "\t<Invalid option chosen.>\n";
    }

}

void delete_acc() {
    std::cout << "\n\tAccount type:\n"
                 "\t1. Student Account\n"
                 "\t2. Teacher Account\n"
                 "\tEnter your option: ";

    int option;
    std::cin >> option;

    int idToBeDeleted;
    std::cout << "\n\tEnter ID of the account to be deleted: ";
    std::cin >> idToBeDeleted;

    std::string tempFile = "temp.txt";
    std::string accountFile = option == 1 ? "student_acc.txt" : "teacher_acc.txt";

    std::ifstream inputFile(accountFile);
    std::ofstream tempOutput(tempFile);

    if (!inputFile || !tempOutput) {
        std::cout << "\t<Problem opening file.>\n";
        return;
    }

    std::string line;
    while(getline(inputFile, line)) {
        std::string firstName = line;
        std::string lastName, dob, number, idString;

        if(getline(inputFile, lastName) && getline(inputFile, dob)
           && getline(inputFile, number) && getline(inputFile, idString)) {

            int id = std::stoi(idString);
            if(id != idToBeDeleted) {
                // If IDs do not match, copy account details to the temp file.
                tempOutput << firstName << '\n'
                           << lastName << '\n'
                           << dob << '\n'
                           << number << '\n'
                           << idString << '\n';

                // Copy the password line as well
                getline(inputFile, line);
                tempOutput << line << '\n';
            } else {
                // If IDs match, skip account's password line
                getline(inputFile, line);
            }
        }
    }

    inputFile.close();
    tempOutput.close();

    remove(accountFile.c_str());
    rename(tempFile.c_str(), accountFile.c_str());

    std::cout << (option == 1 ? "\tStudent" : "\tTeacher") << " account with id " << idToBeDeleted << " deleted successfully.\n";
}


void view_accounts() {
    std::cout << "\n\tAccount type:\n"
                 "\t1. Student Account\n"
                 "\t2. Teacher Account\n"
                 "\tEnter your option: ";

    int option;
    std::cin >> option;
    std::ifstream file;

    switch(option) {
        case 1:
            file.open("student_acc.txt");
            break;
        case 2:
            file.open("teacher_acc.txt");
            break;
        default:
            std::cout << "\t<Invalid option chosen.>\n";
            return;
    }

    if(!file) {
        std::cout << "\t<File cannot be opened.>\n";
        return;
    } else if(file.peek() == EOF) {
        std::cout << "\tThere are no " << (option == 1 ? "Student" : "Teacher") << " Accounts.\n";
        return;
    }

    std::cout << "\n\tDisplaying all " << (option == 1 ? "Student" : "Teacher") << " Accounts:\n";

    std::string line;
    int lineCount = 0;
    while(getline(file, line)) {
        std::cout << "\t" <<line << '\n';
        if (++lineCount % 6 == 0) {
            // If we have printed out 6 lines of information (1 account), print out a separator line
            std::cout << "\t-------------------------------------\n";
        }
    }

    file.close();
}



void display_account(const std::string& name, const std::string& surname, const std::string& dob, const std::string& extra,
                     const std::string& idString, const std::string& password, int option) {
    std::cout << "\tName: " << name << "\n";
    std::cout << "\tSurname: " << surname << "\n";
    std::cout << "\tDate of Birth: " << dob << "\n";
    std::cout << "\t" << (option == 1 ? "Grade: " : "Subject: ") << extra << "\n";
    std::cout << "\tID: " << idString << "\n";
    std::cout << "\tPassword: " << password << "\n";
}


void edit_acc() {
    std::cout << "\n\tAccount type:\n"
                 "\t1. Student Account\n"
                 "\t2. Teacher Account\n"
                 "\tEnter your option: ";

    int option;
    std::cin >> option;

    if (option != 1 && option != 2) {
        std::cout << "\t<Invalid option.>\n";
        return;
    }

    std::string accountFile = (option == 1) ? "student_acc.txt" : "teacher_acc.txt";

    std::ifstream checkFile(accountFile);
    if(checkFile.peek() == EOF) {
        std::cout << "\tThere are no " << (option == 1 ? "Student" : "Teacher") << " Accounts to edit.\n";
        return;
    }
    checkFile.close();

    int idToBeEdited;
    std::cout << "\n\tEnter ID of the account to be edited: ";
    std::cin >> idToBeEdited;

    std::string tempFile = "temp.txt";

    char anotherEdit;
    do {
        anotherEdit = 'n';  // reset the flag

        std::ifstream inputFile(accountFile);
        std::ofstream tempOutput(tempFile);

        if (!inputFile || !tempOutput) {
            std::cout << "\t<Problem opening file.>\n";
            return;
        }

        std::string line;
        bool accountFound = false;
        while (getline(inputFile, line)) {
            std::string name = line;
            getline(inputFile, line);
            std::string surname = line;
            getline(inputFile, line);
            std::string dob = line;
            getline(inputFile, line);
            std::string extra = line;
            getline(inputFile, line);
            std::string idString = line;
            getline(inputFile, line);
            std::string password = line;

            if (std::stoi(idString) == idToBeEdited) {
                accountFound = true;
                std::cout << "\n\tCurrent information for " << (option == 1 ? "Student" : "Teacher") << " account with id " << idToBeEdited << ":\n";
                display_account(name, surname, dob, extra, idString, password, option);
                break;
            }
        }
        inputFile.close();

        if(!accountFound) {
            std::cout << "\t<Account with ID " << idToBeEdited << " not found.>\n";
            return;
        }

        std::cout << "\n\tChoose what you want to edit:\n"
                  << "\t1. Name\n"
                  << "\t2. Surname\n"
                  << "\t3. Date of Birth\n"
                  << "\t4. " << ((option == 1) ? "Grade" : "Subject") << "\n"
                  << "\tEnter your option: ";

        int editOption;
        std::cin >> editOption;

        // Reopen the file and perform the account modification
        inputFile.open(accountFile);

        while (getline(inputFile, line)) {
            std::string name = line;
            getline(inputFile, line);
            std::string surname = line;
            getline(inputFile, line);
            std::string dob = line;
            getline(inputFile, line);
            std::string extra = line;
            getline(inputFile, line);
            std::string idString = line;
            getline(inputFile, line);
            std::string password = line;

            if (std::stoi(idString) == idToBeEdited) {
                switch(editOption) {
                    case 1:
                        std::cout << "\tEnter new name: ";
                        std::cin >> name;
                        break;
                    case 2:
                        std::cout << "\tEnter new surname: ";
                        std::cin >> surname;
                        break;
                    case 3:
                        std::cout << "\tEnter new date of birth (dd/mm/yyyy): ";
                        std::cin >> dob;
                        break;
                    case 4:
                        if(option == 1) {
                            std::cout << "\tEnter new grade: ";
                        } else if(option == 2) {
                            std::cout << "\tEnter new subject: ";
                        }
                        std::cin >> extra;
                        break;
                    default:
                        std::cout << "\t<Invalid edit option chosen.>\n";
                }
            }

            tempOutput << name << "\n"
                       << surname << "\n"
                       << dob << "\n"
                       << extra << "\n"
                       << idString << "\n"
                       << password << "\n";
        }

        // Close the files before renaming
        inputFile.close();
        tempOutput.close();

        remove(accountFile.c_str());
        rename(tempFile.c_str(), accountFile.c_str());

        std::cout << "\n\tDo you want to edit something else? (y/n)\n"
                     "\tEnter your option: ";
        std::cin >> anotherEdit;
    } while (tolower(anotherEdit) == 'y');
}