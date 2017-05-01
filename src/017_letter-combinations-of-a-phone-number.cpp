#include <cstdio>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <functional>


static const std::array<std::string, 10> kLettersMap =
{
    "",
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz",
};

static const char kDigitCharStart = '0';

static const char kDigitCharEnd = kDigitCharStart + kLettersMap.size();


static bool isLetterDigit(char ch)
{
    return (ch >= kDigitCharStart
            && ch < kDigitCharEnd
            && !kLettersMap[ch - kDigitCharStart].empty());
}

class Solution
{
public:
    std::vector<std::string> letterCombinations(std::string digits)
    {
        std::vector<std::string> vecCombinations;
        auto itRemove = std::remove_if(digits.begin(), digits.end(), std::not1(std::ptr_fun(isLetterDigit)));
        digits.erase(itRemove, digits.cend());
        if (digits.empty())
            return vecCombinations;

        bool exit = false;
        auto n = digits.size();
        std::vector<int> vecEnumIndexes(n, 0);
        while (!exit)
        {
            // 生成对应的字符组合
            vecCombinations.emplace_back();
            auto &combination = vecCombinations.back();
            for (auto i = 0; i < n; ++i)
            {
                auto idx = vecEnumIndexes[i];
                auto digitOffset = digits[i] - kDigitCharStart;
                combination.push_back(kLettersMap[digitOffset][idx]);
            }

            // 末位加一并处理进位
            bool carray = false;
            auto idx = n - 1;
            while (true)
            {
                auto digitOffset = digits[idx] - kDigitCharStart;
                ++vecEnumIndexes[idx];
                carray = (vecEnumIndexes[idx] >= kLettersMap[digitOffset].size());
                if (idx == 0 || !carray)
                    break;

                vecEnumIndexes[idx] = 0;
                --idx;
            }

            // 如果进位溢出，证明枚举完所有组合情况
            exit = carray;
        }
        return vecCombinations;
    }
};


#ifdef LEETCODE_DEBUG

static void doGenerateProductions(std::vector<std::string> &vecCombinations,
                                  std::string &digits,
                                  std::string &prefix,
                                  int startIdx)
{
    if (startIdx >= digits.size())
    {
        if (!prefix.empty())
            vecCombinations.push_back(prefix);
        return;
    }

    auto ch = digits[startIdx];
    if (isLetterDigit(ch))
    {
        const auto &vecLetters = kLettersMap[ch - kDigitCharStart];
        for (int i = 0, m = vecLetters.size(); i < m; ++i)
        {
            prefix.push_back(vecLetters[i]);
            doGenerateProductions(vecCombinations, digits, prefix, startIdx + 1);
            prefix.pop_back();
        }
    }
    else
    {
        doGenerateProductions(vecCombinations, digits, prefix, startIdx + 1);
    }
}

static void generateProductions(std::vector<std::string> &vecCombinations, std::string &digits)
{
    std::string prefix;
    doGenerateProductions(vecCombinations, digits, prefix, 0);
}

int main()
{
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomChar('0', '9');
    std::uniform_int_distribution<> randomCount(0, 5);
    std::string digits;
    std::vector<std::string> vecCombinations;
    Solution solution;
    for (int i = 0; i < 100000; ++i)
    {
        auto count = randomCount(randomEngine);
        for (auto j = 0; j < count; ++j)
        {
            char ch = static_cast<char>(randomChar(randomEngine));
            digits.push_back(ch);
        }

        std::vector<std::string> vecRet = solution.letterCombinations(digits);
        generateProductions(vecCombinations, digits);
        if (vecRet != vecCombinations)
        {
            std::printf("%s\n", digits.c_str());
            std::printf("Test failed.\n");
            break;
        }

        digits.clear();
        vecCombinations.clear();
    }
    return 0;
}

#endif
