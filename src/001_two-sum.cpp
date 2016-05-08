#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>


class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> &nums, int target)
    {
        std::unordered_map<int, int> map;
        for (int i = 0, n = nums.size(); i < n; ++i)
            map[nums[i]] = i;

        std::vector<int> ret;
        for (int i = 0, n = nums.size(); i < n; ++i)
        {
            auto it = map.find(target - nums[i]);
            if (it != map.cend() && i != it->second)
            {
                ret.push_back(std::min(i, it->second));
                ret.push_back(std::max(i, it->second));
                return ret;
            }
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> nums, int target, std::vector<int> assertIndexes)
{
    Solution solution;
    std::vector<int> ret = solution.twoSum(nums, target);
    if (ret != assertIndexes)
        std::printf("Test failed.\n");
}

int main()
{
    doTest({ 3, 2, 4 }, 6, { 1, 2 });
    doTest({ 2, 7, 11, 15 }, 9, { 0, 1 });
    doTest({ 1, 2, 3, 4, 5, 6 }, 100, {});
    doTest({ 1, 2, 3, 4, 5, 6 }, 10, { 3, 5 });
    return 0;
}

#endif
