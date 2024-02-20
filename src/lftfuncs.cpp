#include "headers/lftfuncs.hpp"

namespace lft
{
    LongFloat approximate_pi(int digits)
    {
        clock_t time_req = clock();
        
        LongFloat pi = LongFloat();
        LongFloat mult = LongFloat(1);
        LongFloat num_4 = LongFloat(4), num_1 = LongFloat(1), num_8 = LongFloat(8),
            num_2 = LongFloat(2), num_5 = LongFloat(5), num_6 = LongFloat(6);
        int precision = int(LongFloat(digits) * LongFloat(std::log(10) / std::log(16)));
        LongFloat divisor = LongFloat();
        for (int i = 0; i < precision; i++)
        {
            LongFloat cnt = longDivision(num_4, (divisor + num_1), digits + 5) -
                longDivision(num_2, (divisor + num_4), digits + 5) - 
                longDivision(num_1, (divisor + num_5), digits + 5) - 
                longDivision(num_1, (divisor + num_6), digits + 5);
            
            divisor = divisor + num_8;
            pi = pi + mult * cnt;
            pi.set_precision(digits + 5);
            mult = longDivision(mult, LongFloat(16), digits + 5);
        }
        pi.set_precision(digits);
        
        time_req = clock()- time_req;
        std::cout << "needed " << (float)time_req / CLOCKS_PER_SEC << " seconds to calc " << digits << " digits of pi" << std::endl;
        
        return pi;
    }
}