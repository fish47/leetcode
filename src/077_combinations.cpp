#include <iostream>
#include <vector>
#include <random>


typedef std::vector<int>                NumCombination;
typedef std::vector<NumCombination>     NumCombinations;

class Solution {
public:
    NumCombinations combine(int n, int k)
    {
        NumCombinations ret;
        if (k > n || n < 0 || k < 0)
            return ret;

        NumCombination tmp;
        while (true)
        {
            if (tmp.size() < k)
            {
                auto lastNum = tmp.empty() ? 0 : tmp.back();
                tmp.push_back(lastNum + 1);
            }
            else
            {
                // 加入结果集
                ret.push_back(tmp);

                // 回溯
                while (!tmp.empty())
                {
                    ++tmp.back();

                    // 例如 n = 5  k = 3  tmp = [ 1, 5 ] ，最后一个元素肯定是不合法的
                    auto leftCount = k - tmp.size();
                    if (n - leftCount >= tmp.back())
                        break;

                    tmp.pop_back();
                }

                if (tmp.empty())
                    break;
            }
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doEnumerateNumCombinations(NumCombinations *pCombinations,
                                       NumCombination &tmp,
                                       int leftCount,
                                       int maxNum)
{
    if (leftCount == 0)
    {
        pCombinations->push_back(tmp);
        return;
    }

    auto lastNum = tmp.empty() ? 0 : tmp.back();
    auto curNumStart = lastNum + 1;
    auto enumNumCount = maxNum - lastNum - leftCount + 1;
    for (auto i = 0; i < enumNumCount; ++i)
    {
        tmp.push_back(curNumStart + i);
        doEnumerateNumCombinations(pCombinations, tmp, leftCount - 1, maxNum);
        tmp.pop_back();
    }
}


static void enumerateNumCombinations(NumCombinations *pCombinations, int maxNum, int numCount)
{
    if (!pCombinations || maxNum < 1 || numCount < 0 || numCount > maxNum)
        return;

    NumCombination tmp;
    pCombinations->clear();
    doEnumerateNumCombinations(pCombinations, tmp, numCount, maxNum);
}


int main()
{
    Solution solution;
    NumCombinations combinations;
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomMaxNum(1, 10);
    std::uniform_int_distribution<> randomNumCount(1, 10);
    for (auto i = 0; i < 1000; ++i)
    {
        auto maxNum = randomMaxNum(randomEngine);
        auto numCount = randomNumCount(randomEngine);
        if (numCount > maxNum)
            continue;

        auto ret = solution.combine(maxNum, numCount);
        enumerateNumCombinations(&combinations, maxNum, numCount);
        if (ret != combinations)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
