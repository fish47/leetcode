#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


static const int    kColorRed   = 0;
static const int    kColorWhite = 1;
static const int    kColorBlue  = 2;

class Solution
{
public:
    void sortColors(std::vector<int> &nums)
    {
        auto redCount = 0;
        auto whiteCount = 0;
        auto blueCount = 0;
        for (auto &num : nums)
        {
            redCount += (num == kColorRed);
            whiteCount += (num == kColorWhite);
            blueCount += (num == kColorBlue);
        }

        auto it = nums.begin();
        std::fill_n(it, redCount, kColorRed);

        it += redCount;
        std::fill_n(it, whiteCount, kColorWhite);

        it += whiteCount;
        std::fill_n(it, blueCount, kColorBlue);
    }
};


#ifdef LEETCODE_DEBUG

int main()
{
    Solution solution;
    std::vector<int> colors;
    std::vector<int> colors2;
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomColorCount(0, 10);
    for (auto i = 0; i < 1000; ++i)
    {
        colors.clear();
        std::fill_n(std::back_inserter(colors), randomColorCount(randomEngine), kColorRed);
        std::fill_n(std::back_inserter(colors), randomColorCount(randomEngine), kColorWhite);
        std::fill_n(std::back_inserter(colors), randomColorCount(randomEngine), kColorBlue);
        colors2 = colors;

        bool failed = false;
        for (auto i = 0; i < 10; ++i)
        {
            std::random_shuffle(colors.begin(), colors.end());
            solution.sortColors(colors);
            if (colors != colors2)
            {
                failed = true;
                break;
            }
        }

        if (failed)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
