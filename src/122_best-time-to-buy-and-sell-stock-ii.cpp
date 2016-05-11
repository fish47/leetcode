#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>



class Solution
{
public:
    int maxProfit(std::vector<int> &vecPrices)
    {
        int ret = 0;
        if (vecPrices.empty())
            return ret;

        bool hasBought = false;
        int prevPrice = vecPrices[0];
        for (int i = 1, n = vecPrices.size(); i < n; ++i)
        {
            // 持平
            int curPrice = vecPrices[i];
            if (curPrice == prevPrice)
                continue;

            if (curPrice > prevPrice)
            {
                // 趁低买入
                if (!hasBought)
                {
                    hasBought = true;
                    ret -= prevPrice;
                }
            }
            else
            {
                // 趁高卖出
                if (hasBought)
                {
                    hasBought = false;
                    ret += prevPrice;
                }
            }

            prevPrice = curPrice;
        }

        // 趁早套现吧
        if (hasBought)
        {
            hasBought = false;
            ret += prevPrice;
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> vecPrices, int expected)
{
    Solution solution;
    int ret = solution.maxProfit(vecPrices);
    if (expected != ret)
        std::printf("Test failed.\n");
}

int main()
{
    doTest({ 1 }, 0);
    doTest({ 1, 2 }, 1);
    doTest({ 2, 1 }, 0);
    doTest({ 2, 1, 0 }, 0);
    doTest({ 1, 2, 3 }, 2);
    doTest({ 1, 1, 1, 1, 5 }, 4);

    doTest({ 1, 2, 1, 2, 5 }, 5);
    doTest({ 1, 2, 2, 2, 2 }, 1);

    doTest({ 5, 3, 2, 2, 1 }, 0);

    return 0;
}

#endif
