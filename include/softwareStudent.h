#ifndef SOFTWARE_STUDENT_H
#define SOFTWARE_STUDENT_H

#include "student.h"
#include <utility>

class SoftwareStudent : public Student
{
public:
	SoftwareStudent(std::string studentId, std::string firstName, std::string lastName,
			std::string emailAddress, int age,
			std::array<int, 3> daysToComplete3Courses)
	    : Student(std::move(studentId), std::move(firstName), std::move(lastName), std::move(emailAddress), age, daysToComplete3Courses)
	{
		degreeType_ = Degree::SOFTWARE;
	}

	~SoftwareStudent() = default;

	Degree getDegreeProgram() const override;
};

#endif // SOFTWARE_STUDENT_H
