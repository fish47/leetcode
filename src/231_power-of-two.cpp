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
#include <array>


class Solution
{
public:
    bool isPowerOfTwo(int num)
    {
        if (num <= 0)
            return false;

        // 如果除了最高位外还有 1 ，自减之后最高位的 1 不会消失
        return !(num & (num - 1));
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(int num, bool expected)
{
    Solution solution;
    if (solution.isPowerOfTwo(num) != expected)
        std::printf("Test failed.\n");
}


int main()
{
    doTest(-1, false);
    doTest(-5, false);
    doTest(0, false);
    doTest(1, true);
    doTest(2, true);
    doTest(1 << 30, true);
    return 0;
}


#endif
