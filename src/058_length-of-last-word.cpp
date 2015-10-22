#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <string>


class Solution
{
public:
    int lengthOfLastWord(std::string s)
    {
        // 跳过后缀空格
        auto cbIsSpace = [](const char &ch) { return std::isspace(ch); };
        auto itEnd = s.crend();
        auto itFirstNonSpace = std::find_if_not(s.crbegin(), itEnd, cbIsSpace);

        // 全都是空格
        if (itFirstNonSpace == itEnd)
            return 0;

        // 向前找第一个空格
        auto it = std::find_if(itFirstNonSpace, itEnd, cbIsSpace);
        return (it - itFirstNonSpace);
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::string s, int expected)
{
    Solution solution;
    int ret = solution.lengthOfLastWord(s);
    if (ret != expected)
        std::printf("Test failed.\n");
}

int main()
{
    doTest("      ", 0);
    doTest("11 123456", 6);
    doTest("   1 123   ", 3);
    doTest("123   ", 3);
    return 0;
}

#endif
