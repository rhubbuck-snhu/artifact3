//============================================================================
// Name           : CS-499 Milestone 3
// Author         : Ryan Hubbuck
// Created On     : 06/14/2023
// Last Modified  : 12/07/2024
// Description    : The purpose of this application is to allow users to 
//                  dynamically manage a list of college courses and their 
//                  associted prerequisites. SQLite is required for proper
//                  fucntionality. Additionally, the following files are
//                  required for proper functionality:
//                  - functions.h
//============================================================================

#include <sqlite3.h>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "functions.h"

using namespace std;

int main(int argc, char* argv[]) {
    int menuChoice = 0;
    int subMenuChoice = 0;
	char newPrereq[50];
	char userCourse[20];
	char newNumber[20];
	char newTitle[50];
	const char* dir = "C:\\Users\\rhubb\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\Files\\library.db";

    while (menuChoice != 9) { 
        vector<vector<string>> content;
        vector<string> row; 

        displayMenu();

        while (!(cin >> menuChoice)) { // validate user inputs type int
            std::cout << std::endl << "Error - enter a valid menu choice: ";
            cin.clear();
            cin.ignore(123, '\n');
        }

        switch (menuChoice) {


        case 1: // print courses
			selectAllData();
			break;

        case 2: // print specific course details
            std::cout << std::endl << "What course do you want to know about? " << std::endl;
			std::cin.ignore();
			std::cin.getline(newTitle, 50);
			cleanCharInput(newTitle);
			selectRow(newTitle, true);
            break;

        case 3: { // delte a course by key/number
            std::cout << std::endl << "Enter a course number you want to delete: " << std::endl;
			std::cin.ignore();
			std::cin.getline(userCourse, 20);
			cleanCharInput(userCourse);
			deleteData(userCourse);
            break;
		}
        case 4: // create a new course with number and title
            std::cout << std::endl << "Enter the new course's number (i.e. MATH101). " << std::endl;
			std::cin.ignore();
			std::cin.getline(newNumber, 20);
			cleanCharInput(newNumber);
            std::cout << std::endl << "Enter the new course's title (i.e. Reverse Engineering). " << std::endl;
            std::cin.ignore();
            std::cin.getline(newTitle, 50);
			cleanUserInput(newTitle);
			insertData(newNumber, newTitle);
            break;

        case 5: { // list, add to, or delete a course's prerequisites
            std::cout << std::endl << "Enter a course number to manage it's prerequisites. " << std::endl;
			std::cin.ignore();
			std::cin.getline(userCourse, 20);
			cleanCharInput(userCourse);
			selectRow(userCourse, true);
			
			while (subMenuChoice != 3) {
				int pre_num = getPreNum(userCourse);
				std::cout << "This course has " << pre_num << " prerequisites. You can add " << 3 - pre_num << " more." << std::endl << std::endl;
				displaySubMenu();
				while (!(cin >> subMenuChoice)) {
					std::cout << "Error - enter a valid menu choice: ";
					cin.clear();
					cin.ignore(123, '\n');
				}
				if (subMenuChoice == 1 and pre_num == 3) {
					subMenuChoice = 4;
				}
				std::cout << endl;
				switch (subMenuChoice) {
				case 1: {
					std::cout << "Enter the prerequisite's course number to add. " << std::endl;
					std::cin.ignore();
					std::cin.getline(newPrereq, 50);
					cleanCharInput(newPrereq);
					if (strlen(newPrereq) > 2) {
						if (pre_num == 0) {
							updatePre(1, userCourse, newPrereq);
						}
						else if (pre_num == 1) {
							updatePre(2, userCourse, newPrereq);
						}
						else {
							updatePre(3, userCourse, newPrereq);
						}
					}
					break;
				}
				case 2:
					selectRow(userCourse, false);
					std::cout << "Enter the prerequisite number to delete (example 1, 2, or 3; limit 1). " << std::endl;
					std::cin.ignore();
					int num;
					while (true) {
						cout << "Enter an integer: ";
						cin >> num;

						if (cin.fail() || num < 1 || num > 3) {
							cout << "Invalid input. Please enter a valid integer." << endl;
							cin.clear(); 
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
						else {
							break; 
						}
					}
					deletePre(num, userCourse);
					break;
				case 3:
					break;
				default:
					std::cout << std::endl << "Please ensure the course is not at the prerequisite limit and enter a valid menu choice. " << std::endl;
				}
			}
			subMenuChoice = 0;
            break;
		}
        default: // invalid input
            std::cout << std::endl << "Please enter a valid menu choice." << std::endl << std::endl;
        }
    }
    std::cout << "Good bye." << std::endl;
    return 0;
}
