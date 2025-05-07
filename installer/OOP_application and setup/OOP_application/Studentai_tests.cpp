#include "template.h"
#include <gtest/gtest.h>

class StudentaiTest : public ::testing::Test {
protected:
    void SetUp() override {
        testNd = {8, 9, 7, 10, 6};
    }
    Vector<int> testNd;

    duom createSampleStudent() {
        temp input;
        input.pazymiai = testNd;
        duom test(input);
        return test;
    }
};
TEST_F(StudentaiTest, Random_grade_check)
{
    Vector<duom> test_vector;

    // Generate random names and grades for 10 students, each with 5 grades
    random_names_grades(test_vector, 10, 5);

    // Check that the vector contains 10 students
    EXPECT_EQ(test_vector.size(), 10);

    for (auto& student : test_vector)
    {
        // Check that each student has 5 grades
        EXPECT_EQ(student.getPazymiai().size(), 5);

        for (auto& mark : student.getPazymiai())
        {
            // Check that each grade is between 1 and 10
            EXPECT_GE(mark, 1);
            EXPECT_LE(mark, 10);
        }
    }
}
TEST_F(StudentaiTest, Handles_zero_students)
{
    Vector<duom> test_vector;

    // Generate random names and grades for 0 students
    random_names_grades(test_vector, 0, 5);

    // Check that the vector is empty
    EXPECT_EQ(test_vector.size(), 0);
}
TEST_F(StudentaiTest, Handles_zero_grades)
{
    Vector<duom> test_vector;

    // Generate random names and grades for 10 students, each with 0 grades
    random_names_grades(test_vector, 10, 0);

    // Check that the vector contains 10 students
    EXPECT_EQ(test_vector.size(), 10);

    for (auto& student : test_vector)
    {
        // Check that each student has 0 grades
        EXPECT_EQ(student.getPazymiai().size(), 0);
    }
}
TEST_F(StudentaiTest, Handles_data_correctly)
{
    Vector<duom> test_vector;
    bool rule;

    read_file(test_vector, test_file_location + "kursiokai_1000" + ".dat");
    //
    duom test_case = test_vector.at(0);
    //
    duom copy_constr = test_case;
    if(copy_constr==test_case)
        rule=true;
    else
        rule=false;
    EXPECT_EQ(rule, true);
    //
    duom copy_method;
    copy_method=test_case;
    if(copy_method==test_case)
        rule=true;
    else
        rule=false;
    EXPECT_EQ(rule, true);
    //
    duom move_constr = std::move(test_case);
    if(move_constr==test_case && move_constr==test_vector.at(0))
        rule=false;
    else
        rule=true;
    EXPECT_EQ(rule, true);
    //
    test_case = test_vector.at(0);
    duom move_method;
    move_method=std::move(test_case);
    if(move_method==test_case && move_method==test_vector.at(0))
        rule=false;
    else
        rule=true;
    EXPECT_EQ(rule, true);
}