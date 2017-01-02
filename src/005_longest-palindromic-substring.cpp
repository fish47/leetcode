#include <cstdio>
#include <string>


class Solution
{
private:
    static void extendPalindrome(std::string &str,
                                 int frontIdx, int tailIdx,
                                 int *pIdx, int *pLen)
    {
        int strLen = str.length();
        if (!pIdx || !pLen || frontIdx < 0 || tailIdx >= strLen)
            return;

        int i = frontIdx;
        int j = tailIdx;
        while (i >= 0 && j < strLen && str[i] == str[j])
        {
            --i;
            ++j;
        }

        int len = j - i -1;
        if (len > *pLen)
        {
            *pIdx = i + 1;
            *pLen = j - i - 1;
        }
    }

public:
    std::string longestPalindrome(std::string s)
    {
        int maxIdx = 0;
        int maxLen = 1;
        for (int i = 0, n = s.size(); i < n; ++i)
        {
            extendPalindrome(s, i - 1, i, &maxIdx, &maxLen);
            extendPalindrome(s, i - 1, i + 1, &maxIdx, &maxLen);
        }

        return s.substr(maxIdx, maxLen);
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::string str, std::string expected)
{
    Solution solution;
    std::string ret = solution.longestPalindrome(str);
    if (ret != expected)
        std::printf("Test failed.\n");
}

int main()
{
    doTest("babad", "bab");
    doTest("cbbd", "bb");
    return 0;
}

#endif
