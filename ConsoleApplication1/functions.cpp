#include <vector>
#include <string>
#include "functions.h"
#include <iostream>
#include <sqlite3.h>


// Function to display the user menu
void displayMenu() {
    std::cout << std::string(32, '*') << std::endl;
    std::cout << "* Course Planner Main Menu:    *" << std::endl;
    std::cout << "*" <<  std::string(30, '_') << "*" << std::endl;
    std::cout << "*  1. Print Course List.       *" << std::endl;
    std::cout << "*  2. Print Course.            *" << std::endl;
    std::cout << "*  3. Delete a Course.         *" << std::endl;
    std::cout << "*  3. Delete a Course.         *" << std::endl;
    std::cout << "*  4. Add a new Course.        *" << std::endl;
    std::cout << "*  5. Manage Prerequisites.    *" << std::endl;
    std::cout << "*  9. Exit                     *" << std::endl;
    std::cout << std::string(32, '*') << std::endl;
    std::cout << std::endl <<  "Enter an option: ";
}

// Function to display user submenu
void displaySubMenu() {
    std::cout << std::string(28, '*') << std::endl;
    std::cout << "*  1. Add prerequisite.    *" << std::endl;
    std::cout << "*  2. Delete prerequisite. *" << std::endl;
    std::cout << "*  3. Back.                *" << std::endl;
    std::cout << std::string(28, '*') << std::endl;
    std::cout << "Enter an option:";
}

int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		std::string str_n(azColName[i]);
		if (str_n == "course_number" or str_n == "course_title") {
			std::cout << argv[i] << "  ";
		}
	}
	std::cout << std::endl;

	return 0;
};


void cleanCharInput(char* input) {
	int i = 0, j = 0;
	while (input[i]) {
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n') {
			input[j++] = toupper(input[i]);
		}
		i++;
	}
	input[j] = '\0';
}

void cleanUserInput(char* input) {
	int i = 0, j = 0;
	while (input[i]) {
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n') {
			input[j++] = input[i];
		}
		i++;
	}
	input[j] = '\0';
}

int deletePre(int pre_o, char* course_n) {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	// Open database
	rc = sqlite3_open("C:\\Users\\rhubb\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\Files\\library.db", &db);
	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return(1);
	}

	sqlite3_stmt* stmt;

	if (pre_o == 1) {
		// Prepare the UPDATE statement
		const char* sql = "UPDATE courses SET prereq_1 = prereq_2, prereq_2 = prereq_3, prereq_3 = ' ' WHERE course_number = ?;";
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_close(db);
			return(1);
		}

		// Bind values to the statement parameters
		sqlite3_bind_text(stmt, 1, course_n, -1, SQLITE_STATIC);

		// Execute the statement
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		}
		else {
			std::cout << "Data insertion successful!" << std::endl << std::endl;
		}
	}
	else if (pre_o == 2) {
		// Prepare the UPDATE statement
		const char* sql = "UPDATE courses SET prereq_2 = prereq_3, prereq_3 = ' ' WHERE course_number = ?;";
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_close(db);
			return(1);
		}

		// Bind values to the statement parameters
		sqlite3_bind_text(stmt, 1, course_n, -1, SQLITE_STATIC);

		// Execute the statement
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		}
		else {
			std::cout << "Data insertion successful!" << std::endl << std::endl;
		}
	}
	else {
		// Prepare the UPDATE statement
		const char* sql = "UPDATE courses SET prereq_3 = ' ' WHERE course_number = ?;";
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_close(db);
			return(1);
		}

		// Bind values to the statement parameters
		sqlite3_bind_text(stmt, 1, course_n, -1, SQLITE_STATIC);

		// Execute the statement
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		}
		else {
			std::cout << "Record updated!" << std::endl << std::endl;
		}
	}

	// Reset the statement for next use
	sqlite3_reset(stmt);
	// Finalize the statement
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return 0;
}

int updatePre(int pre_o, char* course_n, char* pre_t) {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	// Open database
	rc = sqlite3_open("C:\\Users\\rhubb\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\Files\\library.db", &db);
	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return(1);
	}

	sqlite3_stmt* stmt;

	if (pre_o == 1) {
		// Prepare the UPDATE statement
		const char* sql = "UPDATE courses SET prereq_1 = ? WHERE course_number = ?;";
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_close(db);
			return(1);
		}

		// Bind values to the statement parameters
		sqlite3_bind_text(stmt, 1, pre_t, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, course_n, -1, SQLITE_STATIC);

		// Execute the statement
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		}
		else {
			std::cout << "Data insertion successful!" << std::endl << std::endl;
		}
	}
	else if (pre_o == 2) {
		// Prepare the UPDATE statement
		const char* sql = "UPDATE courses SET prereq_2 = ? WHERE course_number = ?;";
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_close(db);
			return(1);
		}

		// Bind values to the statement parameters
		sqlite3_bind_text(stmt, 1, pre_t, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, course_n, -1, SQLITE_STATIC);

		// Execute the statement
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		}
		else {
			std::cout << "Data insertion successful!" << std::endl << std::endl;
		}
	}
	else {
		// Prepare the UPDATE statement
		const char* sql = "UPDATE courses SET prereq_3 = ? WHERE course_number = ?;";
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_close(db);
			return(1);
		}

		// Bind values to the statement parameters
		sqlite3_bind_text(stmt, 1, pre_t, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, course_n, -1, SQLITE_STATIC);

		// Execute the statement
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		}
		else {
			std::cout << "Data insertion successful!" << std::endl << std::endl;
		}
	}

	// Reset the statement for next use
	sqlite3_reset(stmt);
	// Finalize the statement
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return 0;
}

