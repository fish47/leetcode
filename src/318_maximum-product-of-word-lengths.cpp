#include <iostream>
#include <vector>
#include <string>


static const char   kFirstAlpha     = 'a';

class Solution
{
public:
    int maxProduct(std::vector<std::string> &words)
    {
        auto ret = 0;
        auto wordCount = words.size();
        std::vector<int> alphaBits;
        for (auto i = 0; i < wordCount; ++i)
        {
            // 用 26 bit 记录是否出现过对应的小写字母
            auto bits = 0;
            auto &word = words[i];
            for (auto alpha : word)
                bits |= 1 << (alpha - kFirstAlpha);

            alphaBits.push_back(bits);

            auto wordLenght = word.size();
            for (auto j = 0; j < i; ++j)
            {
                if (alphaBits[j] & bits)
                    continue;

                ret = std::max<int>(ret, wordLenght * words[j].size());
            }
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::vector<std::string> words, int expected)
{
    Solution solution;
    auto ret = solution.maxProduct(words);
    if (ret != expected)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest({ "abcw", "baz", "foo", "bar", "xtfn", "abcdef" }, 16);
    doTest({ "a", "ab", "abc", "d", "cd", "bcd", "abcd" }, 4);
    doTest({ "a", "aa", "aaa", "aaaa" }, 0);
    return 0;
}

#endif
