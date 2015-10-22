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
#include <unordered_set>


static const int kDigitSquares[] = { 0, 1, 4, 9, 16, 25, 36, 49, 64, 81 };

class Solution
{
public:
    bool isHappy(int n)
    {
        if (n <= 0)
            return false;

        int num = n;
        std::unordered_set<int> calculatedNums;
        while (true)
        {
            calculatedNums.insert(num);

            int digitSqureSum = 0;
            while (num)
            {
                digitSqureSum += kDigitSquares[num % 10];
                num /= 10;
            }

            num = digitSqureSum;
            if (num == 1)
                return true;

            // 死循环
            if (calculatedNums.find(num) != calculatedNums.cend())
                return false;
        }

        return false;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(Solution &solution, int num, bool expected)
{
    bool ret = solution.isHappy(num);
    if (ret != expected)
        std::printf("num: %-10d expected: %d\n", num, expected);
}


int main()
{
    Solution solution;
    doTest(solution, 19, true);
    doTest(solution, 1, true);
    doTest(solution, 4, false);
    doTest(solution, 14, false);
    return 0;
}

#endif
