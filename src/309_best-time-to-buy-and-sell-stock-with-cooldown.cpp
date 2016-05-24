#include <iostream>
#include <vector>
#include <limits>
#include <type_traits>


static const int    kTransactionCoolDown    = 1;

class Solution
{
public:
    int maxProfit(std::vector<int> &prices)
    {
        /*
         * 设 f(i) 为不持股时的总收益，设 g(i) 为在 i 时刻买入时的总收益。
         * f(i) = max{ 0, g(j) + prices[i] }
         * g(i) = f(j) - prices[i] | i - j >= cooldown
         */

        typedef std::remove_reference<decltype(prices)>::type::value_type PriceType;

        PriceType ret = 0;
        if (prices.empty())
            return ret;

        PriceType maxBoughtProfit = -prices.front();
        PriceType maxSoldProfit = 0;

        auto soldProfitBufIdx = 0;
        PriceType soldProfitBuf[kTransactionCoolDown] = { 0 };

        for (auto price : prices)
        {
            // 买了之后可以立刻卖
            auto curMaxSoldProfit = std::max(maxBoughtProfit + price, 0);
            auto curMaxBoughtProfit = maxSoldProfit - price;

            // 下一轮可以用缓存区最后的值
            // 卖了不能立刻买，不持股收益要放入缓存区
            soldProfitBufIdx = (soldProfitBufIdx + 1) % (kTransactionCoolDown);
            maxSoldProfit = std::max(maxSoldProfit, soldProfitBuf[soldProfitBufIdx]);
            maxBoughtProfit = std::max(maxBoughtProfit, curMaxBoughtProfit);
            soldProfitBuf[soldProfitBufIdx] = curMaxSoldProfit;

            // 可以减少在最后迭代一次缓冲区
            ret = std::max(ret, curMaxSoldProfit);
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> prices, int expected)
{
    Solution solution;
    auto ret = solution.maxProfit(prices);
    if (ret != expected)
        std::cout << "Test failed." << std::endl;
}


int main()
{
    doTest({ 1, 5, 0, 9 }, 9);
    doTest({ 1, 2, 3, 0, 2 }, 3);
    doTest({ 5, 4, 3, 2, 1 }, 0);
    doTest({ 1, 2, 3, 4, 5 }, 4);
    return 0;
}

#endif
