#include "roster.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

int main(void)
{
	// 1. Print out to the screen, via your application, the course
	// title, the programming language used, your student ID, and your
	// name.
	std::cout << "Scripting and Programming" << std::endl
		  << "C++" << std::endl
		  << "#001281141" << std::endl
		  << "Zelly Snyder" << std::endl;
	// 2. Create an instance of the Roster class called classRoster.
	Roster classRoster;
	// 3. Add each student to classRoster.
	const std::string studentData[] = {
	    "A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY",
	    "A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,NETWORK",
	    "A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE",
	    "A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY",
	    "A5,[firstname],[lastname],[emailaddress],[age],[numberofdaystocomplete3courses],"
	    "SOFTWARE"};
	std::for_each(
	    &studentData[0], &studentData[0] + sizeof(studentData) / sizeof(studentData[0]),
	    [&classRoster](const std::string& src) -> void {
		    // parse line from data table
		    std::vector<std::string> tokens =
			splitCommaSeparatedList(std::istringstream{src});
		    if (tokens.size() != 9) {
			    // Comma-separated line of input too short or too long
			    // silently fail
			    return;
		    }
		    std::string studentId{tokens[0]};
		    std::string firstName{tokens[1]};
		    std::string lastName{tokens[2]};
		    std::string emailAddress{tokens[3]};
		    int age = std::stoi(tokens[4]);
		    std::array<int, 3> daysToComplete3Courses{
			{std::stoi(tokens[5]), std::stoi(tokens[6]), std::stoi(tokens[7])}};
		    std::cout << tokens[8] << std::endl;
		    Degree degreeType = getDegreeTypeEnum(tokens[8]);
		    classRoster.add(studentId, firstName, lastName, emailAddress, age,
				    daysToComplete3Courses[0], daysToComplete3Courses[1],
				    daysToComplete3Courses[2], degreeType);
	    });
	std::cout << std::endl;
	// 4. Convert the following pseudo code to complete the rest of the main() function:
	// classRoster.printAll();
	// classRoster.printInvalidEmails();
	// // loop through classRosterArray and for each element:
	// classRoster.printAverageDaysInCourse(/*current_object's student id*/);
	// classRoster.printByDegreeProgram(SOFTWARE);
	// classRoster.remove("A3");
	// classRoster.remove("A3");
	//  //expected: the above line should print a message saying such a student with this ID was
	//  not found.
	std::cout << "classRoster.printAll():" << std::endl;
	classRoster.printAll();
	std::cout << std::endl;
	std::cout << "Invalid emails:" << std::endl;
	classRoster.printInvalidEmails();
	std::cout << std::endl;
	// loop through classRosterArray
	std::cout << "Average days in course:" << std::endl;
	classRoster.forEach([&classRoster](const Student* student) -> void {
		classRoster.printAverageDaysInCourse(student->getStudentId());
	});
	std::cout << std::endl;
	std::cout << "Students in Software degree program:" << std::endl;
	classRoster.printByDegreeProgram(Degree::SOFTWARE);
	std::cout << std::endl;
	classRoster.remove("A3");
	classRoster.remove("A3");

	return EXIT_SUCCESS;
}
