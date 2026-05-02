#include "student.hpp"
#include "student.hpp"
#include <gtest/gtest.h>
#include "Vector/vector.hpp"
#include <list>

/** Vienetiniai testai Students klasei. Kiekvienas testas tikrina viena elgsena. */


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
    s.set_exam(6);   // sorted: {4, 6, 8}  median = 6

    EXPECT_DOUBLE_EQ(s.median(), 6.0);
}

/// calc_median odd count 
TEST(StudentTest, CalcMedianOddCount)
{
    Students s;
    s.add_grade(2);
    s.add_grade(4);
    s.add_grade(6);  // grades + exam = {2, 4, 6, 8}
    s.set_exam(8);   // sorted: {2, 4, 6, 8}  even (4+6)/2 = 5.0

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

TEST(myVector, Constructor)
{
    my::vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.data(), nullptr);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(myVector, Destructor)
{
    { my::vector<int> v = {1, 2, 3}; }
    SUCCEED(); 
}

TEST(myVector, initializerListConstructor)
{
    my::vector<int> v = { 1, 2, 3};
    EXPECT_EQ(v.size(), 3);
    EXPECT_NE(v.data(), nullptr);
    EXPECT_EQ(v.capacity(), 3);
}

TEST(myVector, rangeConstructor)
{
    std::list<int> l = {1, 2, 3};
    my::vector<int> v(l.begin(), l.end());
    EXPECT_EQ(v.size(), l.size());
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(myVector, copyConstructor)
{
    my::vector<int> v1 = {1, 2, 3};
    my::vector<int> v2 = v1;
    EXPECT_EQ(v1.size(), v2.size());
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
}

TEST(myVector, copyAssignment)
{
    my::vector<int> v1 = {1, 2, 3};
    my::vector<int> v2;
    v2 = v1;
    EXPECT_EQ(v1.size(), v2.size());
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
}

TEST(myVector, moveConstructor)
{
    my::vector<int> v1 = {1, 2, 3};
    my::vector<int> v2(std::move(v1));

    EXPECT_EQ(3, v2.size());
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);

    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.data(), nullptr);
}

TEST(myVector, moveAssignment)
{
    my::vector<int> v1 = {1, 2, 3};
    my::vector<int> v2;
    v2 = (std::move(v1));

    EXPECT_EQ(3, v2.size());
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);

    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.data(), nullptr);
}


TEST(myVector, AssignFill)
{
    my::vector<int> v;
    v.assign(3, 1);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[2], 1);
    EXPECT_EQ(v[3], 1);
}

