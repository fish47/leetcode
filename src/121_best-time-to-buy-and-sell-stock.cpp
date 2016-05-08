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

        int minPrice = vecPrices.front();
        for (int i = 1, n = vecPrices.size(); i < n; ++i)
        {
            int price = vecPrices[i];
            ret = std::max(ret, price - minPrice);
            minPrice = std::min(minPrice, price);
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> vecPrices, int assertValue)
{
    Solution solution;
    int ret = solution.maxProfit(vecPrices);
    if (ret != assertValue)
        std::printf("Test failed.\n");
}

int main()
{
    doTest({ 1 }, 0);
    doTest({ 5, 4, 3, 2, 1 }, 0);
    doTest({ 1, 2, 5, 2, 5, 4 }, 4);
    return 0;
}

#endif
