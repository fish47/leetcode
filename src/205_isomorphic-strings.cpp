#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>
#include <string>


int ensureCharID(int *pCharIDBuf, char ch, int *pCharIDCount)
{
    int &charID = pCharIDBuf[ch];
    if (charID >= 0)
        return charID;

    charID = *pCharIDCount;
    ++(*pCharIDCount);
    return charID;
}


class Solution
{
public:
    bool isIsomorphic(std::string s1, std::string s2)
    {
        if (s1.size() != s2.size())
            return false;

        int charIDCount1 = 0;
        int charIDCount2 = 0;
        int charIDs[2][CHAR_MAX - CHAR_MIN];
        int *pCharIDBuf1 = charIDs[0] - CHAR_MIN;
        int *pCharIDBuf2 = charIDs[1] - CHAR_MIN;
        std::memset(charIDs, -1, sizeof(charIDs));

        for (int i = 0, n = s1.size(); i < n; ++i)
        {
            int charID1 = ensureCharID(pCharIDBuf1, s1[i], &charIDCount1);
            int charID2 = ensureCharID(pCharIDBuf2, s2[i], &charIDCount2);
            if (charID1 != charID2)
                return false;
        }

        return true;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::string s1,
                   std::string s2,
                   bool expected)
{
    Solution solution;
    if (solution.isIsomorphic(s1, s2) != expected)
    {
        const char *pCmpStr = expected ? "==" : "!=";
        std::printf("\"%s\" %s \"%s\"\n", s1.c_str(), pCmpStr, s2.c_str());
    }
}


int main()
{
    doTest("", "", true);
    doTest("egg", "add", true);
    doTest("foo", "bar", false);
    doTest("paper", "title", true);
    doTest("aaab", "bbbb", false);
    return 0;
}

#endif
