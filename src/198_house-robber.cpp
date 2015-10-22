#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>


class Solution
{
public:
    int rob(std::vector<int> &vecNums)
    {
        // 简单一维 DP
        // f(i) = max{ f(i - 2) + m[i], f(i - 1) }

        int ret = 0;
        int prevMaxSum = 0;
        int prevPrevMaxSum = 0;
        for (int i = 0, n = vecNums.size(); i < n; ++i)
        {
            // 详见递推式，方向不重要
            int curMaxSum = std::max(prevPrevMaxSum + vecNums[i], prevMaxSum);
            ret = std::max(ret, curMaxSum);

            // 相对于下一轮而言
            prevPrevMaxSum = prevMaxSum;
            prevMaxSum = curMaxSum;
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> vecNums, int expected)
{
    Solution solution;
    if (solution.rob(vecNums) != expected)
        std::printf("Test failed.\n");
}

int main()
{
    doTest({}, 0);
    doTest({ 1, 3 }, 3);
    doTest({ 1, 3, 1 }, 3);
    doTest({ 1, 3, 1, 100, 102 }, 105);
    return 0;
}

#endif
