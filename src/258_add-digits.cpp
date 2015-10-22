#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>


class Solution
{
public:
    int addDigits(int num)
    {
        // 详见 https://en.wikipedia.org/wiki/Digital_root

        if (num == 0)
            return 0;

        if (num % 9 == 0)
            return 9;

        return num % 9;
    }
};



#ifdef LEETCODE_DEBUG

static bool doTest(Solution &solution, int num)
{
    int result = num;
    while (result > 9)
    {
        int numSum = 0;
        while (result)
        {
            numSum += result % 10;
            result /= 10;
        }

        result = numSum;
    }

    int ret = solution.addDigits(num);
    return ret == result;
}


int main()
{
    std::random_device rd;
    std::mt19937 funcRandomNum(rd());
    Solution solution;

    for (int i = 0; i < 100000; ++i)
    {
        int num = funcRandomNum();
        num = std::abs(num);

        bool succeed = doTest(solution, num);
        if (!succeed)
        {
            std::printf("Test failed: %d\n", num);
            break;
        }
    }
}

#endif
