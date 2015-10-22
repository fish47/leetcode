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



class Solution
{
public:
    bool isAnagram(std::string s, std::string t)
    {
        if (s.size() != t.size())
            return false;

        // 就是这么简单囧囧囧囧
        std::string str1(s);
        std::string str2(t);
        std::sort(str1.begin(), str1.end());
        std::sort(str2.begin(), str2.end());
        return (str1 == str2);
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::string s1, std::string s2, bool expected)
{
    Solution solution;
    if (solution.isAnagram(s1, s2) != expected)
        std::printf("Test failed.\n");
}

int main()
{
    doTest("123", "321", true);
    doTest("12", "34", false);
    doTest("11", "1", false);
    doTest("11", "11", true);
    return 0;
}

#endif
