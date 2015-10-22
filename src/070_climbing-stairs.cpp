#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <memory>


class Solution
{
public:
    int climbStairs(int n)
    {
        // 典型 fibonacii 问题，递归式为 f(n) = f(n-1) + f(n-2)

        if (n < 0)
            return 0;

        int a = 1;
        int b = 0;
        for (int i = 0; i < n; ++i)
        {
            int nextA = a + b;
            b = a;
            a = nextA;
        }

        return a;
    }
};



#ifdef LEETCODE_DEBUG


static int getFibonaciiSum(std::vector<int> *pVecSums, int n)
{
    if (n < 0)
        return 0;

    int ret = pVecSums->at(n);
    if (ret >= 0)
        return ret;

    if (n == 1 || n == 0)
        ret = 1;
    else
        ret = getFibonaciiSum(pVecSums, n - 2) + getFibonaciiSum(pVecSums, n - 1);

    pVecSums->at(n) = ret;
    return ret;
}


int main()
{
    Solution solution;
    std::vector<int> vecSums;
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomNum(0, 10);

    for (int i = 0; i < 1000; ++i)
    {
        int num = randomNum(randomEngine);
        vecSums.resize(num + 1);
        std::fill_n(vecSums.begin(), num + 1, INT_MIN);

        int ret1 = getFibonaciiSum(&vecSums, num);
        int ret2 = solution.climbStairs(num);
        if (ret1 != ret2)
        {
            std::printf("Test failed: n = %d\n", num);
            break;
        }
    }

    return 0;
}

#endif
