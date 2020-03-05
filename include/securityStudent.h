#ifndef SECURITY_STUDENT_H
#define SECURITY_STUDENT_H

#include "student.h"
#include <utility>

class SecurityStudent : public Student
{
public:
	SecurityStudent(std::string studentId, std::string firstName,
		       std::string lastName, std::string emailAddress, int age,
		       std::array<int, 3> daysToComplete3Courses)
	    : Student(std::move(studentId), std::move(firstName), std::move(lastName), std::move(emailAddress), age, daysToComplete3Courses)
	{
		degreeType_ = Degree::SECURITY;
	}

	~SecurityStudent() = default;

	Degree getDegreeProgram() const override;
};


#endif // SECURITY_STUDENT_H
