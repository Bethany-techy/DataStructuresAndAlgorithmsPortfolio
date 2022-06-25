#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

/**
* Course Object used to track course information
*/
class Course {
public:
	string courseNumber;
	string name;
	vector<string> preRequisites;
};

std::map<string, Course> Courses;

/**
 * Display options menu and return the user selection
 */
int DisplayMenu() {
	cout << endl << "1. Load Data Structure." << endl;
	cout << "2. Print Course List." << endl;
	cout << "3. Print Course." << endl;
	cout << "4. Exit" << endl;

	cout << endl << "What would you like to do? ";

	// grab selection from user
	int result;
	cin >> result;

	return result;
}

/**
 * Load data structure from disk and place in our course information
 */
void LoadDataStructure() {
	cout << "What is the name of the course file to load?" << endl;

	string courseFilename;
	cin >> courseFilename;

	// try to open file
	fstream courseFile;
	courseFile.open(courseFilename, ios::in);

	if (!courseFile.is_open()) {
		cout << "ERROR: Unable to load file";
		return;
	}

	// clear existing courses
	Courses.clear();

	// read file line by line and insert into our data structure
	string line;
	while (getline(courseFile, line)) {
		vector<string> courseStrings;

		// split line by commas to get individual strings
		stringstream lineStream(line);

		while (lineStream.good()) {
			string subString;
			getline(lineStream, subString, ',');
			courseStrings.push_back(subString);
		}

		// create course object
		Course newCourse;
		newCourse.courseNumber = courseStrings[0];
		newCourse.name = courseStrings[1];

		for (size_t i = 2; i < courseStrings.size(); ++i) {
			newCourse.preRequisites.push_back(courseStrings[i]);
		}

		// insert course into sorted map
		Courses[courseStrings[0]] = newCourse;
	}

	courseFile.close();
}

/**
 * Print entire course list in order
 */
void PrintCourseList() {
	// map is already sorted so we can iterate without sorting first
	for (auto iterator = Courses.begin(); iterator != Courses.end(); iterator++) {
		cout << iterator->second.courseNumber << ", " << iterator->second.name << endl;
	}
}

/**
 * Print individual course and prerequisites using course number
 */
void PrintIndividualCourse(string courseNumber) {
	auto iterator = Courses.find(courseNumber);
	if (iterator == Courses.end()) {
		cout << "Unable to locate course" << endl;
	}
	else {
		// print course number and name
		cout << iterator->second.courseNumber << ", " << iterator->second.name << endl;

		// print pre requisites
		cout << "Prerequisites : ";

		for (size_t i = 0; i < iterator->second.preRequisites.size(); ++i) {
			cout << iterator->second.preRequisites[i];

			if (i < iterator->second.preRequisites.size() - 1)
				cout << ", ";
		}

		cout << endl;
	}
}

/**
* Perform an action based on the menu selection. Return true if program should exit
*/
bool PerformAction(int option) {
	if (option == 1) {
		LoadDataStructure();
	}
	else if (option == 2) {
		PrintCourseList();
	}
	else if (option == 3) {
		cout << "What course do you want to know about? ";

		string courseNumber;
		cin >> courseNumber;

		PrintIndividualCourse(courseNumber);
	}
	else if (option == 4) {
		return true;
	}
	else {
		cout << option << " is not a valid selection." << endl;
	}

	return false;
}

/**
* Program Entry Point
*/
int main() {	
	cout << "Welcome to the course planner." << endl;

	while (true) {
		// display menu and record user selection
		int option = DisplayMenu();

		// process user selection, exiting loop if true is returned
		if (PerformAction(option)) {
			break;
		}
	}

	return 0;
}
