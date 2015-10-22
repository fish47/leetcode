#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <string>


class Solution
{
public:
    bool isValid(std::string s)
    {
        auto it = s.cbegin();
        auto itEnd = s.cend();
        std::vector<char> vecChars;
        while (it != itEnd)
        {
            char ch = *it;
            char expectedPrevCh = 0;

            switch (ch)
            {
                case '(':
                case '{':
                case '[':
                    expectedPrevCh = 0;
                    vecChars.push_back(ch);
                    break;

                case ')':
                    expectedPrevCh = '(';
                    break;
                case '}':
                    expectedPrevCh = '{';
                    break;
                case ']':
                    expectedPrevCh = '[';
                    break;

                // 混进什么奇怪字符了
                default:
                    return false;
            }

            if (expectedPrevCh > 0)
            {
                if (vecChars.empty())
                    return false;

                char prev = vecChars.back();
                if (prev != expectedPrevCh)
                    return false;

                vecChars.pop_back();
            }

            ++it;
        }

        return vecChars.empty();
    }
};



#ifdef LEETCODE_DEBUG

static bool doTest(std::string s, bool expected)
{
    Solution solution;
    if (solution.isValid(s) != expected)
        std::printf("Test failed.\n");
}


int main()
{
    doTest("", true);
    doTest("[]{}()", true);
    doTest("[{}()]", true);
    doTest("[", false);
    doTest("]", false);
    doTest("[()", false);
    doTest("[{}()]]", false);
    return 0;
}

#endif
