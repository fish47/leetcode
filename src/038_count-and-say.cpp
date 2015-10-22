#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <string>


static void doCountAndSay(std::string &strDigits,
                          std::string &strCountAndSay,
                          char *pBuf)
{
    strCountAndSay.clear();
    if (strDigits.empty())
        return;

    int digitCount = 1;
    char curDigit = strDigits[0];
    for (int i = 1, n = strDigits.size(); i <= n; ++i)
    {
        // 题目规定数才是有效内容
        char digit = (i == n) ? '\0' : strDigits[i];
        digitCount += (digit == curDigit);

        // 遇到不连结相同，或已经遍历完字符串
        if (digit != curDigit)
        {
            int bufLen = std::sprintf(pBuf, "%d%c", digitCount, curDigit);
            if (bufLen > 0)
                strCountAndSay.append(pBuf, bufLen);

            // 计数复位
            curDigit = digit;
            digitCount = 1;
        }
    }
}


class Solution
{
public:
    std::string countAndSay(int n)
    {
        if (n <= 0)
            return "";

        char buf[1024];
        std::string strDigits = "1";
        std::string strCountAndSay = strDigits;

        for (int i = 1; i < n; ++i)
        {
            strDigits.swap(strCountAndSay);
            doCountAndSay(strDigits, strCountAndSay, buf);
        }

        return strCountAndSay;
    }
};


#ifdef LEETCODE_DEBUG


static void doTest(std::string strDigits,
                   std::string strExpected)
{
    char buf[1024];
    std::string strRet;

    doCountAndSay(strDigits, strRet, buf);
    if (strRet != strExpected)
    {
        std::printf("str: %-20s expected: %-20s\n",
                    strDigits.c_str(),
                    strExpected.c_str());
    }
}


int main()
{
    doTest("1", "11");
    doTest("11", "21");
    doTest("21", "1211");
    doTest("1211", "111221");
    doTest("111221", "312211");
    return 0;
}

#endif
