#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>
#include <vector>


class Solution
{
public:
    int countPrimes(int n)
    {
        bool *pIsPrimeNums = new bool[n];
        std::memset(pIsPrimeNums, 1, n * sizeof(bool));
        pIsPrimeNums[0] = false;
        pIsPrimeNums[1] = false;

        for (int i = 2; i * i < n; ++i)
        {
            if (!pIsPrimeNums[i])
                continue;

            for (int j = i * i; j < n; j += i)
                pIsPrimeNums[j] = false;
        }

        int ret = 0;
        for (int i = 0; i < n; ++i)
            ret += pIsPrimeNums[i];

        delete[] pIsPrimeNums;
        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static bool isPrimeNumber(int n)
{
    if (n <= 1)
        return false;

    if (n <= 3)
        return true;

    if (n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; ++i)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}


int main()
{
    std::vector<int> vecPrimeNumbers;
    for (int i = 1; i < 100000; ++i)
    {
        if (isPrimeNumber(i))
            vecPrimeNumbers.push_back(i);
    }

    Solution solution;
    for (int i = 0, n = vecPrimeNumbers.size(); i < n; ++i)
    {
        int primeNumCount = solution.countPrimes(vecPrimeNumbers[i] + 1);
        if (primeNumCount != i + 1)
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
