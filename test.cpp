#include "main.h"
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace std;
using namespace lft;

int main()
{
    assertm(2 + 2 == 4, "TEST0 failed");
    cout << "Test 0 passed" << endl;

    assertm(LongFloat(0) == LongFloat(0.0), "TEST1 failed");
    cout << "Test 1 passed" << endl;    
    assertm(LongFloat(234.546) - LongFloat(234.546) == LongFloat(0), "TEST2 failed");
    cout << "Test 2 passed" << endl;
    assertm(LongFloat(234.546) - LongFloat(-234.546) == LongFloat(469.092), "TEST3 failed");
    cout << "Test 3 passed" << endl;
    assertm(LongFloat("234.546") == LongFloat(234.546), "TEST4 failed");
    cout << "Test 4 passed" << endl;
    assertm(LongFloat("234.546") * LongFloat(0.785) == LongFloat("184.11861"), "TEST5 failed");
    cout << "Test 5 passed" << endl;
    assertm(longDivision(LongFloat("234.546"), LongFloat("-0.785"), 4) == LongFloat("-298.7847"), "TEST6 failed");
    cout << "Test 6 passed" << endl;
    assertm(LongFloat("0") == LongFloat("-0"), "TEST7 failed");
    cout << "Test 7 passed" << endl;
    assertm(LongFloat("-1") < LongFloat("1"), "TEST8 failed");
    cout << "Test 8 passed" << endl;
    assertm(LongFloat("0") <= LongFloat("-0"), "TEST9 failed");
    cout << "Test 9 passed" << endl;
    assertm(LongFloat("1") >= LongFloat("0.5"), "TEST10 failed");
    cout << "Test 10 passed" << endl;
    assertm(LongFloat("1") > LongFloat("-2"), "TEST11 failed");
    cout << "Test 11 passed" << endl;
    assertm(LongFloat("-1") != LongFloat("1"), "TEST12 failed");
    cout << "Test 12 passed" << endl;
}
