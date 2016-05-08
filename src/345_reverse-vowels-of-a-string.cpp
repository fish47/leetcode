#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>


static const std::string kEnglishVowels("aeiouAEIOU");

class Solution
{
public:
    typedef typename std::string    StringType;

    StringType reverseVowels(StringType str)
    {
        auto i = 0;
        auto j = str.size() - 1;
        while (true)
        {
            auto idx1 = str.find_first_of(kEnglishVowels, i);
            auto idx2 = str.find_last_of(kEnglishVowels, j);
            if (idx1 == StringType::npos || idx2 == StringType::npos)
                break;

            if (idx1 >= idx2)
                break;

            i = idx1 + 1;
            j = idx2 - 1;
            std::swap(str[idx1], str[idx2]);
        }

        return str;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(Solution::StringType str, Solution::StringType assertStr)
{
    Solution solution;
    if (solution.reverseVowels(str) != assertStr)
        std::printf("Test failed: %s\n", str.c_str());
}

int main()
{
    doTest("aeioU", "Uoiea");
    doTest("AAAAAB", "AAAAAB");
    doTest("111A111E", "111E111A");
    doTest("111AO111E", "111EO111A");
    doTest("hello", "holle");
    return 0;
}

#endif
