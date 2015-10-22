#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <list>
#include <deque>


using namespace std;


static char seekNextAlphabetOrDigitChar(string &s, int *pInOutIdx, int step)
{
    int strLen = s.size();
    while (*pInOutIdx >= 0 && *pInOutIdx < strLen)
    {
        char ch = s[*pInOutIdx];
        if (isalnum(ch))
            return ch;

        (*pInOutIdx) += step;
    }

    return '\0';
}

class Solution
{
public:
    bool isPalindrome(string s)
    {
        int startIdx = 0;
        int lastIdx = s.size() - 1;

        while (true)
        {
            char ch1 = seekNextAlphabetOrDigitChar(s, &startIdx, 1);
            char ch2 = seekNextAlphabetOrDigitChar(s, &lastIdx, -1);

            if (startIdx > lastIdx)
                break;

            if (toupper(ch1) != toupper(ch2))
                return false;

            ++startIdx;
            --lastIdx;
        }

        return true;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(const char *charArray, bool val)
{
    string str(charArray);
    Solution solution;
    bool output = solution.isPalindrome(str);
    if (output != val)
    {
        cout << "String: " << str << endl;
        cout << "Output: " << output << endl;
        cout << "Correct: " << val << endl;
    }
}


int main()
{
    doTest("A man, a plan, a canal: Panama", true);
    doTest("race a car", false);
    doTest("A ,.,.,.A", true);
    doTest("..B  . .A ,. B...", true);
    return 0;
}

#endif
