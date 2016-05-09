#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>


class Solution
{
public:
    std::vector<int> singleNumber(std::vector<int> &nums)
    {
        auto cbXor = [](const int &a, const int &b) { return a ^ b; };
        int xorResult = std::accumulate(nums.cbegin(), nums.cend(), 0, cbXor);
        int xorResultMSB = (xorResult & ~(xorResult - 1));

        int num1 = 0;
        int num2 = 0;
        for (auto num : nums)
        {
            // 因为返回的两个值是不相同的，所相异或后最后的值一定不为零
            if (xorResultMSB & num)
                num1 ^= num;
            else
                num2 ^= num;
        }

        if (num1 > num2)
            std::swap(num1, num2);

        return { num1, num2 };
    }
};


#ifdef LEETCODE_DEBUG

static bool doTest()
{
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomNumCount(2, 100);
    int numCount = randomNumCount(randomEngine) & ~1;
    std::vector<int> nums;
    for (auto i = 0; i < numCount; ++i)
    {
        nums.push_back(i);
        nums.push_back(i);
    }

    int ret1 = numCount + 1;
    int ret2 = numCount + 2;
    nums.push_back(ret1);
    nums.push_back(ret2);

    Solution solution;
    for (auto i = 0; i < 10; ++i)
    {
        std::shuffle(nums.begin(), nums.end(), randomEngine);
        std::vector<int> ret = solution.singleNumber(nums);
        if (ret[0] != ret1 || ret[1] != ret2)
        {
            std::printf("Test failed.\n");
            return false;
        }
    }

    return true;
}

int main()
{
    for (auto i = 0; i < 1000; ++i)
    {
        if (!doTest())
            break;
    }
    return 0;
}

#endif
