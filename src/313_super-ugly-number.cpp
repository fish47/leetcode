#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <random>


class Solution
{       
public:
    int nthSuperUglyNumber(int n, std::vector<int> &primes)
    {
        /*
         * 所谓的 Super Ugly Number 其实就是素数的乘积。
         * 以题目数据为例
         * result[0]    = 1     -> 特例
         * result[1]    = 2     -> prime[0]
         * result[2]    = 4     -> result[1] * prime[0]
         * result[3]    = 7     -> prime[1]
         * result[4]    = 8     -> result[2] * prime[0]
         * result[5]    = 13    -> prime[2]
         * result[6]    = 14    -> result[3] * prime[0] | result[1] * prime[1]
         * result[7]    = 16    -> result[4] * prime[0]
         * result[8]    = 19    -> prime[3]
         * result[9]    = 26    -> result[5] * prime[0] | result[1] * prime[2]
         * result[10]   = 28    -> result[6] * prime[0] | result[2] * prime[1]
         * result[11]   = 32    -> result[7] * prime[0]
         */

        struct UglyNumInfo
        {
            int     value;
            int     primeIndex;
            int     resultIndex;

            UglyNumInfo(int val, int primeIdx, int resIdx)
            {
                value = val;
                primeIndex = primeIdx;
                resultIndex = resIdx;
            }

            struct CompareByValueDesc
            {
                bool operator()(const UglyNumInfo &info1, const UglyNumInfo &info2)
                {
                    return info1.value > info2.value;
                }
            };
        };

        if (n <= 1)
            return 1;

        auto primeCount = primes.size();
        std::vector<int> ret(1, 1);
        std::vector<int> indexes(primes.size(), 0);

        typedef UglyNumInfo::CompareByValueDesc QueueComparatorType;
        typedef std::vector<UglyNumInfo>        QueueContainerType;
        std::priority_queue<UglyNumInfo, QueueContainerType, QueueComparatorType> uglyNums;
        for (auto i = 0; i < primeCount; ++i)
            uglyNums.emplace(primes[i], i, 0);

        for (auto i = 1; i < n; ++i)
        {
            auto minUglyNum = uglyNums.top().value;
            ret.push_back(minUglyNum);

            // 重复的不至一个，例如题目数据中的 14
            while (uglyNums.top().value == minUglyNum)
            {
                auto &uglyNum = uglyNums.top();
                auto primeIdx = uglyNum.primeIndex;
                auto resultIdx = uglyNum.resultIndex + 1;
                uglyNums.pop();
                uglyNums.emplace(primes[primeIdx] * ret[resultIdx], primeIdx, resultIdx);
            }
        }

        return ret.back();
    }
};




#ifdef LEETCODE_DEBUG

static bool isPrimeNumber(int val)
{
    if (val == 2)
        return true;

    if (val <= 1 || val % 2 == 0)
        return false;

    // 除了 1 和自身外没有可以整除的数
    auto maxDivisor = static_cast<int>(std::sqrt(val));
    for (auto i = 3; i <= maxDivisor; i += 2)
    {
        if (val % i == 0)
            return false;
    }

    return true;
}


static void collectPrimeNumbers(std::vector<int> *pNums, int count)
{
    if (!pNums)
        return;

    auto num = 1;
    auto &primeNums = *pNums;
    primeNums.clear();
    for (auto i = 0; i < count; ++i)
    {
        while (!isPrimeNumber(num))
            ++num;

        primeNums.push_back(num);
        ++num;
    }
}


static int getSuperUglyNumber(std::vector<int> &primes, int numIdx)
{
    auto num = 0;
    auto primeCount = primes.size();
    for (auto i = 0; i < numIdx; ++i)
    {
        auto testNum = ++num;
        while (testNum != 1)
        {
            bool found = false;
            for (auto j = 0; j < primeCount; ++j)
            {
                auto prime = primes[j];
                if (testNum % prime == 0)
                {
                    found = true;
                    testNum /= prime;
                    break;
                }
            }

            if (!found)
            {
                testNum = ++num;
                continue;
            }
        }
    }

    return num;
}


int main()
{
    Solution solu;
    std::vector<int> p = { 2, 7, 13, 19 };
    solu.nthSuperUglyNumber(12, p);


    Solution solution;
    std::vector<int> uglyNumPrimes;
    std::vector<int> primes;
    collectPrimeNumbers(&primes, 5);

    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomUglyNumIdx(1, 10);
    std::uniform_int_distribution<> randomUglyNumPrimeCount(1, primes.size());
    for (auto i = 0; i < 100; ++i)
    {
        auto uglyNumPrimeCount = randomUglyNumPrimeCount(randomEngine);
        uglyNumPrimes = primes;
        std::random_shuffle(uglyNumPrimes.begin(), uglyNumPrimes.end());
        uglyNumPrimes.erase(uglyNumPrimes.cbegin() + uglyNumPrimeCount, uglyNumPrimes.cend());
        std::sort(uglyNumPrimes.begin(), uglyNumPrimes.end());

        auto uglyNumIdx = randomUglyNumIdx(randomEngine);
        auto ret1 = getSuperUglyNumber(uglyNumPrimes, uglyNumIdx);
        auto ret2 = solution.nthSuperUglyNumber(uglyNumIdx, uglyNumPrimes);
        if (ret1 != ret2)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
