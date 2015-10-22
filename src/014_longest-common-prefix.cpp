#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>

class Solution
{
public:
    std::string longestCommonPrefix(std::vector<std::string> &vecStrings)
    {
        if (vecStrings.empty())
            return "";

        int iPrefixIdx = 0;
        std::string strRet;
        while (true)
        {
            std::string &strFirst = vecStrings[0];
            if (strFirst.size() <= iPrefixIdx)
                break;

            // 假设第一个字符是前缀
            // 只要其他字符串的对应位置不是这个字符，就不算前缀
            char ch = strFirst[iPrefixIdx];
            bool bIsPrefixChar = true;

            for (int i = 1, n = vecStrings.size(); i < n; ++i)
            {
                std::string &strIter = vecStrings[i];
                if (strIter.size() <= iPrefixIdx || strIter[iPrefixIdx] != ch)
                {
                    bIsPrefixChar = false;
                    break;
                }
            }


            if (!bIsPrefixChar)
                break;

            strRet.push_back(vecStrings[0][iPrefixIdx]);
            ++iPrefixIdx;
        }

        return strRet;
    }
};


#ifdef LEETCODE_DEBUG


static void doTest(std::vector<std::string> vecStrings,
                   std::string strExpected)
{
    Solution solution;
    std::string strRet = solution.longestCommonPrefix(vecStrings);
    if (strRet != strExpected)
        std::printf("Test failed.\n");
}


int main()
{
    doTest({
               "aa",
               "a",
               "b"
           },
           "");

    doTest({
               "aa",
               "a",
               "abb"
           },
           "a");

    doTest({
               "aaaaab",
               "aaa",
               "aaaaaaaaabb"
           },
           "aaa");

    return 0;
}

#endif
