#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>


class Solution
{
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k)
    {
        typedef std::pair<int, int> IntPair;

        std::unordered_map<int, int> map;
        std::for_each(nums.cbegin(), nums.cend(), [&map](const int &num) { ++map[num]; });

        bool shouldPop = false;
        std::vector<int> ret;
        std::priority_queue<IntPair> queue;
        for (IntPair entry : map)
        {
            auto num = entry.first;
            auto count = entry.second;
            queue.push(std::make_pair(count, num));
        }

        for (auto i = 0; i < k; ++i)
        {
            auto &entry = queue.top();
            ret.push_back(entry.second);
            queue.pop();
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> nums, int k, std::vector<int> assertNums)
{
    Solution solution;
    std::vector<int> ret = solution.topKFrequent(nums, k);
    if (ret != assertNums)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest({ 1, 2, 3, 4 }, 0, {});
    doTest({ 1, 1, 1, 2, 3, 4 }, 1, { 1 });
    doTest({ 1, 1, 1, 2, 2, 3 }, 2, { 1, 2 });
    return 0;
}

#endif
