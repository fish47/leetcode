#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>


static const int kMinPowerOfThreeInt    = 1;
static const int kMaxPowerOfThreeInt    = 1162261467;

class Solution
{
public:
    bool isPowerOfThree(int n)
    {
        return (n >= kMinPowerOfThreeInt && kMaxPowerOfThreeInt % n == 0);
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(int num, bool val)
{
    Solution solution;
    if (solution.isPowerOfThree(num) != val)
        std::printf("Test failed.\n");
}

int main()
{
    doTest(-1, false);
    doTest(0, false);
    doTest(1, true);
    doTest(3, true);
    doTest(9, true);
    return 0;
}

#endif
