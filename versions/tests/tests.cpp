#include <gtest/gtest.h>
#include "main.cpp"

TEST(Random_function, Random_grade_check)
{
    vector<duom> test_vector;

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
TEST(Random_function, Handles_zero_students)
{
    vector<duom> test_vector;

    // Generate random names and grades for 0 students
    random_names_grades(test_vector, 0, 5);

    // Check that the vector is empty
    EXPECT_EQ(test_vector.size(), 0);
}
TEST(Random_function, Handles_zero_grades)
{
    vector<duom> test_vector;

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
/*
TEST(Five_rule_test, Handles_data_correctly)
{
    vector<duom> test_vector;

    read_file(test_vector, test_file_location + "kursiokai_1000" + ".dat");
    //
    duom test_case = test_vector.at(0);
    //
    duom copy_constr = test_case;
    EXPECT_EQ(copy_constr==test_case, true);
    //
    duom copy_method;
    copy_method=test_case;
    EXPECT_EQ(copy_method==test_case, true);
    //
    duom move_constr = std::move(test_case);
    //EXPECT_EQ(move_constr==test_case && move_constr==test_vector.at(0), false);
    //
    test_case = test_vector.at(0);
    duom move_method;
    move_method=std::move(test_case);
    EXPECT_EQ(move_method==test_case && move_method==test_vector.at(0), true);
}
*/
int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}