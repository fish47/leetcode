#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>


bool isBadVersion(int version);

class Solution
{
public:
    int firstBadVersion(int n)
    {
        int first = 1;
        int last = n;
        int ret = n;

        // 题目是说从某个版本开始一直失败
        while (first <= last)
        {
            // 注意直接相加可能会溢出囧囧
            int mid = first + (last - first) / 2;
            if (isBadVersion(mid))
            {
                ret = mid;
                last = mid - 1;
            }
            else
            {
                first = mid + 1;
            }
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static int sFirstBadVersion;

bool isBadVersion(int version)
{
    return (version >= sFirstBadVersion);
}


static bool doTest(std::mt19937 &randomEngine, Solution &solution)
{
    std::uniform_int_distribution<> randomMaxVersion(1, 100000);
    int maxVersion = randomMaxVersion(randomEngine);

    std::uniform_int_distribution<> randomFirstBadVersion(1, maxVersion);
    sFirstBadVersion = randomFirstBadVersion(randomEngine);

    int ret = solution.firstBadVersion(maxVersion);
    return (ret == sFirstBadVersion);
}


int main()
{
    Solution solution;
    std::mt19937 randomEngine;
    for (int i = 0; i < 100000; ++i)
    {
        if (!doTest(randomEngine, solution))
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
