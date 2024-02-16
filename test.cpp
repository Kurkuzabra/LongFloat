#include <gtest/gtest.h>
#include <main.h>

using namespace std;
using namespace lft;

TEST(module_name, test_name)
{
        EXPECT_TRUE(2 + 2 == 4);
        EXPECT_TRUE(LongFloat(0) == LongFloat(0.0));
        EXPECT_TRUE(LongFloat(234.546) - LongFloat(234.546) == LongFloat(0));
        EXPECT_TRUE(LongFloat(234.546) - LongFloat(-234.546) == LongFloat(469.092));
        EXPECT_TRUE(LongFloat("234.546") == LongFloat(234.546));
        EXPECT_TRUE(LongFloat("234.546") * LongFloat(0.785) == LongFloat("184.11861"));
        EXPECT_TRUE(longDivision(LongFloat("234.546"), LongFloat("-0.785"), 4) == LongFloat("-298.7847"));
        EXPECT_TRUE(LongFloat("0") == LongFloat("-0"));
        EXPECT_TRUE(LongFloat("-1") < LongFloat("1"));
        EXPECT_TRUE(LongFloat("0") <= LongFloat("-0"));
        EXPECT_TRUE(LongFloat("1") >= LongFloat("0.5"));
        EXPECT_TRUE(LongFloat("1") > LongFloat("-2"));
}

int main(int argc, char** argv)
{
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
