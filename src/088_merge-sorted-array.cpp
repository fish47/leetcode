#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <functional>
#include <vector>


class Solution
{
public:
    void merge(std::vector<int> &vecNums1, int numCount1,
               std::vector<int> &vecNums2, int numCount2)
    {
        int idx1 = 0;
        int idx2 = 0;
        int remainingCount1 = numCount1;
        int totalCount = numCount1 + numCount2;

        // 不知道外部有没有做这一步
        vecNums1.resize(totalCount);

        while (remainingCount1 > 0 || idx2 < numCount2)
        {
            bool needToMergeFromNums2 = true;
            if (idx2 < numCount2 && remainingCount1 > 0)
                needToMergeFromNums2 = (vecNums1[idx1] > vecNums2[idx2]);
            else if (idx2 == numCount2)
                needToMergeFromNums2 = false;

            if (needToMergeFromNums2)
            {
                // 腾出一个空位给新元素
                auto itStart = vecNums1.begin() + idx1;
                auto itEnd = itStart + remainingCount1;
                std::copy_backward(itStart, itEnd, itEnd + 1);

                vecNums1[idx1] = vecNums2[idx2];

                ++idx1;
                ++idx2;
            }
            else
            {
                ++idx1;
                --remainingCount1;
            }
        }
    }
};



#ifdef LEETCODE_DEBUG

static bool doTest(Solution &solution,
                   std::mt19937 &randomEngine,
                   std::vector<int> *pVecNum1,
                   std::vector<int> *pVecNum2,
                   std::vector<int> *pVecSorted)
{
    std::uniform_int_distribution<> randomNumCount(0, 100);
    std::uniform_int_distribution<> randomNumValue(0, 100000);

    int numCount1 = randomNumCount(randomEngine);
    int numCount2 = randomNumCount(randomEngine);

    pVecNum1->clear();
    pVecNum2->clear();
    pVecSorted->clear();

    auto cbGenerateValue = std::bind(randomNumValue, randomEngine);
    std::generate_n(std::back_inserter(*pVecNum1), numCount1, cbGenerateValue);
    std::generate_n(std::back_inserter(*pVecNum2), numCount2, cbGenerateValue);

    std::sort(pVecNum1->begin(), pVecNum1->end());
    std::sort(pVecNum2->begin(), pVecNum2->end());

    std::copy(pVecNum1->begin(), pVecNum1->end(), std::back_inserter(*pVecSorted));
    std::copy(pVecNum2->begin(), pVecNum2->end(), std::back_inserter(*pVecSorted));

    solution.merge(*pVecNum1, numCount1, *pVecNum2, numCount2);
    std::sort(pVecSorted->begin(), pVecSorted->end());

    return (*pVecNum1 == *pVecSorted);
}

int main()
{
    Solution solution;
    std::mt19937 randomEngine;
    std::vector<int> vecNums1;
    std::vector<int> vecNums2;
    std::vector<int> vecSorted;

    for (int i = 0; i < 10000; ++i)
    {
        if (!doTest(solution, randomEngine, &vecNums1, &vecNums2, &vecSorted))
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
