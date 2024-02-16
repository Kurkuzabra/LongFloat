#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <ctime>
#include <sstream>

namespace lft
{
    enum class CmpSign {More, Less, Eq};

    class LongFloat
    {
        public:
        
        LongFloat();
        explicit LongFloat(int);
        LongFloat(double);
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

    void LongFloat::simplify_end(std::vector<short>& vec)
    {
        while (vec.size() > 0 && vec[vec.size() - 1] == 0)
        {
            vec.pop_back();
        }
    }

    void LongFloat::simplify_beg(std::vector<short>& vec)
    {
        std::reverse(vec.begin(), vec.end());
        simplify_end(vec);
        std::reverse(vec.begin(), vec.end());
    }

    LongFloat::LongFloat()
    {
        sign = 1;
        pointers.resize(0);
        integers.resize(0);
    }

    LongFloat::LongFloat(std::string str_num)
    {
        sign = 1;
        pointers.resize(0);
        integers.resize(0);
        
        int i = 0;
        if (str_num.length() > 0 && str_num[0] == '-')
        {
            sign = -1;
            i++;
        }
        for (; i < str_num.length() && str_num[i] != '.'; i++)
        {
            integers.push_back(str_num[i] - '0');
        }
        i++;
        for (; i < str_num.length(); i++)
        {
            pointers.push_back(str_num[i] - '0');
        }
    }

    LongFloat::LongFloat(int num) : LongFloat(static_cast<double>(num)) {}

    LongFloat::LongFloat(double num)
    {
        sign = 1;
        pointers.resize(0);
        integers.resize(0);
        
        std::stringstream str_stream;
        std::string str_num;
        str_stream << num;
        str_stream >> str_num;
        
        int i = 0;
        if (num < 0)
        {
            sign = -1;
            i++;
        }
        for (; i < str_num.length() && str_num[i] != '.'; i++)
        {
            integers.push_back(str_num[i] - '0');
        }
        i++;
        for (; i < str_num.length(); i++)
        {
            pointers.push_back(str_num[i] - '0');
        }
    }

    void LongFloat::set_precision(int prec)
    {
        if (this->pointers.size() > prec)
        {
            this->pointers.resize(prec);
        }
    }

    void LongFloat::mult_by_base()
    {
        if (this->is_zero())
        {
            return;
        }
        if (this->pointers.size() == 0)
        {
            this->integers.push_back(0);
        }
        else
        {
            this->integers.push_back(pointers[0]);
            this->pointers.erase(this->pointers.begin());
        }
    }

    void LongFloat::div_by_base()
    {
        if (this->is_zero())
        {
            return;
        }
        if (this->integers.size() == 0)
        {
            this->pointers.insert(this->pointers.begin(), 0);
        }
        else
        {
            this->pointers.insert(this->pointers.begin(), this->integers[this->integers.size() - 1]);
            this->integers.pop_back();
        }
    }

    bool LongFloat::is_zero() const
    {
        for (int i = 0; i < this->integers.size(); i++)
        {
            if (this->integers[i] != 0)
            {
                return false;
            }
        }
        for (int i = 0; i < this->pointers.size(); i++)
        {
            if (this->pointers[i] != 0)
            {
                return false;
            }
        }
        return true;
    }

    std::string LongFloat::to_string() const
    {
        if (this->is_zero())
        {
            return "0";
        }
        std::string str;
        if (this->sign == -1)
        {
            std::cout<<"ho";
            str.push_back('-');
        }
        for (int i = 0; i < this->integers.size(); i++)
        {
            str.push_back((char)this->integers[i] + '0');
        }
        if (this->pointers.size() > 0)
        {
            str.push_back('.');
            for (int i = 0; i < this->pointers.size(); i++)
            {
                str.push_back((char)this->pointers[i] + '0');
            }
        }
        return str;
    }

    int LongFloat::to_int() const
    {
        int num = 0;
        for (auto el : this->integers)
        {
            num *= 10;
            num += el;
        }
        return num;
    }

    CmpSign compare_abs(const LongFloat& left, const LongFloat& right)
    {
        int lis = left.integers.size();
        int ris = right.integers.size();
        int lps = left.pointers.size();
        int rps = right.pointers.size();
        
        if (lis > ris)
        {
            return CmpSign::More;
        }
        if (lis < ris)
        {
            return CmpSign::Less;
        }
        for (int i = 0; i < lis; i++)
        {
            if (left.integers[i] > right.integers[i])
            {
                return CmpSign::More;
            }
            if (left.integers[i] < right.integers[i])
            {
                return CmpSign::Less;
            }
        }
        for (int i = 0; i < std::max(lps, rps); i++)
        {
            short left_ptr = i < lps ? left.pointers[i] : 0;
            short right_ptr = i < rps ? right.pointers[i] : 0;
            if (left_ptr > right_ptr)
            {
                return CmpSign::More;
            }
            if (left_ptr < right_ptr)
            {
                return CmpSign::Less;
            }
        }
        return CmpSign::Eq;
    }

