#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <ctime>
#include <sstream>
#include <stdexcept>

namespace lft
{
    enum class CmpSign {More, Less, Eq};

    class LongFloat
    {
        public:
        
        LongFloat();
        explicit LongFloat(int);
        explicit LongFloat(double);
        LongFloat(std::string);

        std::vector<short> integers;
        std::vector<short> pointers;
        short sign;
        
        void set_precision(int);
        void mult_by_base();
        void div_by_base();
        friend LongFloat longDivision(const LongFloat&, const LongFloat&, int);
        
        bool is_zero() const;
        
        operator std::string() {return this->to_string();}
        operator int() {return this->to_int();}
        
        friend std::istream& operator>>(std::istream&, LongFloat&);
        
        friend LongFloat operator+(const LongFloat&, const LongFloat&);
        friend LongFloat operator-(const LongFloat&, const LongFloat&);
        friend LongFloat operator*(const LongFloat&, const LongFloat&);
        friend LongFloat operator/(const LongFloat&, const LongFloat&);
        
        friend bool operator>(const LongFloat&, const LongFloat&);
        friend bool operator>=(const LongFloat&, const LongFloat&);
        friend bool operator<(const LongFloat&, const LongFloat&);
        friend bool operator<=(const LongFloat&, const LongFloat&);
        friend bool operator==(const LongFloat&, const LongFloat&);
        friend bool operator!=(const LongFloat&, const LongFloat&);

        private:

        std::string to_string() const;
        int to_int() const;

        void write_sub(const LongFloat&, const LongFloat&);
        void write_add(const LongFloat&, const LongFloat&);
        
        CmpSign compare_abs(const LongFloat&, const LongFloat&);
        CmpSign compare(const LongFloat&, const LongFloat&);

        void simplify_end(std::vector<short>&);
        void simplify_beg(std::vector<short>&);
        
    };
}