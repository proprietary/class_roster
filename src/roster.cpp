#include "roster.h"
#include "networkStudent.h"
#include "securityStudent.h"
#include "softwareStudent.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <vector>

std::string getDegreeTypeString(Degree degree)
{
	switch (degree) {
	case Degree::NETWORKING:
		return "Networking";
	case Degree::SECURITY:
		return "Security";
	case Degree::SOFTWARE:
		return "Software";
	}
}

Degree getDegreeTypeEnum(std::string degreeName)
{
	if (degreeName == "NETWORK") {
		return Degree::NETWORKING;
	} else if (degreeName == "SECURITY") {
		return Degree::SECURITY;
	} else if (degreeName == "SOFTWARE") {
		return Degree::SOFTWARE;
	} else {
		throw std::invalid_argument(
		    "Degree name has no corresponding member in the enumerated type of degrees.");
	}
}

std::vector<std::string> splitCommaSeparatedList(std::istringstream input)
{
	std::vector<std::string> out;
	for (std::string token; std::getline(input, token, ',');) {
		out.push_back(token);
	}
	return out;
}

namespace {
bool validEmail(const std::string& emailAddress)
{
	// A valid email should include an at sign ('@') and period ('.')
	// and should not include a space (' ').
	bool hasAtSign = false;
	bool hasPeriod = false;
	for (auto characterIterator = emailAddress.begin(); characterIterator != emailAddress.end();
	     ++characterIterator) {
		switch (*characterIterator) {
		case '@':
			hasAtSign = true;
			break;
		case '.':
			hasPeriod = true;
			break;
		case ' ':
			return false;
		}
	}
	return hasAtSign && hasPeriod;
}
} // namespace



void Roster::resize()
{
	// Create a new array double the size and copy the old data to the new array
	size_t oldCapacity = capacity_;
	// check for overflow
	if (oldCapacity >= (std::numeric_limits<size_t>::max() >> 1)) {
		throw std::overflow_error(
		    "Class roster data table exceeded highest available index.");
	}
	// allocate a new array with double the capacity
	capacity_ *= 2;
	Student** newClassRosterArray = new Student*[capacity_];
	// Copy old elements to the newly allocated array
	std::copy(classRosterArray_, classRosterArray_ + oldCapacity, newClassRosterArray);
	delete[] classRosterArray_;
	classRosterArray_ = newClassRosterArray;
}

void Roster::add(std::string studentId, std::string firstName, std::string lastName,
		 std::string emailAddress, int age, int daysInCourse1, int daysInCourse2,
		 int daysInCourse3, Degree degreeProgram)
{
	// instantiate the correct type of student
	Student* student = nullptr;
	std::array<int, 3> daysToComplete3Courses = {daysInCourse1, daysInCourse2, daysInCourse3};
	switch (degreeProgram) {
	case Degree::NETWORKING:
		student = new NetworkStudent(studentId, firstName, lastName, emailAddress, age,
					     daysToComplete3Courses);
		break;
	case Degree::SECURITY:
		student = new SecurityStudent(studentId, firstName, lastName, emailAddress, age,
					      daysToComplete3Courses);
		break;
	case Degree::SOFTWARE:
		student = new SoftwareStudent(studentId, firstName, lastName, emailAddress, age,
					      daysToComplete3Courses);
		break;
	}
	// add new student to array
	size_ += 1;
	if (size_ > capacity_) {
		// increase capacity of array if necessary
		resize();
	}
	classRosterArray_[size_ - 1] = student;
}

Student** const Roster::find(std::string studentId) const
{
	for (int i = 0; i < size_; ++i) {
		if (studentId == classRosterArray_[i]->getStudentId()) {
			return &classRosterArray_[i];
		}
	}
	throw std::invalid_argument("student ID not found in class roster table");
}

void Roster::remove(std::string studentId)
{
	try {
		// Remove element from class roster array
		Student** it = find(studentId);
		// release memory associated with abstract student
		delete *it;
		// left shift elements in range [target, end)
		while (++it != classRosterArray_ + size_) {
			*(it - 1) = *it;
		}
		size_ -= 1; // 1 element is removed
			    // release resources

	} catch (const std::invalid_argument& err) {
		std::cerr << "Student ID (" << studentId << ") not found: " << err.what()
			  << std::endl;
	}
}

/// Prints a complete tab-separated list of student data using
/// accessor functions with the provided format: 1 [tab] First Name:
/// John [tab] Last Name: Smith [tab] Age: 20 [tab]daysInCourse: {35,
/// 40, 55} Degree Program: Security. The printAll() function should
/// loop through all the students in classRosterArray and call the
/// print() function for each student.
void Roster::printAll() const
{
	forEach([](const Student* student) -> void { printStudent(*student); });
}

void Roster::printAverageDaysInCourse(std::string studentId) const
{
	const Student* student = *find(studentId);
	const std::array<int, 3> days = student->getDaysToComplete3Courses();
	double sum = 0.0;
	for (auto it = days.begin(); it != days.end(); ++it) {
		sum += *it;
	}
	const double average = sum / days.size();
	std::cout << average << std::endl;
}

void Roster::printInvalidEmails() const
{
	forEach([](const Student* student) -> void {
		if (!validEmail(student->getEmailAddress())) {
			std::cout << student->getEmailAddress() << std::endl;
		}
	});
}

void Roster::printByDegreeProgram(Degree degreeProgram) const
{
	forEach([degreeProgram](const Student* student) -> void {
		if (degreeProgram == student->getDegreeProgram()) {
			printStudent(*student);
		}
	});
}

void printStudent(const Student& student)
{
	static const char sep = '\t';
	const std::array<int, 3> days = student.getDaysToComplete3Courses();
	std::cout << student.getStudentId() << sep << "First Name: " << student.getFirstName()
		  << sep << "Last Name: " << student.getLastName() << sep
		  << "Age: " << student.getAge() << sep << "daysInCourse: {" << days[0] << ", "
		  << days[1] << ", " << days[2] << '}' << sep
		  << "degreeProgram: " << getDegreeTypeString(student.getDegreeProgram())
		  << std::endl;
}

