#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <random>


class Solution
{
public:
    std::vector<int> intersection(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        std::vector<int> ret;
        std::unordered_set<int> numSet(nums1.cbegin(), nums1.cend());
        for (auto num : nums2)
        {
            if (numSet.find(num) != numSet.cend())
                ret.push_back(num);
        }

        // 去重
        std::sort(ret.begin(), ret.end());
        auto it = std::unique(ret.begin(), ret.end());
        ret.erase(it, ret.cend());
        return ret;
    }
};



#ifdef LEETCODE_DEBUG


static void doTest(std::vector<int> nums1, std::vector<int> nums2, std::vector<int> expected)
{
    Solution solution;
    auto ret = solution.intersection(nums1, nums2);
    std::sort(ret.begin(), ret.end());
    std::sort(expected.begin(), expected.end());
    if (ret != expected)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest({ 1 }, { 2, 3 }, {});
    doTest({ 1, 2 }, { 3, 4 }, {});
    doTest({ 2, 1 }, { 1, 1 }, { 1 });
    doTest({ 1 }, { 1, 2, 3 }, { 1 });
    return 0;
}

#endif
