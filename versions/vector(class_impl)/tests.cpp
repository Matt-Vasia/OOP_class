#include <gtest/gtest.h>
#include "template.cpp"

TEST(Compare, CompareFunctionTest)
{
    string name1 = "Jonas";
    string name2 = "Petras";

    EXPECT(compare(name1, name2, nullptr)).toBe(true);
}