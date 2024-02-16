#include <gtest/gtest.h>
#include "main.h"

using namespace std;
using namespace lft;

TEST(module0, test0)
{
        EXPECT_TRUE(2 + 2 == 4);
}
TEST(module1, test1)
{
        EXPECT_TRUE(LongFloat(0) == LongFloat(0.0));
}
TEST(module1, test2)
{
        EXPECT_TRUE(LongFloat(234.546) - LongFloat(234.546) == LongFloat(0));
}
TEST(module1, test3)
{
        EXPECT_TRUE(LongFloat(234.546) - LongFloat(-234.546) == LongFloat(469.092));
}

TEST(module2, test1)
{
        EXPECT_TRUE(LongFloat("234.546") * LongFloat(0.785) == LongFloat("184.11861"));
}
TEST(module2, test2)
{
        EXPECT_TRUE(longDivision(LongFloat("234.546"), LongFloat("-0.785"), 4) == LongFloat("-298.7847"));
}

TEST(module3, test1)
{
        EXPECT_TRUE(LongFloat("234.546") == LongFloat(234.546));
}
TEST(module3, test2)
{
       EXPECT_TRUE(LongFloat("0") == LongFloat("-0"));
}
TEST(module3, test3)
{
        EXPECT_TRUE(LongFloat("-1") < LongFloat("1"));
}
TEST(module3, test4)
{
        EXPECT_TRUE(LongFloat("1") >= LongFloat("0.5"));
}
TEST(module3, test5)
{
        EXPECT_TRUE(LongFloat("1") > LongFloat("-2"));
}
TEST(module3, test6)
{
        EXPECT_TRUE(LongFloat("0") <= LongFloat("-0"));
}

int main(int argc, char** argv)
{
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
