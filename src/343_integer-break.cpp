#include <iostream>
#include <array>
#include <vector>


static const int kBreakFactor           = 3;

class Solution
{
public:
    int integerBreak(int n)
    {
        if (n <= 0)
            return 0;

        switch (n)
        {
            case 1:
                return 1;
            case 2:
                return 1;
            case 3:
                return 2;
            case 4:
                return 4;
            case 5:
                return 6;
        }

        /*
         * 原始状态方程是
         * f(n) = max{ i * max(n - i, f(n - i)) }
         *
         * 根据 Discuss 提示，从 6 开始必须分离出一个 3 才会有最大值，所以可以改为
         * f(n) = (n - 3) * max(n - 3, f(n - 3))
         */

        auto idx = 0;
        auto prevIdx = 0;
        std::array<int, kBreakFactor> buf = { 2, 4, 6 };
        for (auto i = 6; i <= n; ++i)
        {
            auto split = i - kBreakFactor;
            auto val = kBreakFactor * std::max(split, buf[idx]);
            buf[idx] = val;
            prevIdx = idx;
            idx = (idx + 1) % buf.size();
        }

        return buf[prevIdx];
    }
};



#ifdef LEETCODE_DEBUG

static void generateDPValues(std::vector<int> *pDPValues, int n)
{
    pDPValues->clear();
    pDPValues->push_back(0);

    for (auto i = 1; i <= n; ++i)
    {
        auto maxValue = 1;
        for (auto j = 1; j < i; ++j)
        {
            auto split = i - j;
            auto val = j * std::max(split, (*pDPValues)[split]);
            maxValue = std::max(maxValue, val);
        }
        pDPValues->push_back(maxValue);
    }
}


int main()
{
    const auto maxNumber = 40;

    std::vector<int> dpValues;
    generateDPValues(&dpValues, maxNumber);

    Solution solution;
    for (auto i = 0; i <= maxNumber; ++i)
    {
        auto ret1 = solution.integerBreak(i);
        auto ret2 = dpValues[i];
        if (ret1 != ret2)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }

    return 0;
}

#endif
