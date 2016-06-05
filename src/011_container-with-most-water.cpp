#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <algorithm>


class Solution
{
public:
    int maxArea(std::vector<int> &heights)
    {
        int i = 0;
        int j = heights.size() - 1;
        auto ret = 0;
        while (i < j)
        {
            auto area = (j - i) * std::min(heights[i], heights[j]);
            ret = std::max(ret, area);

            /*
             * 例如 heights[i] < heights[j] ，
             * 对于 [i, i + 1] ~ [i, j] 范围的面积都不用检查了，
             * 因为此时就是最大值。
             */
            if (heights[i] < heights[j])
                ++i;
            else
                --j;
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static int getMaxArea(std::vector<int> &heights)
{
    auto ret = 0;
    auto heightCount = heights.size();
    for (auto i = 0; i < heightCount; ++i)
    {
        for (auto j = i + 1; j < heightCount; ++j)
            ret = std::max(ret, (j - i) * std::min(heights[i], heights[j]));
    }
    return ret;
}

int main()
{
    Solution solution;
    std::vector<int> heights;
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomHeight(0, 1000);
    std::uniform_int_distribution<> randomHeightCount(1, 30);
    auto cbRandomHeight = std::bind(randomHeight, randomEngine);
    for (auto i = 0; i < 1000; ++i)
    {
        heights.clear();
        std::generate_n(std::back_inserter(heights), randomHeightCount(randomEngine), cbRandomHeight);

        auto ret1 = getMaxArea(heights);
        auto ret2 = solution.maxArea(heights);
        if (ret1 != ret2)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
