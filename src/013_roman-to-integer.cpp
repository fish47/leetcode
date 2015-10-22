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
#include <cstring>

static const char kRomanDigits[]    = "IVXLCDM";
static const int kRomanWeights[]    = { 1, 5, 10, 50, 100, 500, 1000 };
static const int kRomanDigitCount   = std::strlen(kRomanDigits);

class Solution
{
public:
    int romanToInt(std::string s)
    {
        int ret = 0;
        int prevWeight = INT_MAX;
        for (int i = 0, n = s.size(); i < n; ++i)
        {
            auto *pDigitEnd = kRomanDigits + kRomanDigitCount;
            auto *pResult = std::find(kRomanDigits, pDigitEnd, s[i]);
            if (pResult >= pDigitEnd)
                continue;


            int weight = kRomanWeights[pResult - kRomanDigits];
            if (weight > prevWeight)
            {
                // 如果下一位比前一位大，有特殊的读法，例如 IV 是读成 4 的
                ret -= prevWeight;
                ret += (weight - prevWeight);
            }
            else
            {
                ret += weight;
            }

            prevWeight = weight;
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::string str, int expected)
{
    Solution solution;
    int ret = solution.romanToInt(str);
    if (ret != expected)
        std::printf("input: %-10s ret: %-5d expected: %d\n", str.c_str(), ret, expected);
}

int main()
{
    doTest("IV", 4);
    doTest("IX", 9);
    doTest("LXXX", 80);
    doTest("XXXIV", 34);
    doTest("VII", 7);
    doTest("MMMCMXCIX", 3999);
    return 0;
}

#endif
