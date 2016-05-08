#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <random>

class NumArray
{
private:
    std::vector<int>    m_vecSums;

public:
    NumArray(std::vector<int> &vecNums)
    {
        auto numSum = 0;
        for (auto it = vecNums.cbegin(); it != vecNums.cend(); ++it)
        {
            m_vecSums.push_back(numSum);
            numSum += *it;
        }
        m_vecSums.push_back(numSum);
    }

    int sumRange(int i, int j)
    {
        if (i > j)
            std::swap(i, j);

        if (i >= 0 && i < m_vecSums.size() && j >=0 && j < m_vecSums.size())
        {
            int sum1 = m_vecSums[i];
            int sum2 = m_vecSums[j + 1];
            return sum2 - sum1;
        }

        return 0;
    }
};



#ifdef LEETCODE_DEBUG

int main()
{
    std::vector<int> vecNums;
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomNumCount(0, 1000);
    std::uniform_int_distribution<> randomValue(-1000, 1000);
    auto cbGetNumValue = [&randomEngine, &randomValue]() { return randomValue(randomEngine); };
    for (int i = 0; i < 1000; ++i)
    {
        vecNums.clear();
        std::generate_n(std::back_inserter(vecNums), randomNumCount(randomEngine), cbGetNumValue);

        bool succeed = true;
        std::uniform_int_distribution<> randomIndex(0, vecNums.size() - 1);
        NumArray numArray(vecNums);
        for (int j = 0; j < 1000; ++j)
        {
            int startIdx = randomIndex(randomEngine);
            int lastIdx = randomIndex(randomEngine);
            if (startIdx > lastIdx)
                std::swap(startIdx, lastIdx);

            int assertSumVal = std::accumulate(vecNums.cbegin() + startIdx, vecNums.cbegin() + (lastIdx + 1), 0);
            if (assertSumVal != numArray.sumRange(startIdx, lastIdx))
            {
                succeed = false;
                std::printf("Test failed.\n");
                break;
            }
        }

        if (!succeed)
            break;
    }
    return 0;
}

#endif
