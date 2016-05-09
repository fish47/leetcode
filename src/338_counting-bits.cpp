#include <cstdio>
#include <algorithm>
#include <vector>

class Solution
{
public:
    std::vector<int> countBits(int num)
    {
        std::vector<int> ret;
        if (num < 0)
            return ret;

        if (num >= 0)
            ret.push_back(0);

        if (num >= 1)
            ret.push_back(1);

        for (auto i = 2; i <= num; ++i)
        {
            // 例如计算 0b011 可以基于 0b001 的结果
            int prevIdx = (i & (i - 1));
            ret.push_back(ret[prevIdx] + 1);
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static int getOneBitCount(int num)
{
    int ret = 0;
    while (num > 0)
    {
        ret += (num & 1);
        num >>= 1;
    }
    return ret;
}

int main()
{
    std::vector<int> nums;
    Solution solution;
    for (auto i = 0; i < 1000; ++i)
    {
        nums.clear();
        for (auto j = 0; j <= i; ++j)
            nums.push_back(getOneBitCount(j));

        std::vector<int> ret = solution.countBits(i);
        if (ret != nums)
        {
            std::printf("Test failed.\n");
            break;
        }
    }
    return 0;
}

#endif
