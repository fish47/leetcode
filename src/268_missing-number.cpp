#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class Solution
{
public:
    int missingNumber(std::vector<int> &nums)
    {
        auto xorResult = 0;
        auto numCount = nums.size();
        for (auto i = 0; i < numCount; ++i)
        {
            // 这是 136_single-number 的变型
            // 因为长度为 n 的数组元素也是 [0, n - 1] ，提前用索引值抵消
            xorResult ^= i;
            xorResult ^= nums[i];
        }
        xorResult ^= numCount;
        return xorResult;
    }
};


#ifdef LEETCODE_DEBUG

int main()
{
    Solution solution;
    std::vector<int> nums;
    std::mt19937 randomEngine;
    for (auto i = 1; i < 1000; ++i)
    {
        auto numValue = 0;
        nums.clear();
        std::generate_n(std::back_inserter(nums), i, [&numValue]() { return numValue++; });
        std::random_shuffle(nums.begin(), nums.end());

        std::uniform_int_distribution<> randomIdx(0, i - 1);
        auto idx = randomIdx(randomEngine);
        auto missedNum = nums[idx];
        nums.erase(nums.cbegin() + idx);

        auto ret = solution.missingNumber(nums);
        if (ret != missedNum)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }

    return 0;
}

#endif
