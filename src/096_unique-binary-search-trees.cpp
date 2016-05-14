#include <iostream>
#include <vector>


class Solution
{
public:
    int numTrees(int n)
    {
        /*
         * 设 F(i, n) 为以升序第 i (0-based) 个结点为根，包括根结点在内共有 n 个结点，可组成的 BST 个数。
         * F(i, n) = sum { F(j, i) } * sum { F(k, n - i - 1) }
         *
         * 题目结果设为 G(n) = F(0, n) + F(1, n) + ... + F(n - 1, n) 并合并上式即可得到
         * G(n) = sum{ G(i) * G(n - i - 1) }
         *
         * 注意以下性质：
         * 1. 因为是 BST 所以如果选定以 i 作为根，左子树只能放 [0, i) 结点，右子树只能放 [i + 1, n) 结点；
         * 2. 注意 F(i, n) 是个递推式，以 F(1, 3) = F(0, 1) * F(0, 1) 为例，
         *    实际是指以第 1 个结点为根，左子树是第 0 个结点，右子树是第 2 个结点的情况；
         */


        if (n < 0)
            return 1;

        std::vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;

        for (auto i = 2; i <= n; ++i)
        {
            auto productSum = 0;
            for (auto j = 0, m = i - 1; j <= m; ++j)
                productSum += dp[j] * dp[i - j - 1];

            dp[i] = productSum;
        }

        return dp[n];
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(int n, int result)
{
    Solution solution;
    auto ret = solution.numTrees(n);
    if (ret != result)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest(1, 1);
    doTest(2, 2);
    doTest(3, 5);
    doTest(4, 14);
    return 0;
}

#endif
