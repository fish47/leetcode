#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <list>


class Solution
{
public:
    int removeDuplicates(std::vector<int>& vecNums)
    {
        int iWriteIdx = -1;
        int iReadIdx = 0;
        int nOrgSize = vecNums.size();

        while (iReadIdx < nOrgSize)
        {
            if (iWriteIdx < 0 || vecNums[iReadIdx] != vecNums[iWriteIdx])
            {
                ++iWriteIdx;
                vecNums[iWriteIdx] = vecNums[iReadIdx];
            }

            ++iReadIdx;
        }

        return (iWriteIdx + 1);
    }
};



#ifdef LEETCODE_DEBUG

int main()
{
    Solution solution;
    std::mt19937 randomEngine;
    std::vector<int> vecNums;
    std::vector<int> vecNumsCmp;

    std::uniform_int_distribution<> randomNumCount(0, 100);
    std::uniform_int_distribution<> randomNumValue(0, 100);

    for (int i = 0; i < 100000; ++i)
    {
        vecNums.resize(randomNumCount(randomEngine));
        for (int j = 0, n = vecNums.size(); j < n; ++j)
            vecNums[j] = randomNumValue(randomEngine);

        std::sort(vecNums.begin(), vecNums.end());
        vecNumsCmp = vecNums;

        int len = solution.removeDuplicates(vecNums);
        vecNums.resize(len);

        auto itNewEnd = std::unique(vecNumsCmp.begin(), vecNumsCmp.end());
        vecNumsCmp.erase(itNewEnd, vecNumsCmp.end());

        if (vecNums != vecNumsCmp)
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
