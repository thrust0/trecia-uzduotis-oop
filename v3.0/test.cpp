#include "student.hpp"
#include "student.hpp"
#include <gtest/gtest.h>


/** Vienetiniai testai Students klasei. Kiekvienas testas tikrina viena elgsena. */

#include <gtest/gtest.h>
#include <sstream>
#include "student.hpp"

/// Default Constructor Test
TEST(Student, default_constructor)
{
    Students s;
    EXPECT_EQ(s.first_name(), "");
    EXPECT_EQ(s.last_name(), "");
    EXPECT_EQ(s.exam(), 0);
}

/// Copy Constructor 
TEST(Student, copy_constructor)
{
    Students s1;
    s1.set_first_name("Jonas");
    s1.set_last_name("Jonaitis");
    s1.set_exam(8);
    s1.add_grade(7);
    s1.add_grade(9);

    Students s2(s1); // copy constructor

    EXPECT_EQ(s2.first_name(), s1.first_name());
    EXPECT_EQ(s2.last_name(), s1.last_name());
    EXPECT_EQ(s2.exam(), s1.exam());

    // deep copy check — modifying s2 should not affect s1
    s2.add_grade(5);
    EXPECT_NE(s2.result(), s1.result());
}

/// Copy Assignment 
TEST(Student, copy_assignment)
{
    Students s1;
    s1.set_first_name("Jonas");
    s1.set_last_name("Jonaitis");
    s1.set_exam(9);
    s1.add_grade(8);

    Students s2;
    s2 = s1; // copy assignment

    EXPECT_EQ(s2.first_name(), "Jonas");
    EXPECT_EQ(s2.last_name(), "Jonaitis");
    EXPECT_EQ(s2.exam(), 9);
}

/// Move Constructor 
TEST(Student, move_constructor)
{
    Students s1;
    s1.set_first_name("Jonas");
    s1.set_last_name("Jonaitis");
    s1.set_exam(7);
    s1.add_grade(6);

    Students s2(std::move(s1)); // move constructor

    EXPECT_EQ(s2.first_name(), "Jonas");
    EXPECT_EQ(s2.last_name(), "Jonaitis");
    EXPECT_EQ(s2.exam(), 7);

    // s1 should be cleared after move
    EXPECT_EQ(s1.first_name(), "");
    EXPECT_EQ(s1.last_name(), "");
}

/// Move Assignment 
TEST(Student, move_assignment)
{
    Students s1;
    s1.set_first_name("Petras");
    s1.set_last_name("Petraitis");
    s1.set_exam(10);
    s1.add_grade(9);

    Students s2;
    s2 = std::move(s1); // move assignment

    EXPECT_EQ(s2.first_name(), "Petras");
    EXPECT_EQ(s2.last_name(), "Petraitis");
    EXPECT_EQ(s2.exam(), 10);

    // s1 should be cleared
    EXPECT_EQ(s1.first_name(), "");
    EXPECT_EQ(s1.last_name(), "");
    EXPECT_EQ(s1.exam(), 0);
}

/// Destructor 
TEST(Student, destructor)
{
    {
        Students s;
        s.set_first_name("Jonas");
        s.add_grade(8);
        s.add_grade(9);
    } // destructor called here, should not crash
    SUCCEED();
}

/// Getters
TEST(Student, getters)
{
    Students s;
    s.set_first_name("Jonas");
    s.set_last_name("Jonaitis");
    s.set_exam(8);
    s.add_grade(6);
    s.add_grade(10);

    EXPECT_EQ(s.first_name(), "Jonas");
    EXPECT_EQ(s.last_name(), "Jonaitis");
    EXPECT_EQ(s.exam(), 8);
}

/// calc_result 
TEST(StudentTest, CalcResultWorks)
{
    Students s;
    s.add_grade(6);
    s.add_grade(8);  // homework avg = 7.0
    s.set_exam(9);   // result = 7.0*0.4 + 9*0.6 = 2.8 + 5.4 = 8.2

    EXPECT_DOUBLE_EQ(s.result(), 8.2);
}

/// calc_median even count 
TEST(StudentTest, CalcMedianWorks)
{
    Students s;
    s.add_grade(4);
    s.add_grade(8);  // grades + exam = {4, 8, 6}
    s.set_exam(6);   // sorted: {4, 6, 8}  median = 6

    EXPECT_DOUBLE_EQ(s.median(), 6.0);
}

/// calc_median odd count 
TEST(StudentTest, CalcMedianOddCount)
{
    Students s;
    s.add_grade(2);
    s.add_grade(4);
    s.add_grade(6);  // grades + exam = {2, 4, 6, 8}
    s.set_exam(8);   // sorted: {2, 4, 6, 8}  even  (4+6)/2 = 5.0

    EXPECT_DOUBLE_EQ(s.median(), 5.0);
}

/// Compare functions 
TEST(SortTest, CompareByFirstName)
{
    Students a, b;
    a.set_first_name("Adas");
    b.set_first_name("Zygimantas");

    EXPECT_TRUE(compare_by_first_name(a, b));
    EXPECT_FALSE(compare_by_first_name(b, a));
}

TEST(SortTest, CompareByLastName)
{
    Students a, b;
    a.set_last_name("Adas");
    b.set_last_name("Zygimantas");

    EXPECT_TRUE(compare_by_last_name(a, b));
    EXPECT_FALSE(compare_by_last_name(b, a));
}

TEST(SortTest, CompareByResult)
{
    Students a, b;
    a.add_grade(10); a.set_exam(10); // result = 10.0
    b.add_grade(4);  b.set_exam(4);  // result = 4.0

    EXPECT_TRUE(compare_by_result(a, b));   // a > b
    EXPECT_FALSE(compare_by_result(b, a));
}

TEST(SortTest, CompareByMedian)
{
    Students a, b;
    a.add_grade(10); a.set_exam(10); // median = 10
    b.add_grade(2);  b.set_exam(2);  // median = 2

    EXPECT_TRUE(compare_by_median(a, b));   // a > b
    EXPECT_FALSE(compare_by_median(b, a));
}

// operator<< 
TEST(StudentTest, OutputOperator)
{
    Students s;
    s.set_first_name("Jonas");
    s.set_last_name("Jonaitis");
    s.add_grade(8);
    s.set_exam(9);

    std::ostringstream oss;
    oss << s;

    std::string output = oss.str();
    EXPECT_TRUE(output.find("Jonas") != std::string::npos);
    EXPECT_TRUE(output.find("Jonaitis") != std::string::npos);
}

// operator>> 
TEST(StudentTest, InputOperator)
{
    std::istringstream iss("Jonas Jonaitis 7 8 9 10");
    Students s;
    iss >> s;

    EXPECT_EQ(s.first_name(), "Jonas");
    EXPECT_EQ(s.last_name(), "Jonaitis");
    EXPECT_EQ(s.exam(), 10); // last number is exam
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}