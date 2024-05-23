#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <sstream>
#include "data_structures.h"




void create_acc() {
    std::cout << "Choose account type:\n"
              << "1. Student Account\n"
              << "2. Teacher Account\n";

    int option;
    std::cin >> option;

    switch(option) {
        case 1: {  // Create Student Account
            std::string name, surname, dob;
            int grade;

            std::cout << "\nEnter name: ";
            std::cin >> name;
            std::cout << "Enter surname: ";
            std::cin >> surname;
            std::cout << "Enter date of birth (dd/mm/yyyy): ";
            std::cin >> dob;
            std::cout << "Enter grade: ";
            std::cin >> grade;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1000, 9999);

            int ID = dis(gen);
            int password = dis(gen);

            std::ofstream file("student_acc.txt", std::ios::app);  // open file in append mode
            if (!file.is_open()) {
                std::cout << "Error opening file\n";
                return;
            }

            file << name << '\n'
                 << surname << '\n'
                 << dob << '\n'
                 << grade << '\n'
                 << ID << '\n'
                 << password << '\n';

            std::cout << "Student account created successfully. ID: " << ID << ", Password: " << password << "\n";

            break;
        }

        case 2: {
            std::string name, surname, dob, subject;

            std::cout << "\nEnter name: ";
            std::cin >> name;
            std::cout << "Enter surname: ";
            std::cin >> surname;
            std::cout << "Enter date of birth (dd/mm/yyyy): ";
            std::cin >> dob;
            std::cout << "Enter subject: ";
            std::cin >> subject;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1000, 9999);

            int ID = dis(gen);
            int password = dis(gen);

            std::ofstream file("teacher_acc.txt", std::ios::app);  // open file in append mode
            if (!file.is_open()) {
                std::cout << "Error opening file\n";
                return;
            }

            file << name << '\n'
                 << surname << '\n'
                 << dob << '\n'
                 << subject << '\n'
                 << ID << '\n'
                 << password << '\n';

            std::cout << "Teacher account created successfully. ID: " << ID << ", Password: " << password << "\n";

            break;
        }
        default:
            std::cout << "Invalid option chosen.\n";
    }

}

void delete_acc() {
    std::cout << "Choose account type:\n"
              << "1. Student Account\n"
              << "2. Teacher Account\n";

    int option;
    std::cin >> option;

    int idToBeDeleted;
    std::cout << "Enter ID of the account to be deleted: ";
    std::cin >> idToBeDeleted;

    std::string tempFile = "temp.txt";
    std::string accountFile = option == 1 ? "student_acc.txt" : "teacher_acc.txt";

    std::ifstream inputFile(accountFile);
    std::ofstream tempOutput(tempFile);

    if (!inputFile || !tempOutput) {
        std::cout << "Problem opening file.\n";
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

    std::cout << (option == 1 ? "Student" : "Teacher") << " account with id " << idToBeDeleted << " deleted successfully.\n";
}


void view_accounts() {
    std::cout << "Choose account type to view:\n"
              << "1. Student Accounts\n"
              << "2. Teacher Accounts\n";

    int option;
    std::cin >> option;

    if(option == 1) { // View All Student Accounts
        std::ifstream file("student_acc.txt");
        if(!file) {
            std::cout << "File cannot be opened\n";
            return;
        }

        std::cout << "Displaying all Student Accounts:\n";
        std::string line;
        while(getline(file, line)) {
            std::cout << line << '\n';
        }
    }
    else if(option == 2) { // View All Teacher Accounts
        std::ifstream file("teacher_acc.txt");
        if(!file) {
            std::cout << "File cannot be opened\n";
            return;
        }

        std::cout << "Displaying all Teacher Accounts:\n";
        std::string line;
        while(getline(file, line)) {
            std::cout << line << '\n';
        }
    }
    else {
        std::cout << "Invalid option chosen.\n";
    }
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
    std::cout << "Choose account type to edit:\n"
              << "1. Student Account\n"
              << "2. Teacher Account\n";

    int option;
    std::cin >> option;

    if (option != 1 && option != 2) {
        std::cout << "Invalid option.\n";
        return;
    }

    int idToBeEdited;
    std::cout << "Enter ID of the account to be edited: ";
    std::cin >> idToBeEdited;

    std::string tempFile = "temp.txt";
    std::string accountFile = (option == 1) ? "student_acc.txt" : "teacher_acc.txt";

    char anotherEdit;
    do {
        anotherEdit = 'n';  // reset the flag

        std::ifstream inputFile(accountFile);
        std::ofstream tempOutput(tempFile);

        if (!inputFile || !tempOutput) {
            std::cout << "Problem opening file.\n";
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
                std::cout << "Current information for " << (option == 1 ? "Student" : "Teacher") << " account with id " << idToBeEdited << ":\n";
                display_account(name, surname, dob, extra, idString, password, option);
                break;
            }
        }
        inputFile.close();

        if(!accountFound) {
            std::cout << "Account with ID " << idToBeEdited << " not found.\n";
            return;
        }

        std::cout << "Choose what you want to edit:\n"
                  << "1. Name\n"
                  << "2. Surname\n"
                  << "3. Date of Birth\n"
                  << "4. " << ((option == 1) ? "Grade" : "Subject") << "\n";

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
                        std::cout << "Enter new name: ";
                        std::cin >> name;
                        break;
                    case 2:
                        std::cout << "Enter new surname: ";
                        std::cin >> surname;
                        break;
                    case 3:
                        std::cout << "Enter new date of birth (dd/mm/yyyy): ";
                        std::cin >> dob;
                        break;
                    case 4:
                        if(option == 1) {
                            std::cout << "Enter new grade: ";
                        } else if(option == 2) {
                            std::cout << "Enter new subject: ";
                        }
                        std::cin >> extra;
                        break;
                    default:
                        std::cout << "Invalid edit option chosen.\n";
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

        std::cout << "Do you want to edit something else? (y/n)\n";
        std::cin >> anotherEdit;
    } while (tolower(anotherEdit) == 'y');
}