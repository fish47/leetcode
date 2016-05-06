#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>

class Solution
{
public:
    std::string reverseString(std::string s)
    {
        std::string ret;
        auto it = s.crbegin();
        while (it != s.crend())
        {
            ret.push_back(*it);
            ++it;
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::string s1, std::string s2)
{
    Solution solution;
    std::string ret = solution.reverseString(s1);
    if (ret != s2)
        std::printf("Test failed.\n");
}

int main()
{
    doTest("", "");
    doTest("a", "a");
    doTest("abc", "cba");
    return 0;
}

#endif
