#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <string>


class Solution
{
public:
    int strStr(std::string strHaystack, std::string strNeedle)
    {
        int haystackSize = strHaystack.size();
        int needleSize = strNeedle.size();
        if (needleSize > haystackSize)
            return -1;

        auto itHaystack = strHaystack.cbegin();
        auto itHaystackEnd = itHaystack + haystackSize - needleSize + 1;
        auto itNeedle = strNeedle.cbegin();
        auto itNeedleEnd = strNeedle.cend();

        while (itHaystack != itHaystackEnd)
        {
            if (std::equal(itNeedle, itNeedleEnd, itHaystack))
                return itHaystack - strHaystack.cbegin();

            ++itHaystack;
        }


        return -1;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::string strHaystack,
                   std::string strNeedle,
                   int expected)
{
    Solution solution;
    int ret = solution.strStr(strHaystack, strNeedle);
    if (ret != expected)
        std::printf("Test failed.\n");
}


int main()
{
    doTest("1", "1111", -1);
    doTest("12345", "45", 3);
    doTest("12345", "12345", 0);
    doTest("12312345", "12345", 3);
    doTest("12312345", "1234", 3);
    return 0;
}

#endif
