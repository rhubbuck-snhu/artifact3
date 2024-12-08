#pragma once

void displayMenu();
void displaySubMenu();
int callback(void* NotUsed, int argc, char** argv, char** azColName);
void cleanCharInput(char* input);
void cleanUserInput(char* input);
int deletePre(int pre_o, char* course_n);
int updatePre(int pre_o, char* course_n, char* pre_t);
int insertData(char* newNumber, char* newTitle);
int deleteData(char* courseNumber);
int getPreNum(char* courseNumber);
int selectRow(char* courseNumber, bool show_all);
int selectAllData();