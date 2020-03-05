#include "roster.h"
#include <gtest/gtest.h>

TEST(TestRoster, TestAddOneElement) {
	Roster classRoster{};
	classRoster.add("A1", "John", "Doe", "mail@example.com", 20, 1, 2, 3, Degree::SOFTWARE);
	classRoster.forEach([](const Student* student) -> void {
		ASSERT_TRUE(student->getStudentId() == "A1");
		ASSERT_TRUE(student->getFirstName() == "John");
		ASSERT_TRUE(student->getLastName() == "Doe");
		ASSERT_TRUE(student->getEmailAddress() == "mail@example.com");
		ASSERT_TRUE(student->getAge() == 20);
		auto days = student->getDaysToComplete3Courses();
		ASSERT_EQ(days[0], 1);
		ASSERT_EQ(days[1], 2);
		ASSERT_EQ(days[2], 3);
		ASSERT_EQ(student->getDegreeProgram(), Degree::SOFTWARE);
	});
}

TEST(TestRoster, TestAddMultipleElements) {
	// Tests resizing of dynamic array
	Roster classRoster{};
	static constexpr int ROUNDS = 100;
	for (int i = 0; i < ROUNDS; ++i) {
		classRoster.add("A1", "John", "Doe", "mail@example.com", 20, i, i+1, i+2, Degree::SOFTWARE);
	}
	int count = 0;
	classRoster.forEach([&count](const Student* student) -> void {
		printStudent(*student);
		ASSERT_TRUE(student->getStudentId() == "A1");
		count += 1;
	});
	ASSERT_EQ(count, 100);
}