    CmpSign compare(const LongFloat& left, const LongFloat& right)
    {
        if(left.is_zero() && right.is_zero())
        {
            return CmpSign::Eq;
        }
        if (left.sign > right.sign)
        {
            return CmpSign::More;
        }
        if (left.sign < right.sign)
        {
            return CmpSign::Less;
        }
        if (left.sign == 1)
        {
            return compare_abs(left, right); 
        }

        CmpSign sgn = compare_abs(left, right);
        if (sgn == CmpSign::More)
        {
            return CmpSign::Less;
        }
        if (sgn == CmpSign::Less)
        {
            return CmpSign::More;
        }
        return CmpSign::Eq;
    }

    std::istream& operator>>(std::istream& is, LongFloat& obj)
    {
        char symbol = 0;
        obj.sign = 1;
        obj.integers.resize(0);
        is.get(symbol);
        if (symbol == '-')
        {
            obj.sign = -1;
        }
        while (symbol != ' ' && symbol != '\n')
        {
            if (symbol == '.')
            {
                break;
            }
            else if (symbol >= '0' && symbol <= '9')
            {
                obj.integers.push_back((short)(symbol - '0'));
            }
            is.get(symbol);
        }
        while (symbol != ' ' && symbol != '\n')
        {
            if (symbol >= '0' && symbol <= '9')
            {
                obj.pointers.push_back((short)(symbol - '0'));
            }
            is.get(symbol);
        }
        simplify_end(obj.pointers);
        simplify_beg(obj.integers);
        return is;
    }

    LongFloat operator+(const LongFloat& left, const LongFloat& right)
    {
        LongFloat res = LongFloat();
        if (left.sign == right.sign)
        {
            res.write_add(left, right);
            res.sign = left.sign;
        }
        else if (compare_abs(left, right) == CmpSign::More)
        {
            res.write_sub(left, right);
            res.sign = left.sign;
        }
        else
        {
            res.write_sub(right, left);
            res.sign = right.sign;
        }
        return res;
    }

    LongFloat operator-(const LongFloat& left, const LongFloat& right)
    {
        LongFloat res = LongFloat();
        if (left.sign != right.sign)
        {
            res.write_add(left, right);
            res.sign = left.sign;
        }
        else if (compare_abs(left, right) == CmpSign::More)
        {
            res.write_sub(left, right);
            res.sign = left.sign;
        }
        else
        {
            res.write_sub(right, left);
            res.sign = right.sign;
        }
        return res;
    }

    LongFloat operator*(const LongFloat& left, const LongFloat& right) {
        int l_size = left.integers.size() + left.pointers.size();
        int r_size = right.integers.size() + right.pointers.size();
        int lis = left.integers.size();
        int ris = right.integers.size();
        
        LongFloat ans = LongFloat();
        
        if (left.is_zero() || right.is_zero())
        {
            return ans;
        }
        
        std::vector<short> res(l_size + r_size);
        
        for (int i = 0; i < l_size; i++) {
            for (int j = 0; j < r_size; j++) {
                res[i + j + 1] += (i < lis ? left.integers[i] : left.pointers[i - lis])
                    * (j < ris ? right.integers[j] : right.pointers[j - ris]);
            }
        }

        for (int i = res.size() - 1; i > 0; i--) {
            res[i - 1] += res[i] / 10;
            res[i] %= 10;
        }
        
        ans.integers = std::vector<short>(res.begin(), res.end() - left.pointers.size() - 
            right.pointers.size());
        ans.pointers = std::vector<short>(res.end() - left.pointers.size() - 
            right.pointers.size(), res.end());
        
        simplify_end(ans.pointers);
        simplify_beg(ans.integers);
        ans.sign = left.sign * right.sign;
        
        return ans;
    }

    LongFloat operator/(const LongFloat& left, const LongFloat& right)
    {
        return longDivision(left, right, 16);
    }

