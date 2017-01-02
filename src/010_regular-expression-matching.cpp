#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

class Solution
{
private:
    class RegexPiece
    {
    private:
        char    m_chPieceChar;
        char    m_chQuantity;

    public:
        static const char kCharWildCard     = '.';
        static const char kCharQuantityN    = '*';

    private:
        static const char kQuantityNormalN      = -1;
        static const char kQuantityNormalOne    = -2;
        static const char kQuantityWildCardN    = -3;
        static const char kQuantityWildCardOne  = -4;

    public:
        static RegexPiece createNormalRegexPiece(char ch, bool isQuantityN)
        {
            RegexPiece p;
            p.m_chPieceChar = ch;
            p.m_chQuantity = isQuantityN ? kQuantityNormalN : kQuantityNormalOne;
            return p;
        }

        static RegexPiece createWildCardRegexPiece(bool isQuantityN)
        {
            RegexPiece p;
            p.m_chPieceChar = 0;
            p.m_chQuantity = isQuantityN ? kQuantityWildCardN : kQuantityWildCardOne;
            return p;
        }

        bool isCharMatched(char c) const
        {
            switch (m_chQuantity)
            {
                case kQuantityWildCardN:
                case kQuantityWildCardOne:
                    return true;

                case kQuantityNormalN:
                case kQuantityNormalOne:
                    return (c == m_chPieceChar);
            }
            return false;
        }

        bool isQuantityN() const
        {
            return (m_chQuantity == kQuantityNormalN || m_chQuantity == kQuantityWildCardN);
        }
    };


    static void doCommitRegexPiece(std::vector<RegexPiece> *pVecPieces,
                                   char ch,
                                   bool *pHasChar,
                                   bool *pIsWildCard,
                                   bool *pIsQuantityN)
    {
        if (!pVecPieces || !pHasChar || !pIsWildCard || !pIsQuantityN)
            return;

        if (!*pHasChar)
            return;

        if (*pIsWildCard)
            pVecPieces->push_back(RegexPiece::createWildCardRegexPiece(*pIsQuantityN));
        else
            pVecPieces->push_back(RegexPiece::createNormalRegexPiece(ch, *pIsQuantityN));

        *pHasChar = false;
        *pIsWildCard = false;
        *pIsQuantityN = false;
    }


    static std::vector<RegexPiece> parseRegexPieces(std::string &pattern)
    {
        char ch = 0;
        bool hasChar = false;
        bool isWildCard = false;
        bool isQuantityN = false;
        std::vector<RegexPiece> vecPieces;
        for (int i = 0, n = pattern.size(); i < n; ++i)
        {
            char c = pattern[i];
            if (c == RegexPiece::kCharQuantityN)
            {
                isQuantityN = true;
            }
            else if (c == RegexPiece::kCharWildCard)
            {
                doCommitRegexPiece(&vecPieces, ch, &hasChar, &isWildCard, &isQuantityN);
                isWildCard = true;
                hasChar = true;
            }
            else
            {
                doCommitRegexPiece(&vecPieces, ch, &hasChar, &isWildCard, &isQuantityN);
                ch = c;
                hasChar = true;
            }
        }

        doCommitRegexPiece(&vecPieces, ch, &hasChar, &isWildCard, &isQuantityN);
        return vecPieces;
    }


public:
    bool isMatch(std::string s, std::string p)
    {
        std::vector<RegexPiece> vecPieces = parseRegexPieces(p);
        if (s.empty() && vecPieces.empty())
            return true;

        if (s.empty())
        {
            return std::all_of(vecPieces.cbegin(),
                               vecPieces.cend(),
                               std::bind(&RegexPiece::isQuantityN, std::placeholders::_1));
        }

        if (vecPieces.empty())
            return false;

        // 设 f(i, j) 为字符串 s[i:] 是否匹配模式 p[j:]
        int rowCount = s.size();
        int colCount = vecPieces.size();
        std::vector<bool> vecCurDPValues(colCount, false);
        std::vector<bool> vecNextDPValues(colCount, false);

        // 初值计算是简化版的状态推导，只考虑一个字符能否匹配 n 个模式
        for (int i = colCount - 1; i >= 0; --i)
        {
            RegexPiece &piece = vecPieces[i];
            vecNextDPValues[i] = piece.isCharMatched(s.back());
            if (!piece.isQuantityN())
                break;
        }

        for (int i = rowCount - 1; i >= 0; --i)
        {
            vecCurDPValues.swap(vecNextDPValues);
            std::fill(vecNextDPValues.begin(), vecNextDPValues.end(), false);

            for (int j = colCount - 1; j >= 0; --j)
            {
                if (!vecCurDPValues[j])
                    continue;

                // f(i, j) -> f(i, j - 1)
                // "aa" "aa" -> "aa" "a*aa"
                if (j > 0 && vecPieces[j - 1].isQuantityN())
                    vecCurDPValues[j - 1] = true;

                // f(i, j) -> f(i - 1, j)
                // "ab" "a*b" -> "aab" "a*b"
                if (i > 0 && vecPieces[j].isQuantityN() && vecPieces[j].isCharMatched(s[i - 1]))
                    vecNextDPValues[j] = true;

                // f(i, j) -> f(i - 1, j - 1)
                // "ab" "ab" -> "cab" "cab"
                if (i > 0 && j > 0 && vecPieces[j - 1].isCharMatched(s[i - 1]))
                    vecNextDPValues[j - 1] = true;
            }
        }

        return vecCurDPValues.front();
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::string str, std::string pattern, bool expected)
{
    Solution solution;
    bool val = solution.isMatch(str, pattern);
    if (val != expected)
        std::printf("\"%s\" \"%s\" %d\n", str.c_str(), pattern.c_str(), expected);
}

int main()
{
    doTest("", "", true);
    doTest("", ".*", true);
    doTest("a", "", false);
    doTest("aa", "a", false);
    doTest("aa", "aa", true);
    doTest("aaa", "aa", false);
    doTest("aa", "a*", true);
    doTest("aa", ".*", true);
    doTest("ab", ".*", true);
    doTest("aab", "c*a*b", true);
    doTest("aaa", "a.a", true);
    doTest("abc", "a*b*c*.*", true);
    doTest("abc", "a*b*c.*", true);
    doTest("abc", "a*b*c.*.", false);
    doTest("abcd", "d*", false);
    doTest("aaa", "ab*ac*a", true);
    doTest("abc", "5*6*ab*1*2*3*c*", true);
    return 0;
}

#endif
