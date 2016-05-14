#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

class Solution
{
public:
    int singleNumber(std::vector<int> &nums)
    {
        // 用 64bit 去统计 1 的出次次数，不过是逢三清零
        auto count1 = 0;
        auto count2 = 0;
        for (auto num : nums)
        {
            // 低位满二高位加一
            count2 |= (num & count1);

            // 低位做溢出加法
            count1 ^= num;

            // 逢三清零
            auto mask = (count1 & count2);
            count1 &= ~mask;
            count2 &= ~mask;
        }

        // 最后肯定只多出一个 1
        return count1;
    }
};



#ifdef LEETCODE_DEBUG

static int createTestCase(std::vector<int> *pNums, int numCount)
{
    if (!pNums || numCount <= 1)
        return 0;

    pNums->clear();
    pNums->resize(numCount);

    auto insertIt = pNums->begin();
    while (true)
    {
        std::generate_n(insertIt, numCount, []() { return std::rand(); });
        insertIt = std::unique(pNums->begin(), pNums->end());
        if (insertIt == pNums->cend())
            break;
    }

    // 最后一个数就是答案，将其他值再重复两次
    auto result = (*pNums)[numCount - 1];
    for (auto i = 0; i < numCount - 1; ++i)
    {
        auto val = (*pNums)[i];
        pNums->push_back(val);
        pNums->push_back(val);
    }

    return result;
}


int main()
{
    Solution solution;
    std::vector<int> nums;
    for (auto i = 0; i < 1000; ++i)
    {
        auto failed = false;
        int numCount = std::rand() % 30 + 2;
        auto result = createTestCase(&nums, numCount);
        for (auto j = 0; j < 30; ++j)
        {
            auto ret = solution.singleNumber(nums);
            if (ret != result)
            {
                std::cout << "Test failed." << std::endl;
                failed = true;
                break;
            }
        }

        if (failed)
            break;
    }
    return 0;
}

#endif
