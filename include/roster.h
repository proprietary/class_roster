#ifndef ROSTER_H
#define ROSTER_H

#include "student.h"
#include <cctype>
#include <string>

class Roster
{
public:
	/// Sets instance variables
	void add(std::string studentId, std::string firstName, std::string lastName,
		 std::string emailAddress, int age, int daysInCourse1,
		 int daysInCourse2, int daysInCourse3, Degree degreeProgram);

	/// Removes students from the roster by student ID. If the student
	/// ID does not exist, the function prints an error message
	/// indicating that the student was not found.
	void remove(std::string studentId);

	/// Prints a complete tab-separated list of student data using
	/// accessor functions with the provided format: 1 [tab] First Name:
	/// John [tab] Last Name: Smith [tab] Age: 20 [tab]daysInCourse: {35,
	/// 40, 55} Degree Program: Security. The printAll() function should
	/// loop through all the students in classRosterArray and call the
	/// print() function for each student.
	void printAll() const;

	/// Prints a student’s average number of days in the three courses
	void printAverageDaysInCourse(std::string studentId) const;

	/// Verifies student email addresses and displays all invalid
	/// email addresses to the user. Note: A valid email should
	/// include an at sign ('@') and period ('.') and should not
	/// include a space (' ').
	void printInvalidEmails() const;

	/// Prints out student information for a degree program specified
	/// by an enumerated type
	void printByDegreeProgram(Degree degreeProgram) const;

	/// Loop through members of class roster array
	template<typename Lambda> void forEach(Lambda fn) const {
		for (Student** it = classRosterArray_; it != classRosterArray_ + size_; ++it) {
			fn(*it);
		}
	}

	Roster() { classRosterArray_ = new Student*[CLASS_ROSTER_ARRAY_INIT_CAPACITY]; }
	~Roster() noexcept
	{
		if (classRosterArray_ != nullptr) {
			for (Student** it = classRosterArray_; it != classRosterArray_ + size_; ++it) {
				// deallocate each abstract student
				delete *it;
			}
			// deallocate the vector holding pointers to these student types
			delete[] classRosterArray_;
		}
	}

	// unimplemented
	Roster(const Roster&) = delete;
	Roster(Roster&&) noexcept = delete;
	Roster& operator=(const Roster&) = delete;
	Roster& operator=(Roster&&) = delete;

private:
	// In practice I would use std::vector, but the assignment asked for manual memory
	// operations.
	static const size_t CLASS_ROSTER_ARRAY_INIT_CAPACITY = 10;
	size_t capacity_ = CLASS_ROSTER_ARRAY_INIT_CAPACITY;
	size_t size_ = 0;
	Student** classRosterArray_ = nullptr;

	/// Reallocates the array by 2x
	void resize();

	/// Lookup by student ID
	Student** const find(std::string studentId) const;
};

/// Print out an individual student to standard output
void printStudent(const Student&);


/// Map string to enumeration value
Degree getDegreeTypeEnum(std::string degreeName);

/// Get string representation of enumerated degree type
std::string getDegreeTypeString(Degree degree);

/// Utility function to split a string input stream by commas
std::vector<std::string> splitCommaSeparatedList(std::istringstream input);

#endif // ROSTER_H
