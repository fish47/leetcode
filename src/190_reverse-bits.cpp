#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <array>


using namespace std;

class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t highMask = 1 << 31;
        uint32_t lowMask = 1;

        uint32_t ret = 0;
        for (int i = 0; i < 16; ++i)
        {
            uint32_t highVal = (lowMask & n) ? highMask : 0;
            uint32_t lowVal = (highMask & n) ? lowMask : 0;
            ret |= highVal;
            ret |= lowVal;

            highMask >>= 1;
            lowMask <<= 1;
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(uint32_t num, uint32_t expected)
{
    Solution solution;
    if (solution.reverseBits(num) != expected)
        std::printf("Test failed.\n");
}

int main()
{
    doTest(0x80000000, 1);
    doTest(0xfffff000, 0x000fffff);
    return 0;
}

#endif
