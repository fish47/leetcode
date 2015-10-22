#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>


using namespace std;


class Solution
{
public:
    int trailingZeroes(int n)
    {
        /*
         * 因为只有 2 * 5 才会出现零，所以要统计 1 ~ n 有多少个 2 和 5 的倍数。
         * 2 的倍数出现次数非常多，因为双数就有 2 ，肯定比 5 的倍数多，所以只统计后者。
         * 5 的倍数只会是 5 / 10 / 15 / 20 / .... ，出现间隔是 5 。
         *
         * 还要考虑 5^2 / 5^3 / 5^4 / 5^5 ... 之类有多个 5 的数。
         *
         * 5 / 10 / 15 相隔 5 的数，一定有 1 个 5 ，
         * 5^2 / 5^3 / 5^4 相隔 5^2 的数，本身又比 5 / 10 / 15 之类多 1 个 5
         * 5^3 / 5^5 / 5^7 相隔 5^3 的数，本身至少有 3 个 5 ，
         * 如此类推...
         *
         * 第一轮考察有多少个 5 的倍数，
         * 第二轮考察有多少个 25 的倍数，
         * 第三轮考察有多少个 5^3 的倍数，
         * 如此类推...
         */

        int res = 0;
        while (n)
        {
            res += n / 5;
            n /= 5;
        }
        return res;
    }
};


#ifdef LEETCODE_DEBUG

static int getPrime5Count(int n)
{
    int res = 0;
    while (n % 5 == 0)
    {
        ++res;
        n /= 5;
    }
    return res;
}


int main()
{
    Solution solution;

    for (int iter_num = 0; iter_num < 10000; ++iter_num)
    {
        int correct = 0;
        for (int i = 1; i <= iter_num; ++i)
            correct += getPrime5Count(i);

        int cmp = solution.trailingZeroes(iter_num);
        if (cmp != correct)
        {
            printf("Bang!\n");
            printf("num=%d\nresult=%d correct=%d\n", iter_num, cmp, correct);
            break;
        }
    }

    return 0;
}

#endif
