#include <iostream>
#include <cmath>

class Solution
{
public:
    int bulbSwitch(int n)
    {
        /*
         * https://leetcode.com/discuss/91371/share-my-o-1-solution-with-explanation
         *
         * 假设 n = 6
         * 第 1 个灯泡被第 1 轮操作 toggle ；
         * 第 4 个灯泡被第 1 / 2 / 4 轮操作 toggle ；
         * 第 6 个灯泡被第 1 / 2 / 3 / 6 轮操作 toogle ；
         *
         * 第 i (1-based) 个灯泡是否被点亮取决于是在 [1, n] 中有多少个可以被整除的数。
         * 除了 1 和 平方数，在 [1, i] 都只有偶数个可被整除的数，因为都是配对出现，以 6 为例有 (1, 6) / (2, 3) 。
         * 其实当 i 是平方数时灯炮才会亮，最后变成间接统计 [1, n] 有多少个平方数。
         */

        return std::sqrt(n);
    }
};