int insertData(char* newNumber, char* newTitle) {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	// Open database
	rc = sqlite3_open("C:\\Users\\rhubb\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\Files\\library.db", &db);
	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return(1);
	}

	// Prepare the UPDATE statement
	sqlite3_stmt* stmt;
	const char* sql = "INSERT INTO courses (course_number, course_title, prereq_1, prereq_2, prereq_3) VALUES (?, ?, ' ', ' ', ' ');";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return(1);
	}

	// Bind values to the statement parameters
	sqlite3_bind_text(stmt, 1, newNumber, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, newTitle, -1, SQLITE_STATIC);


	// Execute the statement
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "Data insertion successful!" << std::endl << std::endl;
	}

	// Reset the statement for next use
	sqlite3_reset(stmt);
	// Finalize the statement
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return 0;
}

int deleteData(char* courseNumber) {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	// Open database
	rc = sqlite3_open("C:\\Users\\rhubb\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\Files\\library.db", &db);
	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return(1);
	}

	// Prepare the UPDATE statement
	sqlite3_stmt* stmt;
	const char* sql = "DELETE FROM courses WHERE course_number = ?;";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return(1);
	}

	// Bind values to the statement parameters
	rc = sqlite3_bind_text(stmt, 1, courseNumber, -1, SQLITE_STATIC);

	// Execute the statement
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "Data deletion successful!" << std::endl << std::endl;
	}

	// Reset the statement for next use
	sqlite3_reset(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return 0;
}

int getPreNum(char* courseNumber) {
	sqlite3* db;
	int rc = sqlite3_open("C:\\Users\\rhubb\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\Files\\library.db", &db);
	int row_f = 0;
	int pre_n = 0;

	if (rc != SQLITE_OK) {
		std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
	}

	const char* sql = "SELECT * FROM courses WHERE course_number = ?";
	sqlite3_stmt* stmt;

	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << std::endl;
	}

	// Bind value to the parameter
	rc = sqlite3_bind_text(stmt, 1, courseNumber, -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Cannot bind parameter: " << sqlite3_errmsg(db) << std::endl;
	}

	// Execute the statement and fetch the result
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		const char* number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		const char* pre1 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		const char* pre2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		const char* pre3 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

		if (strlen(pre1) > 2) {
			pre_n = 1;
		}
		if (strlen(pre2) > 2) {
			pre_n = 2;
		}
		if (strlen(pre3) > 2) {
			pre_n = 3;
		}

		std::cout << std::endl;
		row_f = 1;
	}

	if (row_f == 0) {
		std::cout << std::endl << "No record found." << std::endl << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return pre_n;
}

int selectRow(char* courseNumber, bool show_all) {
	sqlite3* db;
	int rc = sqlite3_open("C:\\Users\\rhubb\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\Files\\library.db", &db);
	int row_f = 0;

	if (rc != SQLITE_OK) {
		std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}

	const char* sql = "SELECT * FROM courses WHERE course_number = ?";
	sqlite3_stmt* stmt;

	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Cannot prepare statement: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}

	// Bind value to the parameter
	rc = sqlite3_bind_text(stmt, 1, courseNumber, -1, SQLITE_STATIC);
	if (rc != SQLITE_OK) {
		std::cerr << "Cannot bind parameter: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}

	// Execute the statement and fetch the result
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		const char* number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		const char* pre1 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		const char* pre2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		const char* pre3 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

		if (show_all) {
			std::cout << std::endl << "Course Number: " << number << std::endl << "Course Title: " << title << std::endl;
		}

		if (strlen(pre1) > 2) {
			std::cout << "Prerequisite 1: " << pre1 << std::endl;
		}
		if (strlen(pre2) > 2) {
			std::cout << "Prerequisite 2: " << pre2 << std::endl;
		}
		if (strlen(pre3) > 2) {
			std::cout << "Prerequisite 3: " << pre3 << std::endl;
		}

		std::cout << std::endl;
		row_f = 1;
	}

	if (row_f == 0) {
		std::cout << std::endl << "No record found." << std::endl << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return 0;
}

int selectAllData() {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;

	// Open database
	rc = sqlite3_open("C:\\Users\\rhubb\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\Files\\library.db", &db);
	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return(1);
	}

	std::string sql = "SELECT * FROM courses;";

	sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
	// close connection
	sqlite3_close(db);
	return 0;
}