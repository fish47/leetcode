#include <iostream>
#include <vector>


class Solution
{
public:
    int maxSubArray(std::vector<int> &nums)
    {
        /*
         * 设 f(i) 在 [0, i] 的数列中最大的子序列和。
         * f(i) = max{ nums[i], f(i - 1) + nums[i] }
         */

        auto ret = nums.empty() ? 0 : nums.front();
        auto subArraySum = 0;
        for (auto num : nums)
        {
            subArraySum = std::max(subArraySum + num, num);
            ret = std::max(ret, subArraySum);
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> nums, int expected)
{
    Solution solution;
    auto ret = solution.maxSubArray(nums);
    if (ret != expected)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest({}, 0);
    doTest({ -1, -2, -3, -5 }, -1);
    doTest({ -2, 1, -3, 4, -1, 2, 1, -5, 4 }, 6);
    return 0;
}

#endif
