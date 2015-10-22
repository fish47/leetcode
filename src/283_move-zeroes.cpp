#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <memory>


class Solution
{
public:
    void moveZeroes(std::vector<int> &nums)
    {
        int writeIdx = 0;
        int nonZeroIdx = 0;
        int numCount = nums.size();

        while (true)
        {
            // 首先找到第一个非零值的下标
            while (nonZeroIdx < numCount && nums[nonZeroIdx] == 0)
                ++nonZeroIdx;

            // 找到尾也没有
            if (nonZeroIdx >= numCount)
                break;

            // 如果前半部分都是非零，可以省一点点赋值时间
            if (writeIdx != nonZeroIdx)
                nums[writeIdx] = nums[nonZeroIdx];

            ++writeIdx;
            ++nonZeroIdx;
        }

        // 末尾填充零
        if (writeIdx < numCount)
            std::fill(nums.begin() + writeIdx, nums.end(), 0);
    }
};



#ifdef LEETCODE_DEBUG

static void generateRandomIntVector(std::mt19937 &randomEngine,
                                    std::vector<int> *pVecNums)
{
    pVecNums->clear();
    int count = std::uniform_int_distribution<>(1, 1000)(randomEngine);
    for (int i = 0; i < count; ++i)
    {
        int val = std::uniform_int_distribution<>(0, 5)(randomEngine);
        pVecNums->push_back(val);
    }
}


static bool doTest(Solution &solution,
                   std::vector<int> &vecNums,
                   std::vector<int> *pVecMoved,
                   std::vector<int> *pVecResults)
{
    *pVecResults = vecNums;
    auto itRemoveEnd = std::remove_if(pVecResults->begin(),
                                      pVecResults->end(),
                                      [](const int &val) { return val == 0; });
    std::fill(itRemoveEnd, pVecResults->end(), 0);

    *pVecMoved = vecNums;
    solution.moveZeroes(*pVecMoved);
    return *pVecMoved == *pVecResults;
}


int main()
{
    std::mt19937 randomEngine;
    Solution solution;
    std::vector<int> vecNums;
    std::vector<int> vecResults;
    std::vector<int> vecMoved;

    for (int i = 0; i < 100000; ++i)
    {
        generateRandomIntVector(randomEngine, &vecNums);
        bool ret = doTest(solution, vecNums, &vecMoved, &vecResults);
        if (!ret)
        {
            std::printf("Test failed\n");
            break;
        }
    }

    return 0;
}

#endif
