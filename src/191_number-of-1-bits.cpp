#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <climits>
#include <ctime>
#include <algorithm>
#include <iostream>


static const int BYTE_ONE_BIT_COUNT_MAP[] =
{
    0, 1, 1, 2, 1, 2, 2, 3,
    1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4,
    2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4,
    2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5,
    3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4,
    2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5,
    3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5,
    3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6,
    4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4,
    2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5,
    3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5,
    3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6,
    4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5,
    3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6,
    4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6,
    4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7,
    5, 6, 6, 7, 6, 7, 7, 8,
};

class Solution
{
public:
    int hammingWeight(std::uint32_t n)
    {
        int ret = 0;
        while (n != 0)
        {
            int byte = (n & 0xff);
            ret += BYTE_ONE_BIT_COUNT_MAP[byte];
            n >>= 8;
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static int getOneBitCount(std::uint32_t n)
{
    int ret = 0;
    while (n != 0)
    {
        ret += (n & 1);
        n >>= 1;
    }

    return ret;
}

int main()
{
    std::srand(std::time(0));

    Solution solution;
    for (int i = 0; i < 100000; ++i)
    {
        uint32_t num = std::rand();
        if (getOneBitCount(num) != solution.hammingWeight(num))
        {
            std::cout << "Bang!" << std::endl;
            break;
        }
    }

    return 0;
}

#endif
