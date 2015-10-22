#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>


class Solution
{
public:
    int reverse(int x)
    {
        bool isNegative = (x < 0);
        int num = x;
        long long ret = 0;

        while (num)
        {
            int digit = num % 10;
            num /= 10;

            ret *= 10;
            ret += digit;

            // 负溢出
            if (isNegative && ret < INT_MIN)
                return 0;

            // 正溢出
            if (!isNegative && ret > INT_MAX)
                return 0;
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG


static void doTest(int num, int expected)
{
    Solution solution;
    int ret = solution.reverse(num);
    if (ret != expected)
        std::printf("num: %-7d ret: %-7d expected: %-7d\n", num, ret, expected);
}


int main()
{
    doTest(123, 321);
    doTest(-123, -321);
    doTest(10000, 1);
    doTest(INT_MAX, 0);
    doTest(INT_MIN, 0);
    return 0;
}

#endif
