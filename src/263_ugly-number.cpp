#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <memory>


static bool isDivisibleBy(int num, int mod)
{
    if (num < mod)
        return false;

    int modCount = num / mod;
    return (num - modCount * mod == 0);
}


class Solution
{
public:
    bool isUgly(int num)
    {
        if (num <= 0)
            return false;

        while (num != 1)
        {
            if (isDivisibleBy(num, 2))
            {
                num /= 2;
                continue;
            }

            if (isDivisibleBy(num, 3))
            {
                num /= 3;
                continue;
            }

            if (isDivisibleBy(num, 5))
            {
                num /= 5;
                continue;
            }

            // 至少有一个不是 2 / 3 / 5 的素数
            return false;
        }

        return true;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(Solution &solution, int num, bool expected)
{
    bool ret = solution.isUgly(num);
    if (ret != expected)
        std::printf("num: %-10d expected: %d\n", num, expected);
}

int main()
{
    Solution solution;
    doTest(solution, -1, false);
    doTest(solution, 0, false);
    doTest(solution, 1, true);
    doTest(solution, 6, true);
    doTest(solution, 8, true);
    doTest(solution, 14, false);
    return 0;
}

#endif
