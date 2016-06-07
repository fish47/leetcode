#include <iostream>
#include <vector>


static const int    kIncreasingSeqLength    = 3;

class Solution
{
public:
    bool increasingTriplet(std::vector<int> &nums)
    {
        // 其实就是 O(nlogn) 的 LIS 变式，因为最大长度固定所以是常数项规模
        std::vector<int> sequence;
        for (auto num : nums)
        {
            auto it = std::lower_bound(sequence.begin(), sequence.end(), num);
            if (it == sequence.end())
            {
                sequence.push_back(num);
                if (sequence.size() >= kIncreasingSeqLength)
                    return true;
            }
            else
            {
                *it = num;
            }
        }

        return false;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> nums, bool val)
{
    Solution solution;
    auto ret = solution.increasingTriplet(nums);
    if (ret != val)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest({ 1, 2, 3, 4, 5 }, true);
    doTest({ 5, 4, 3, 2, 1 }, false);
    doTest({ 1, 1, 1, 1, 1 }, false);
    doTest({ 8, 9, 4, 5, 1, 2 }, false);
    return 0;
}

#endif
