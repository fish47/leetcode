#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>


class Solution
{
private:
    static const char kSpace                = ' ';
    typedef std::string::size_type          StringPos;
    typedef std::pair<char, std::string>    PatternItem;

    static StringPos skipSpaces(std::string &str, StringPos curPos)
    {
        auto idx = str.find_first_not_of(kSpace, curPos);
        return (idx == std::string::npos) ? str.size() : idx;
    }


public:
    bool wordPattern(std::string patterns, std::string str)
    {
        // 注意前面可能有空格
        auto charIdx = skipSpaces(str, 0);
        auto endCharIdx = str.size();

        auto patternIdx = 0;
        auto endPatternIdx = patterns.size();

        std::vector<PatternItem> vecItems;
        while (charIdx < endCharIdx && patternIdx < endPatternIdx)
        {
            auto spaceIdx = str.find_first_of(kSpace, charIdx);
            if (spaceIdx == std::string::npos)
                spaceIdx = endCharIdx;


            bool hasFoundItem = false;
            char pattern = patterns[patternIdx];
            std::string subString = str.substr(charIdx, spaceIdx - charIdx);
            for (int i = 0, n = vecItems.size(); i < n; ++i)
            {
                PatternItem &item = vecItems[i];
                if (item.first == pattern)
                {
                    if (item.second != subString)
                        return false;

                    hasFoundItem = true;
                    break;
                }

                if (item.second == subString)
                    return false;
            }

            // 没有对应记录
            if (!hasFoundItem)
            {
                vecItems.resize(vecItems.size() + 1);
                PatternItem &item = vecItems.back();
                item.first = pattern;
                item.second = subString;
            }

            // 注意跳过中间的空格
            charIdx = skipSpaces(str, spaceIdx);
            ++patternIdx;
        }


        // 有可能数量上就不对
        return (patternIdx == endPatternIdx && charIdx == endCharIdx);
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::string patterns, std::string str, bool expected)
{
    Solution solution;
    if (solution.wordPattern(patterns, str) != expected)
        std::printf("Test failed.\n");
}

int main()
{
    // sample
    doTest("abba", "dog cat cat dog", true);
    doTest("abba", "dog cat cat fish", false);
    doTest("aaaa", "dog cat cat dog", false);
    doTest("abba", "dog dog dog dog", false);

    // 前后空格
    doTest("a", " 1  ", true);
    doTest("abba", "  1 2 2 1", true);
    doTest("aa", " 1 1 ", true);

    // 模式与字符串不匹对
    doTest("abc", " 1 2 3 4 ", false);
    doTest("abcd", " 1 2 3 ", false);

    return 0;
}

#endif
