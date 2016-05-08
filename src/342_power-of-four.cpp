#include <cstdio>
#include <cstdlib>
#include <algorithm>


class Solution
{
private:
    static const int kPowerOfFourMask   = 0x55555555;

public:
    bool isPowerOfFour(int num)
    {
        /*
         * 1    -> 0b0000001
         * 4    -> 0b0000100
         * 16   -> 0b0010000
         * 64   -> 0b1000000
         *
         * 规律就是最高位只出现在特定位置，而且没有其他位是 1
         */

        return (num > 0 && !(num & (num - 1)) && (num & kPowerOfFourMask));
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(int num, bool assertVal)
{
    Solution solution;
    if (solution.isPowerOfFour(num) != assertVal)
        std::printf("Test failed: %d -> %d", num, assertVal);
}

int main()
{
    doTest(1, true);
    doTest(4, true);
    doTest(16, true);
    doTest(64, true);
    doTest(-1, false);
    doTest(512, false);
    return 0;
}

#endif
