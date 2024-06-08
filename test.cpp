#include <iostream>
#include <cstdlib>
#include "data_structures.h"
#include <string.h>


#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// add grade for students from profesor account
//std::pair<bool, std::string> verify_login_justid(int id, std::string basicString);
//from profesor account, sa poti sa vezi elevii pe care ii are


int main(){
    std::vector<User> headmaster;
    headmaster.push_back(User(111, "dobi"));

    int User_Type;
    int User_ID;
    char ID;
    std::string User_Password;

    int tries = 0;
    int option = 0;
    bool isLoggedIn = false;
    bool running = true;
    std::string filename = "teacher_acc.txt";
    std::string file_name = "student_acc.txt";
    std::string name;
    std::string name_s;

    std::cout << "\t~Hello~\n";
    std::cout << "\tLogin as: \n"
                 "\t1. Headmaster\n"
                 "\t2. Teacher\n"
                 "\t3. Student\n";
    std::cout << "\tChoose your desired user type: ";
    std::cin >> User_Type;

    switch (User_Type) {
        case 1:
            while (tries < 3 && !isLoggedIn) {
                std::cout << "\tEnter your ID: ";
                std::cin >> User_ID;
                for (const auto &user: headmaster) {
                    if (user.ID == User_ID) {
                        std::cout << "\tEnter your password: ";
                        std::cin >> User_Password;
                        if (user.password == User_Password) {
                            std::cout << "\n\t<You successfully logged in.> "
                                         "\n\tWelcome, Headmaster!\n";
                            isLoggedIn = true;
                            std::system(CLEAR);

                            while (running){
                            std::cout << "\n\tMenu:\n";
                            std::cout << "\t1. Create Account\n";
                            std::cout << "\t2. Delete Account\n";
                            std::cout << "\t3. Edit Account\n";
                            std::cout << "\t4. View Account\n";
                            std::cout << "\t5. Logout\n";
                            std::cout << "\tChoose an option: ";
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
                                    std::cout << "\tLogging out...\n";
                                    running = false;
                                    break;

                                default:
                                    break;
                            }
                            }


                            break;
                        } else {
                            std::cout << "\t<Incorrect Password>\n";
                        }
                    } else {
                        std::cout << "\t<Incorrect ID>\n";
                    }
                }
                tries++;
            }
            if (tries == 3 && !isLoggedIn) {
                std::cout << "\t<You've entered incorrect credentials 3 times. Access denied.>\n";
            }
            break;


        case 2:
            while (tries < 3 && !isLoggedIn) {
                std::cout << "\tEnter your ID: ";
                std::cin >> User_ID;

                std::cout << "\tEnter your password: ";
                std::getline(std::cin >> std::ws, User_Password);

                std::pair<bool, std::string> result = verify_login(User_ID, User_Password, filename);

                if (result.first) {
                    std::cout << "\n\tYou successfully logged in.\n";
                    isLoggedIn = true;
                    std::system("CLEAR");
                    name = result.second;
                    std::cout << "\tWelcome, " << name << "!\n";
                    //introducing name_"idstudent" for adding a grade so call the function add_grade()

                    std::cout<<"Please choose:\n 1. Add student grade\n 2. See student grade\n";

                    int prof_option ;

                    std::cin>>prof_option;

                    if (prof_option != 1 && prof_option != 2)
                    {
                        std::cout<<"Please choose a number between 1 and 2!";
                    }

                    std::cout << "\tEnter student ID: ";
                    std::cin >> User_ID;
                    std::string name_of_student_file = "student_";
                    name_of_student_file += std::to_string(User_ID) + ".txt";
                    std::pair<bool, std::string> check_student =  verify_login_justid(name_of_student_file, filename);


                    std::string prof_subject = get_prof_subject(filename);

                    if (! check_student.first){

                        std::cout << "You dind't entered the correct Id ";
                        exit(1);
                    }
                    else
                    {
                        std::cout << " Student has been found ";

                    }


                    switch (prof_option) {
                        case 1: add_grade(prof_subject, name_of_student_file);
                        case 2: see_all_grades(name_of_student_file);
                        default: {}


                    }


                    
                } else {
                    if (tries < 2) {
                        std::cout << "\t<Incorrect ID or Password. Please try again.>\n";
                    }
                }

                tries++;
            }

            if (tries == 3 && !isLoggedIn) {
                std::cout << "\t<You've entered incorrect credentials 3 times. Access denied.>\n";
            }
            break;


        case 3:
            while (tries < 3 && !isLoggedIn) {
                std::cout << "\tEnter your ID: ";
                std::cin >> User_ID;

                std::cout << "\tEnter your password: ";
                std::getline(std::cin >> std::ws, User_Password);

                std::pair<bool, std::string> result = verify_login(User_ID, User_Password, file_name);

                if (result.first) {
                    std::cout << "\n\tYou successfully logged in.\n";
                    isLoggedIn = true;
                    std::system("CLEAR");
                    name_s = result.second;

                    std::cout << "\tWelcome, " << name_s << "!\n";

                    std::string name_of_student_file = "student_";
                    name_of_student_file += std::to_string(User_ID) + ".txt";
                    std::pair<bool, std::string> check_student =  verify_login_justid(name_of_student_file, filename);
                    see_all_grades(name_of_student_file);

                } else {
                    if (tries < 2) {
                        std::cout << "\t<Incorrect ID or Password. Please try again.>\n";
                    }
                }

                tries++;
            }

            if (tries == 3 && !isLoggedIn) {
                std::cout << "\t<You've entered incorrect credentials 3 times. Access denied.>\n";
            }
            break;
        default:
            break;
        
    }





    return 0;
}


