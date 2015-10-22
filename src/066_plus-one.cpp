#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>


class Solution
{
public:
    std::vector<int> plusOne(std::vector<int> &vecDigits)
    {
        std::vector<int> vecRet = vecDigits;

        for (int i = vecDigits.size() - 1; i >= 0; --i)
        {
            // 不需要进位
            if (vecRet[i] != 9)
            {
                ++vecRet[i];
                return vecRet;
            }

            // 进位
            vecRet[i] = 0;
        }

        // 最坏的情况，进位使得要多开一个 int 来保存
        vecRet.resize(vecRet.size() + 1);
        std::copy_backward(vecRet.begin(), vecRet.end() - 1, vecRet.end());
        vecRet[0] = 1;
        return vecRet;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> vecDigits,
                   std::vector<int> vecExpected)
{
    Solution solution;
    std::vector<int> vecRet = solution.plusOne(vecDigits);
    if (vecRet != vecExpected)
        std::printf("Test failed.\n");
}

int main()
{
    doTest({ 1, 2, 3 }, { 1, 2, 4 });
    doTest({ 9, 9, 9 }, { 1, 0, 0, 0 });
    return 0;
}

#endif