TEST(myVector, AssignRange)
{
    std::list<int> l = {1, 2, 3};
    my::vector<int> v;
    v.assign(l.begin(), l.end());
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(myVector, AssignInitializerList)
{
    my::vector<int> v;
    v.assign({1, 2, 3});
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(myVector, at)
{
    my::vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.at(2), 3);
}

TEST(myVector, indexOperator) //operator[]
{
    my::vector<int> v = {1, 2, 3};
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(myVector, front)
{
    my::vector<int> v1 = {1, 2, 3};
    EXPECT_EQ(v1.front(), 1);
    
    const my::vector<int> v2 = {1, 2, 3};
    EXPECT_EQ(v2.front(), 1);
    
}

TEST(myVector, back)
{
    my::vector<int> v1 = {1, 2, 3};
    EXPECT_EQ(v1.back(), 3);
    
    const my::vector<int> v2 = {1, 2, 3};
    EXPECT_EQ(v2.back(), 3);
}

TEST(myVector, data)
{
    my::vector<int> v1 = {1, 2, 3};
    EXPECT_EQ(*v1.data(), 1);
    
    const my::vector<int> v2 = {1, 2, 3};
    EXPECT_EQ(*v2.data(), 1);
}

TEST(myVector, begin)
{
    my::vector<int> v1 = {1, 2, 3};
    EXPECT_EQ(*v1.begin(), 1);
}

TEST(myVector, cbegin)
{
    const my::vector<int> v2 = {1, 2, 3};
    EXPECT_EQ(*v2.cbegin(), 1);
}

TEST(myVector, end)
{
    my::vector<int> v1 = {1, 2, 3};
    EXPECT_EQ(v1.end() - v1.begin(), 3);
}

TEST(myVector, cend)
{
    const my::vector<int> v1 = {1, 2, 3};
    EXPECT_EQ(v1.cend() - v1.cbegin(), 3);
}

TEST(myVector, rbegin)
{
    my::vector<int> v1 = {1, 2, 3};
    EXPECT_EQ(*v1.rbegin(), 3);
}

TEST(myVector, crbegin)
{
    const my::vector<int> v1 = {1, 2, 3};
    EXPECT_EQ(*v1.crbegin(), 3);
}

TEST(myVector, rend)
{
    my::vector<int> v1 = {1, 2, 3};
    EXPECT_EQ(v1.rend() - v1.rbegin(), 3);
}

TEST(myVector, crend)
{
    my::vector<int> v1 = {1, 2, 3};
    EXPECT_EQ(v1.crend() - v1.rbegin(), 3);
}

TEST(myVector, empty)
{
    my::vector<int> v;
    EXPECT_TRUE(v.empty());

    v.push_back(1);
    EXPECT_FALSE(v.empty());
}

TEST(myVector, size)
{
    my::vector<int> v = { 1, 2, 3};
    EXPECT_EQ(v.size(), 3);
}

TEST(myVector, max_size)
{
    my::vector<int> v;
    EXPECT_EQ(v.max_size(), INT_MAX/sizeof(int));
}

TEST(myVector, reserve)
{
    my::vector<int> v = {1, 2, 3};
    v.reserve(10);
    
    EXPECT_EQ(v.capacity(), 10);
    EXPECT_EQ(v.size(), 3);        
    EXPECT_EQ(v[0], 1);            
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    
    v.reserve(5);                  // mazesnis nei dabar, turetu tsg returnint
    EXPECT_EQ(v.capacity(), 10); 
}

TEST(myVector, capacity)
{
    my::vector<int> v;
    v.reserve(10);
    EXPECT_EQ(v.capacity(), 10);
}

TEST(myVector, shrink_to_fit)
{
    my::vector<int> v = {1, 2, 3};
    v.reserve(10);
    EXPECT_EQ(v.capacity(), 10);
    v.shrink_to_fit();
    EXPECT_EQ(v.size(), v.capacity());
}

TEST(myVector, clear)
{
    my::vector<int> v = {1, 2, 3};
    v.clear();
    EXPECT_EQ(v.size(), 0);
}

TEST(myVector, insert)
{
    my::vector<int> v = {1, 3};
    auto pos = std::next(v.begin());
    v.insert(pos, 2);

    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.at(2), 3);
    EXPECT_EQ(v.size(), 3);
}

TEST(myVector, emplace)
{

}

TEST(myVector, emplace_back)
{

}

TEST(myVector, erase)
{
    my::vector<int> v = {1, 2, 3};
    auto pos = std::next(v.begin());
    v.erase(pos);

    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 3);
    EXPECT_EQ(v.size(), 2);
}

TEST(myVector, pop_back)
{
    my::vector<int> v = {1, 2, 3};
    v.pop_back();

    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 2);
    EXPECT_EQ(v.size(), 2);
}

TEST(myVector, resize)
{
    my::vector<int> v;
    v.resize(10);
    EXPECT_EQ(v.size(), 10);
}

TEST(myVector, swap)
{
    my::vector<int> v1 = {1, 2, 3};
    my::vector<int> v2 = {3, 2};

    v1.swap(v2);
    EXPECT_EQ(v1.size(), 2);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v1.at(0), 3);
    EXPECT_EQ(v1.at(1), 2);
    EXPECT_EQ(v2.at(0), 1);
    EXPECT_EQ(v2.at(1), 2);
    EXPECT_EQ(v2.at(2), 3);
}

TEST(myVector, equalOperator)
{
    my::vector<int> v1 = {1, 2, 3};
    my::vector<int> v2 = {1, 2, 3};

    EXPECT_TRUE(v1 == v2);
}

TEST(myVector, notEqualOperator)
{
    my::vector<int> v1 = {1, 2, 3};
    my::vector<int> v2 = {1, 2, 4};

    EXPECT_TRUE(v1 != v2);
}

TEST(myVector, lessThanOperator) // operator<
{

}

TEST(myVector, lessThanOrEqualOperator) // operator <=
{

}

TEST(myVector, moreThanOperator) //operator>
{

}

TEST(myVector, moreThanOrEqualOperator) //operator>=
{

}

TEST(myVector, lessThanOrEqualOperator)
{

}

TEST(myVector, pushBackCopy)
{
    int x = 3;
    my::vector<int> v;
    v.push_back(x);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.at(0), x);
}

TEST(myVector, pushBackMove)
{
    string s = "hello";
    my::vector<string> v;
    v.push_back(std::move(s));
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.at(0), "hello");
    EXPECT_EQ(s, s.empty());
}

TEST(myVector, lessThanOrEqualOperator)
{

}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}