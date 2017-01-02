#include <string>
#include <array>
#include <algorithm>


static const int kPositionNone  = -1;
typedef std::array<int, 256>    AlphaPositionType;

class Solution
{
public:
    int lengthOfLongestSubstring(std::string s)
    {
        int ret = 0;
        int startIdx = 0;
        AlphaPositionType pos;
        pos.fill(kPositionNone);
        for (int i = 0, n = s.size(); i < n; ++i)
        {
            // 例如之前收集到的子串是 abcd ，如果下一个字符是 a ，子串变为 bcda 继续收集
            auto ch = s[i];
            if (pos[ch] == kPositionNone || pos[ch] < startIdx)
                ret = std::max(ret, i - startIdx + 1);
            else
                startIdx = pos[ch] + 1;

            pos[ch] = i;
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::string str, int expected)
{
    Solution solution;
    int ret = solution.lengthOfLongestSubstring(str);
    if (ret != expected)
        std::printf("Test failed.\n");
}


int main()
{
    doTest("abcabcbb", 3);
    doTest("bbbbb", 1);
    doTest("pwwkew", 3);
    doTest("tmmzuxt", 5);
    return 0;
}

#endif
