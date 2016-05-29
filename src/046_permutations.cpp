#include <iostream>
#include <vector>
#include <algorithm>


typedef std::vector<int>            Permutation;
typedef std::vector<Permutation>    Permutations;

class Solution
{
public:
    Permutations permute(Permutation &nums)
    {
        Permutations ret;
        Permutation tmp = nums;
        std::vector<int> swapIndexes;
        swapIndexes.push_back(0);
        while (!swapIndexes.empty())
        {
            if (swapIndexes.size() < nums.size())
            {
                auto nextSwapIdx = swapIndexes.size();
                swapIndexes.push_back(nextSwapIdx);
                continue;
            }

            ret.push_back(tmp);

            while (true)
            {
                swapIndexes.pop_back();
                if (swapIndexes.empty())
                    break;

                // 恢复之前的交换
                auto curIdx = swapIndexes.size() - 1;
                auto curSwapIdx = swapIndexes.back();
                std::swap(tmp[curIdx], tmp[curSwapIdx]);

                // 下一轮
                ++curSwapIdx;
                if (curSwapIdx < nums.size())
                {
                    swapIndexes.back() = curSwapIdx;
                    std::swap(tmp[curIdx], tmp[curSwapIdx]);
                    break;
                }
            }
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doCalcPermutations(Permutations &perms, Permutation &tmp, int curIdx)
{
    if (curIdx == tmp.size())
    {
        perms.push_back(tmp);
        return;
    }

    doCalcPermutations(perms, tmp, curIdx + 1);

    auto count = tmp.size();
    for (auto i = curIdx + 1; i < count; ++i)
    {
        std::swap(tmp[curIdx], tmp[i]);
        doCalcPermutations(perms, tmp, curIdx + 1);
        std::swap(tmp[curIdx], tmp[i]);
    }
}

static void calcPermutations(Permutations *pPerms, Permutation perm)
{
    if (!pPerms)
        return;

    doCalcPermutations(*pPerms, perm, 0);
}


int main()
{
    Solution solution;
    Permutation perm;
    Permutations perms;
    for (auto i = 0; i < 10; ++i)
    {
        perm.clear();
        for (auto val = 0; val <= i; ++val)
            perm.push_back(val);

        perms.clear();
        calcPermutations(&perms, perm);
        auto ret = solution.permute(perm);
        if (ret != perms)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }

    }
    return 0;
}

#endif