    void LongFloat::write_add(const LongFloat& left, const LongFloat& right)
    {
        this->sign = left.sign;
        this->integers.resize(0);
        short prev_num = 0;
        
        int lps = left.pointers.size();
        int rps = right.pointers.size();
        for (int i = std::max(lps, rps) - 1; i >= 0; i--)
        {
            short num = prev_num;
            num += i < lps ? left.pointers[i] : 0;
            num += i < rps ? right.pointers[i] : 0;
            this->pointers.push_back(num % 10);
            prev_num = num / 10;
        }
        
        int lis = left.integers.size();
        int ris = right.integers.size();
        if (lis >= ris)
        {
            for (int i = lis - 1 ; i >= 0; i--)
            {
                short num = prev_num;
                num += left.integers[i];
                num += i >= lis - ris ? right.integers[i - lis + ris] : 0;
                this->integers.push_back(num % 10);
                prev_num = num / 10;
            }
        }
        else
        {
            for (int i = ris - 1 ; i >= 0; i--)
            {
                short num = prev_num;
                num += right.integers[i];
                num += i >= ris - lis ? left.integers[i - ris + lis] : 0;
                this->integers.push_back(num % 10);
                prev_num = num / 10;
            }
        }
        if (prev_num > 0)
        {
            this->integers.push_back(prev_num);
        }
        simplify_end(this->integers);
        std::reverse(this->integers.begin(), this->integers.end());
        std::reverse(this->pointers.begin(), this->pointers.end());
        simplify_end(this->pointers);
    }


    void LongFloat::write_sub(const LongFloat& left, const LongFloat& right)
    {
        this->sign = left.sign;
        this->integers.resize(0);
        int lis = left.integers.size();
        int ris = right.integers.size();
        int lps = left.pointers.size();
        int rps = right.pointers.size();
        
        int non_zero_idx = 2147483647;
        for (int i = std::max(lps, rps) - 1; i >= 0; i--)
        {
            short lpnum = i < lps ? left.pointers[i] : 0;
            short rpnum = i < rps ? right.pointers[i] : 0;
            this->pointers.push_back(lpnum - rpnum);
        }
        
        for (int i = std::max(lis, ris) - 1; i >= 0; i--)
        {
            short linum = left.integers[i];
            short rinum = i >= lis - ris ? right.integers[i - lis + ris] : 0;
            this->integers.push_back(linum - rinum);
        }
        if (this->pointers.size() != 0)
        {
            for (int i = 0; i < this->pointers.size() - 1; i++)
            {
                if (this->pointers[i] < 0)
                {
                    this->pointers[i] += 10;
                    this->pointers[i + 1]--;
                }
            }
            if (this->pointers[this->pointers.size() - 1] < 0)
            {
                this->pointers[this->pointers.size() - 1] += 10;
                this->integers[0]--;
            }
        }

        if (this->integers.size() != 0)
        {
            for (int i = 0; i < this->integers.size() - 1; i++)
            {
                if (this->integers[i] < 0)
                {
                    this->integers[i] += 10;
                    this->integers[i + 1]--;
                }
            }
        }
        simplify_end(this->integers);
        std::reverse(this->integers.begin(), this->integers.end());
        std::reverse(this->pointers.begin(), this->pointers.end());
        simplify_end(this->pointers);
    }

    bool operator>(const LongFloat& left, const LongFloat& right)
    {
        CmpSign cmp = compare(left, right);
        return cmp == CmpSign::More;
    }

    bool operator<(const LongFloat& left, const LongFloat& right)
    {
        CmpSign cmp = compare(left, right);
        return cmp == CmpSign::Less;
    }

    bool operator==(const LongFloat& left, const LongFloat& right)
    {
        CmpSign cmp = compare(left, right);
        return cmp == CmpSign::Eq;
    }

    bool operator!=(const LongFloat& left, const LongFloat& right)
    {
        CmpSign cmp = compare(left, right);
        return cmp != CmpSign::Eq;
    }

    bool operator>=(const LongFloat& left, const LongFloat& right)
    {
        CmpSign cmp = compare(left, right);
        return cmp != CmpSign::Less;
    }

    bool operator<=(const LongFloat& left, const LongFloat& right)
    {
        CmpSign cmp = compare(left, right);
        return cmp != CmpSign::More;
    }

    LongFloat longDivision(const LongFloat& left, const LongFloat& right, int precision = 0)
    {
        LongFloat _left = left;
        _left.sign = 1;
        LongFloat _right = right;
        _right.sign = 1;
        LongFloat res = LongFloat();
        int k = 0;
        while (_left >= _right)
        {
            _right.mult_by_base();
            k++;
        }
        
        while (k > -1 * precision)
        {
            if (left.is_zero())
            {
                return res;
            }
            _right.div_by_base();
            k--;
            if (k >= 0)
            {
                res.integers.push_back(0);
            }
            else
            {
                res.pointers.push_back(0);
            }
            
            while(_left >= _right)
            {
                _left = _left - _right;
                if (k >= 0)
                {
                    res.integers[res.integers.size() - 1]++;
                }
                else
                {
                    res.pointers[res.pointers.size() - 1]++;
                }
            }
        }
        res.sign = left.sign * right.sign;
        return res;
    }

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
        std::cout << "needed " << (float)time_req / CLOCKS_PER_SEC << "seconds to calc pi" << std::endl;
        
        return pi;
    }
}
