#ifndef NETWORK_STUDENT_H
#define NETWORK_STUDENT_H

#include "student.h"
#include <utility>

class NetworkStudent : public Student
{
public:
	NetworkStudent(std::string studentId, std::string firstName, std::string lastName,
		       std::string emailAddress, int age,
		       std::array<int, 3> daysToComplete3Courses)
	    : Student(std::move(studentId), std::move(firstName), std::move(lastName), std::move(emailAddress), age, daysToComplete3Courses)
	{
		degreeType_ = Degree::NETWORKING;
	}

	~NetworkStudent() = default;

	Degree getDegreeProgram() const override;
};

#endif // NETWORK_STUDENT_H
