#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>


class Solution
{
public:
    int myAtoi(std::string str)
    {
        long long ret = 0;
        bool isNegative = false;
        std::string::size_type idx = 0;
        std::string::size_type strLen = str.size();


        // 跳过多余的空格
        while (idx < strLen && std::isspace(str[idx]))
            ++idx;

        if (idx == strLen)
            return ret;


        // 正负号
        char ch = str[idx];
        if (ch == '+' || ch == '-')
        {
            ++idx;
            isNegative = (ch == '-');
        }


        // 数字部分
        while (idx < strLen)
        {
            char ch = str[idx];
            int digit = ch - '0';
            if (digit < 0 || digit > 10)
                break;

            ret *= 10;
            ret += digit;

            if (!isNegative && ret > INT_MAX)
                return INT_MAX;

            if (isNegative && ret > std::abs((long long) INT_MIN))
                return INT_MIN;

            ++idx;
        }


        return isNegative ? -ret : ret;
    }
};



#ifdef LEETCODE_DEBUG

static void assertAtoi(std::string str, int value)
{
    Solution solution;
    int ret = solution.myAtoi(str);
    if (ret != value)
        std::printf("Wrong Answer: %s (%d) -> %d\n", str.c_str(), value, ret);
}

int main()
{
    assertAtoi("", 0);
    assertAtoi("  ", 0);
    assertAtoi("123456", 123456);
    assertAtoi("   1234   ", 1234);
    assertAtoi(" +1234", 1234);
    assertAtoi(" -1234", -1234);
    assertAtoi(" - 1 2 3 4 ", 0);
    assertAtoi(" 1111111111111111111111 ", INT_MAX);
    assertAtoi(" -1111111111111111111111 ", INT_MIN);
    return 0;
}

#endif
