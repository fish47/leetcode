#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>


static bool advanceIndex(std::vector<int> &vecNums,
                         int *pIdx, int step, int anchorIdx)
{
    if (!pIdx)
        return false;

    auto &idx = *pIdx;
    auto size = vecNums.size();
    auto idxBak = idx;
    while (true)
    {
        if (idx <= anchorIdx || idx >= size)
            return false;

        if (vecNums[idx] != vecNums[idxBak])
            break;

        idx += step;
    }
    return true;
}

static void appendCombination(std::vector<std::vector<int>> &vecVecCombinations,
                              int a, int b, int c, int d)
{
    vecVecCombinations.emplace_back();
    auto &vecNums = vecVecCombinations.back();
    vecNums.push_back(a);
    vecNums.push_back(b);
    vecNums.push_back(c);
    vecNums.push_back(d);
#ifdef LEETCODE_DEBUG
    std::sort(vecNums.begin(), vecNums.end());
#endif
}

static bool findBBXSumCombination(std::vector<int> &vecNums, int idx, int anchorIdx, int c)
{
    auto b = vecNums[idx];
    auto idx2 = idx + 1;
    auto idx3 = idx + 2;
    if (idx3 >= vecNums.size() || vecNums[idx2] != b)
        return false;

    // 例如对于 [ 0, 1, 1, 1, 4] 时 idx = 2 其实就枚举过 b + b + x 的情况
    auto idx1 = idx - 1;
    if (idx > anchorIdx && vecNums[idx1] == b)
        return false;

    auto it = std::find(vecNums.cbegin() + idx3, vecNums.cend(), c);
    return (it != vecNums.cend());
}

static void calculateSumCombinations(std::vector<int> &vecNums,
                                     std::vector<std::vector<int>> &vecVecCombinations,
                                     int anchorIdx, int target)
{
    auto anchorVal = vecNums[anchorIdx];
    auto threeSumTarget = target - anchorVal;
    auto idx = anchorIdx + 2;
    auto count = vecNums.size();
    while (idx < count)
    {
        // 枚举 a + b + c 的组合情况，其中 a < b && b <= c
        auto b = vecNums[idx];
        int leftIdx = idx - 1;
        int rightIdx = idx + 1;
        bool advanced = (leftIdx > anchorIdx && rightIdx < count);
        while (advanced)
        {
            // 注意不要选中锚定索引
            auto a = vecNums[leftIdx];
            auto c = vecNums[rightIdx];
            auto delta = a + b + c - threeSumTarget;
            if (delta == 0)
                appendCombination(vecVecCombinations, a, b, c, anchorVal);

            if (delta >= 0)
                advanced = advanced && advanceIndex(vecNums, &leftIdx, -1, anchorIdx);
            if (delta <= 0)
                advanced = advanced && advanceIndex(vecNums, &rightIdx, 1, anchorIdx);
        }

        // 上面流程可能没有枚举 b + b + x 的情况，最后要特判一下
        auto val = threeSumTarget - b - b;
        if (findBBXSumCombination(vecNums, idx, anchorIdx, val))
            appendCombination(vecVecCombinations, b, b, val, anchorVal);

        if (!advanceIndex(vecNums, &idx, 1, anchorIdx))
            break;
    }
}


class Solution
{
public:
    std::vector<std::vector<int>> fourSum(std::vector<int> &vecNums, int target)
    {
        std::vector<std::vector<int>> vecVecCombinations;
        if (vecNums.size() < 4)
            return vecVecCombinations;

        int i = 0;
        std::sort(vecNums.begin(), vecNums.end());
        while (true)
        {
            calculateSumCombinations(vecNums, vecVecCombinations, i, target);
            if (!advanceIndex(vecNums, &i, 1, -1))
                break;
        }
        return vecVecCombinations;
    }
};

#ifdef LEETCODE_DEBUG

static void calculateSumCombinationResults(std::vector<int> &vecNums,
                                           std::vector<std::vector<int>> *pVecVecCombinations,
                                           int target)
{
    if (!pVecVecCombinations)
        return;

    pVecVecCombinations->clear();
    for (int i = 0, n = vecNums.size(); i < n; ++i)
    {
        auto a = vecNums[i];
        for(int j = i + 1; j < n; ++j)
        {
            auto b = vecNums[j];
            for (int k = j + 1; k < n; ++k)
            {
                auto c = vecNums[k];
                for (int m = k + 1; m < n; ++m)
                {
                    auto d = vecNums[m];
                    if (a + b + c + d == target)
                        appendCombination(*pVecVecCombinations, a, b, c, d);
                }
            }
        }
    }
    std::sort(pVecVecCombinations->begin(), pVecVecCombinations->end());
    auto itRemove = std::unique(pVecVecCombinations->begin(), pVecVecCombinations->end());
    pVecVecCombinations->erase(itRemove, pVecVecCombinations->end());
}

static bool doTest(std::vector<int> &vecNums,
                   std::vector<std::vector<int>> *pVecVecCombinations,
                   int target, Solution &solution)
{
    if (!pVecVecCombinations)
        return false;

    calculateSumCombinationResults(vecNums, pVecVecCombinations, target);
    std::vector<std::vector<int>> ret = solution.fourSum(vecNums, target);
    std::sort(ret.begin(), ret.end());
    if (*pVecVecCombinations != ret)
    {
        std::cout << "Test failed." << std::endl;
        return false;
    }
    return true;
}

static bool doTest(std::initializer_list<int> nums,
                   std::vector<std::vector<int>> *pVecVecCombinations,
                   int target, Solution &solution)
{
    std::vector<int> vecNums(nums);
    return doTest(vecNums, pVecVecCombinations, target, solution);
}

int main()
{
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomCount(4, 10);
    std::uniform_int_distribution<> randomValue(-5, 5);
    std::uniform_int_distribution<> randomSum(-10, 10);
    auto cbRandomValue = std::bind(randomValue, randomEngine);
    Solution solution;
    std::vector<int> vecNums;
    std::vector<std::vector<int>> vecVecCombinations;
    for (int i = 0; i < 10000; ++i)
    {
        auto count = randomCount(randomEngine);
        auto target = randomSum(randomEngine);
        vecNums.clear();
        std::generate_n(std::back_inserter(vecNums), count, cbRandomValue);
        if (!doTest(vecNums, &vecVecCombinations, target, solution))
            break;
    }
    doTest({ 1, 0, -1, 0, -2, 2 }, &vecVecCombinations, 0, solution);
    doTest({ 1 ,-5, 1, -4, 2, 1, -3 }, &vecVecCombinations, 1, solution);
    return 0;
}

#endif
