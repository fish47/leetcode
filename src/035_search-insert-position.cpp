#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>


class Solution
{
public:
    int searchInsert(std::vector<int> &nums, int target)
    {
        int low = 0;
        int high = nums.size() - 1;
        while (low <= high)
        {
            int mid = (high + low) / 2;
            auto val = nums[mid];
            if (val == target)
                return mid;
            else if (val < target)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return low;
    }
};


#ifdef LEETCODE_DEBUG

static void fillUniqueNumbers(std::vector<int> *pNums, int maxCount, std::function<int()> func)
{
    if (!pNums || !func)
        return;

    pNums->clear();
    std::generate_n(std::back_inserter(*pNums), maxCount, func);
    std::sort(pNums->begin(), pNums->end());

    auto it = std::unique(pNums->begin(), pNums->end());
    pNums->erase(it, pNums->cend());
}


int main()
{
    Solution solution;
    std::vector<int> nums;
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomNumber(-1000, 1000);
    std::uniform_int_distribution<> randomNumberCount(0, 1000);
    auto cbRandomNumber = std::bind(randomNumber, randomEngine);
    for (auto i = 0; i < 100; ++i)
    {
        bool failed = false;
        fillUniqueNumbers(&nums, randomNumberCount(randomEngine), cbRandomNumber);
        for (auto j = 0; j < 100; ++j)
        {
            auto target = cbRandomNumber();
            auto ret1 = solution.searchInsert(nums, target);
            auto ret2 = std::lower_bound(nums.cbegin(), nums.cend(), target) - nums.cbegin();
            if (ret1 != ret2)
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
