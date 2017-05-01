#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <random>


class Solution
{
public:
    int threeSumClosest(std::vector<int> &vecNums, int target)
    {
        if (vecNums.size() < 3)
            return std::accumulate(vecNums.cbegin(), vecNums.cend(), 0);

        int minDelta = std::numeric_limits<int>::max();
        std::sort(vecNums.begin(), vecNums.end());
        for (int i = 1, n = vecNums.size(); i < n; ++i)
        {
            auto b = vecNums[i];
            int front = i - 1;
            int back = i + 1;
            while (front >= 0 && back < n)
            {
                // 注意用绝对值比较差值
                auto delta = vecNums[front] + b + vecNums[back] - target;
                if (std::abs(minDelta) > std::abs(delta))
                    minDelta = delta;

                if (delta == 0)
                    return target;

                // 如果 a + b + c > target ，则 c 值越大差值越大，此时应减小 a 值
                if (delta > 0)
                    --front;
                else
                    ++back;
            }
        }
        return target + minDelta;
    }
};


#ifdef LEETCODE_DEBUG


static int calcuateClosestSum(std::vector<int> vecNums, int target)
{
    if (vecNums.size() < 3)
        return std::accumulate(vecNums.cbegin(), vecNums.cend(), 0);

    int minDelta = std::numeric_limits<int>::max();
    for (int i = 0, n = vecNums.size(); i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            for (int k = j + 1; k < n; ++k)
            {
                int delta = vecNums[i] + vecNums[j] + vecNums[k] - target;
                if (std::abs(minDelta) > std::abs(delta))
                    minDelta = delta;

                if (delta == 0)
                    break;
            }
        }
    }
    return target + minDelta;
}

static void doTest(std::vector<int> *pVecNums, int target)
{
    if (!pVecNums)
        return;

    Solution solution;
    int ret = solution.threeSumClosest(*pVecNums, target);
    int val = calcuateClosestSum(*pVecNums, target);
    int delta1 = std::abs(target - ret);
    int delta2 = std::abs(target - val);
    if (delta1 != delta2)
        std::printf("Test failed.\n");
}

int main()
{
    std::vector<int> vecNums;
    std::mt19937 randomeEngine;
    std::uniform_int_distribution<> randomCount(0, 10);
    std::uniform_int_distribution<> randomValue(-10, 10);
    std::uniform_int_distribution<> randomTarget(-30, 30);
    std::function<int()> cbRandomValue = std::bind(randomValue, std::ref(randomeEngine));
    for (int i = 0; i < 10000; ++i)
    {
        auto count = randomCount(randomeEngine);
        std::generate_n(std::back_inserter(vecNums), count, cbRandomValue);
        for (int j = 0; j < 30; ++j)
        {
            auto target = randomTarget(randomeEngine);
            doTest(&vecNums, target);
        }
        vecNums.clear();
    }
    return 0;
}

#endif
