#include "student.h"
#include <iostream>

void Student::print() const
{
	static const char* sep = "\t";
	std::cout << "student id" << sep << "first name" << sep << "last name" << sep << std::endl;
}

std::string Student::getStudentId() const { return studentId_; }

std::string Student::getFirstName() const { return firstName_; }
std::string Student::getLastName() const { return lastName_; }
std::string Student::getEmailAddress() const { return emailAddress_; }
int Student::getAge() const { return age_; }
std::array<int, 3> Student::getDaysToComplete3Courses() const
{
	return daysToComplete3Courses_;
}

void Student::setStudentId(std::string studentId) { studentId_ = std::move(studentId); }
void Student::setFirstName(std::string firstName) { firstName_ = std::move(firstName); }
void Student::setLastName(std::string lastName) { lastName_ = std::move(lastName); }
void Student::setEmailAddress(std::string emailAddress) { emailAddress_ = std::move(emailAddress); }
void Student::setAge(int age) { age_ = age; }
void Student::setDaysToComplete3Courses(std::array<int, 3> daysToComplete3Courses)
{
	daysToComplete3Courses_ = daysToComplete3Courses;
}
