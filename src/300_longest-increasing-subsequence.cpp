#include <iostream>
#include <vector>
#include <algorithm>


class Solution
{
public:
    int lengthOfLIS(std::vector<int> &nums)
    {
        std::vector<int> sequence;
        for (auto num : nums)
        {
            // 用小值去替换大值，尽可能让后来的数加到序列中
            auto it = std::lower_bound(sequence.begin(), sequence.end(), num);
            if (it == sequence.cend())
                sequence.push_back(num);
            else
                *it = num;
        }

        return sequence.size();
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> nums, int len)
{
    Solution solution;
    auto ret = solution.lengthOfLIS(nums);
    if (ret != len)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest({ 10, 9, 2, 5, 3, 7, 101, 18 }, 4);
    doTest({ 5, 4, 3, 2, 1 }, 1);
    doTest({ 1, 2, 3, 4, 5 }, 5);
    doTest({ 5, 4, 2, 1, 3 }, 2);
    doTest({ 1, 1, 1, 1, 1 }, 1);
    return 0;
}

#endif
