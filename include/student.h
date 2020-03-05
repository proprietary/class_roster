#ifndef STUDENT_H
#define STUDENT_H

#include "degree.h"

#include <array>
#include <string>
#include <vector>

class Student
{
public:
	// constructor
	Student(std::string studentId, std::string firstName, std::string lastName,
		std::string emailAddress, int age,
		std::array<int, 3> daysToComplete3Courses)
	    : studentId_(studentId), firstName_(firstName), lastName_(lastName),
	      emailAddress_(emailAddress), age_(age),
	      daysToComplete3Courses_(daysToComplete3Courses)
	{
	}

	// enforce using the derived classes
	Student() = delete;
	Student(const Student&) = delete;
	const Student& operator=(const Student&) = delete;
	Student(Student&& other) noexcept = delete;
	Student& operator=(Student&&) = delete;

	/// Print student specific data
	virtual void print() const;

	/// Get degree program of this student (implemented in derived classes)
	virtual Degree getDegreeProgram() const = 0;

	// getters
	std::string getStudentId() const;
	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getEmailAddress() const;
	int getAge() const;
	std::array<int, 3> getDaysToComplete3Courses() const;

	// setters
	void setStudentId(std::string);
	void setFirstName(std::string);
	void setLastName(std::string);
	void setEmailAddress(std::string);
	void setAge(int);
	void setDaysToComplete3Courses(std::array<int, 3>);

	virtual ~Student() {
		// std::array manages memory of daysToComplete3Courses
	}

protected:
	Degree degreeType_;

private:
	std::string studentId_;
	std::string firstName_;
	std::string lastName_;
	std::string emailAddress_;
	int age_;
	std::array<int, 3> daysToComplete3Courses_;
};
#endif // STUDENT_H
