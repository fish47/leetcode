#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>


static void appendCombination(std::vector<std::vector<int>> *pVecVecNums,
                              int a, int b, int c)
{
    if (!pVecVecNums)
        return;

    pVecVecNums->emplace_back();
    pVecVecNums->back().push_back(a);
    pVecVecNums->back().push_back(b);
    pVecVecNums->back().push_back(c);
}


class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &vecNums)
    {
        std::vector<std::vector<int>> vecVecRet;
        std::sort(vecNums.begin(), vecNums.end());
        for (int i = 0, n = vecNums.size(); i < n - 1; ++i) {
            // 选一个 b 值，那么 a 值在其左侧，而 c 值在其右侧
            auto b = vecNums[i];
            int front = i - 1;
            int back = i + 1;
            while (front >= 0 && back < n)
            {
                auto a = vecNums[front];
                auto c = vecNums[back];
                auto sum = a + c + b;
                if (sum == 0)
                {
                    appendCombination(&vecVecRet, a, b, c);

                    // 相同的 a 值组合情况是一样的，不用再枚举了，下同
                    while (front >= 0 && vecNums[front] == a)
                        --front;
                    while (back >= 0 && vecNums[back] == c)
                        ++back;
                }
                else if (sum > 0)
                {
                    --front;
                }
                else
                {
                    ++back;
                }
            }

            bool check = false;
            while (i + 1 < n && vecNums[i + 1] == b)
            {
                // 还有一种组合是 b b x ，在这里检查一下
                if (!check && i + 2 < n)
                {
                    check = true;
                    auto target = -(b + b);
                    auto it = std::find(vecNums.cbegin() + i + 2, vecNums.cend(), target);
                    if (it != vecNums.cend())
                        appendCombination(&vecVecRet, b, b, target);
                }

                ++i;
            }
        }
        return vecVecRet;
    }
};


#ifdef LEETCODE_DEBUG

static void generateResults(std::vector<int> *pVecNums,
                            std::vector<std::vector<int>> *pVecVecResults)
{
    if (!pVecNums || !pVecVecResults)
        return;

    auto &vecNums = *pVecNums;
    std::sort(vecNums.begin(), vecNums.end());
    for (int i = 0, n = vecNums.size(); i < n; ++i)
    {
        auto a = vecNums[i];
        for (int j = i + 1; j < n; ++j)
        {
            auto b = vecNums[j];
            for (int k = j + 1; k < n; ++k)
            {
                auto c = vecNums[k];
                if (a + b + c == 0)
                    appendCombination(pVecVecResults, a, b, c);
            }
        }
    }

    std::sort(pVecVecResults->begin(), pVecVecResults->end());
    auto itLast = std::unique(pVecVecResults->begin(), pVecVecResults->end());
    pVecVecResults->erase(itLast, pVecVecResults->end());
}

static void compareResults(std::vector<int> *pVecNums,
                           std::vector<std::vector<int>> *pVecVecResults)
{
    Solution solution;
    std::vector<std::vector<int>> vecVecRet = solution.threeSum(*pVecNums);
    std::sort(vecVecRet.begin(), vecVecRet.end());
    generateResults(pVecNums, pVecVecResults);

    if (vecVecRet != *pVecVecResults)
        std::printf("Test failed.\n");
}

static void doTest(std::vector<int> *pVecNums,
                   std::vector<std::vector<int>> *pVecVecResults,
                   std::function<int()> &cbRandomCount,
                   std::function<int()> &cbRandomValue)
{
    if (!pVecNums || !pVecVecResults)
        return;

    auto randomCount = cbRandomCount();
    pVecNums->clear();
    pVecVecResults->clear();
    std::generate_n(std::back_inserter(*pVecNums), randomCount, cbRandomValue);
    compareResults(pVecNums, pVecVecResults);
}

static void doTest(std::vector<int> vecNums)
{
    std::vector<std::vector<int>> vecVecResults;
    compareResults(&vecNums, &vecVecResults);
}

int main()
{
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomCount(3, 6);
    std::uniform_int_distribution<> randomValue(-5, 5);
    std::function<int()> cbRandomCount = std::bind(randomCount, std::ref(randomEngine));
    std::function<int()> cbRandomValue = std::bind(randomValue, std::ref(randomEngine));

    std::vector<int> vecNums;
    std::vector<std::vector<int>> vecVecResults;
    for (int i = 0; i < 10000; ++i)
        doTest(&vecNums, &vecVecResults, cbRandomCount, cbRandomValue);

    doTest({ 0, 0, 0 });
    doTest({ 0, 0, 0, 0 });
    doTest({ -1, 0, 1, 2, -1, -4 });

    return 0;
}

#endif
