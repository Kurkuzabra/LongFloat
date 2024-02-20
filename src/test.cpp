#include <gtest/gtest.h>
#include "headers/longfloat.hpp"
#include "headers/lftfuncs.hpp"

using namespace std;
using namespace lft;

TEST(sum, test1)
{
        EXPECT_TRUE(LongFloat(0) + LongFloat(-0) == LongFloat(0.0));
}
TEST(sum, test2)
{
        EXPECT_TRUE(LongFloat(999.999) + LongFloat(0.001) == LongFloat(1000));
}
TEST(sum, test3)
{
        EXPECT_TRUE(LongFloat("324634574673568356857") + LongFloat("32462456443645765447") == LongFloat("357097031117214122304"));
}
TEST(sum, test4)
{
        EXPECT_TRUE(LongFloat("948368437875.8768") + LongFloat("-967899678999.9984") == LongFloat("-19531241124.1216"));
}
TEST(sum, test5)
{
        EXPECT_TRUE(LongFloat("948368437875.8768") + LongFloat("967899678999.9984") == LongFloat("1916268116875.8752"));
}

TEST(sub, test1)
{
        EXPECT_TRUE(LongFloat(0) - LongFloat(-0) == LongFloat(0.0));
}
TEST(sub, test2)
{
        EXPECT_TRUE(LongFloat(1000.0) - LongFloat(0.001) == LongFloat(999.999));
}
TEST(sub, test3)
{
        EXPECT_TRUE(LongFloat("53542545") - LongFloat("5365363") == LongFloat("48177182"));
}
TEST(sub, test4)
{
        EXPECT_TRUE(LongFloat("53542545.87565758") - LongFloat("9789745679.986875875") == LongFloat("-9736203134.111218295"));
}
TEST(sub, test5)
{
        EXPECT_TRUE(LongFloat("53542545.87565758") - LongFloat("-9789745679.986875875") == LongFloat("9843288225.862533455"));
}

TEST(mult, test1)
{
        EXPECT_TRUE(LongFloat(0) * LongFloat(-0) == LongFloat(0));
}
TEST(mult, test2)
{
        EXPECT_TRUE(LongFloat(1000.0) * LongFloat(0.001) == LongFloat(1));
}
TEST(mult, test3)
{
        EXPECT_TRUE(LongFloat("53542545") * LongFloat("5365363") == LongFloat("287275189868835"));
}
TEST(mult, test4)
{
        EXPECT_TRUE(LongFloat("-945223203.34645734") * LongFloat("45874945.1437177") == LongFloat("-43362062602087851.188931452052918"));
}
TEST(mult, test5)
{
        EXPECT_TRUE(LongFloat("0") * LongFloat("45874945.1437177") == LongFloat("-0"));
}

TEST(div, test1)
{
        EXPECT_TRUE(LongFloat(0) / LongFloat(9) == LongFloat(0));
}
TEST(div, test2)
{
    try {
        LongFloat ans = LongFloat(9) / LongFloat(0);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("received zero divisor"));
    }
}
TEST(div, test3)
{
        EXPECT_TRUE(longDivision(LongFloat("52452.676474"), LongFloat("42.54743457"), 20) == LongFloat("1232.80468033163485748560"));
}
TEST(div, test4)
{
        EXPECT_TRUE(longDivision(LongFloat("234.546"), LongFloat("-0.785"), 4) == LongFloat("-298.7847"));
}

TEST(comp, test1)
{
        EXPECT_TRUE(LongFloat("234.546") == LongFloat(234.546));
}
TEST(comp, test2)
{
       EXPECT_TRUE(LongFloat("0") == LongFloat("-0"));
}
TEST(comp, test3)
{
        EXPECT_TRUE(LongFloat("-1") < LongFloat("1"));
}
TEST(comp, test4)
{
        EXPECT_TRUE(LongFloat("1") >= LongFloat("0.5"));
}
TEST(comp, test5)
{
        EXPECT_TRUE(LongFloat("1") > LongFloat("-2"));
}
TEST(comp, test6)
{
        EXPECT_TRUE(LongFloat("0") <= LongFloat("-0"));
}

TEST(pi, test1)
{
        EXPECT_TRUE(approximate_pi(100) == LongFloat("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679")); 
}

int main(int argc, char** argv)
{
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
