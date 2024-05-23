#include <iostream>
#include <cstdlib>
#include "data_structures.h"


#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif


int main(){
    std::vector<User> headmaster;
    headmaster.push_back(User(111, "dobidobi21"));

    int User_Type;
    int User_ID;
    std::string User_Password;

    int tries = 0;
    int option = 0;
    bool isLoggedIn = false;
    bool running = true;
    std::string filename = "teacher_acc.txt";
    std::string file_name = "student_acc.txt";
    std::string name;
    std::string name_s;

    std::cout << "Hello\n";
    std::cout << "\nLogin as: \n"
                 "1. Headmaster\n"
                 "2. Teacher\n"
                 "3. Student\n";
    std::cout << "Choose your desired user type: ";
    std::cin >> User_Type;

    switch (User_Type) {
        case 1:
            while (tries < 3 && !isLoggedIn) {
                std::cout << "Enter your ID: ";
                std::cin >> User_ID;
                for (const auto &user: headmaster) {
                    if (user.ID == User_ID) {
                        std::cout << "Enter your password: ";
                        std::cin >> User_Password;
                        if (user.password == User_Password) {
                            std::cout << "\nYou successfully logged in. "
                                         "\nWelcome, Headmaster!\n\n";
                            isLoggedIn = true;
                            std::system(CLEAR);

                            while (running){
                            std::cout << "\nMenu:\n";
                            std::cout << "1. Create Account\n";
                            std::cout << "2. Delete Account\n";
                            std::cout << "3. Update Account\n";
                            std::cout << "4. View Account\n";
                            std::cout << "5. Logout\n";
                            std::cout << "Choose an option: ";
                            std::cin >> option;

                            switch (option) {

                                case 1:
                                    create_acc();
                                    break;

                                case 2:
                                    delete_acc();
                                    break;

                                case 4:
                                    view_accounts();
                                    break;

                                case 3:
                                    edit_acc();
                                    break;

                                case 5:
                                    std::cout << "Logging out...\n";
                                    running = false;
                                    break;

                                default:
                                    break;
                            }
                            }


                            break;
                        } else {
                            std::cout << "Incorrect Password\n";
                        }
                    } else {
                        std::cout << "Incorrect ID\n";
                    }
                }
                tries++;
            }
            if (tries == 3 && !isLoggedIn) {
                std::cout << "You've entered incorrect credentials 3 times. Access denied.\n";
            }
            break;


        case 2:
            while (tries < 3 && !isLoggedIn) {
                std::cout << "Enter your ID: ";
                std::cin >> User_ID;

                std::cout << "Enter your password: ";
                std::getline(std::cin >> std::ws, User_Password);

                std::pair<bool, std::string> result = verify_login(User_ID, User_Password, filename);

                if (result.first) {
                    std::cout << "\nYou successfully logged in.\n";
                    isLoggedIn = true;
                    std::system("CLEAR");
                    name = result.second;
                    std::cout << "Welcome, " << name << "!\n";
                    // add menu generation and option handling
                } else {
                    if (tries < 2) {
                        std::cout << "Incorrect ID or Password. Please try again.\n";
                    }
                }

                tries++;
            }

            if (tries == 3 && !isLoggedIn) {
                std::cout << "You've entered incorrect credentials 3 times. Access denied.\n";
            }
            break;


        case 3:
            while (tries < 3 && !isLoggedIn) {
                std::cout << "Enter your ID: ";
                std::cin >> User_ID;

                std::cout << "Enter your password: ";
                std::getline(std::cin >> std::ws, User_Password);

                std::pair<bool, std::string> result = verify_login(User_ID, User_Password, file_name);

                if (result.first) {
                    std::cout << "\nYou successfully logged in.\n";
                    isLoggedIn = true;
                    std::system("CLEAR");
                    name_s = result.second;

                    std::cout << "Welcome, " << name_s << "!\n";
                    // same here...add menu generation and option handling
                } else {
                    if (tries < 2) {
                        std::cout << "Incorrect ID or Password. Please try again.\n";
                    }
                }

                tries++;
            }

            if (tries == 3 && !isLoggedIn) {
                std::cout << "You've entered incorrect credentials 3 times. Access denied.\n";
            }
            break;
        default:
            break;
        
    }





    return 0;
}

