#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <functional>
#include <algorithm>


static const char   kLeftParentheses    = '(';
static const char   kRightParentheses   = ')';

static const int    kEnumFlagNone   = 0;
static const int    kEnumFlagAddLP  = 1 << 0;
static const int    kEnumFlagAddRP  = 1 << 1;


class Solution
{
public:
    std::vector<std::string> generateParenthesis(int n)
    {
        std::string buf;
        std::vector<std::string> ret;
        std::vector<int> enumFlags;
        std::vector<int> leftParenthesesCounts;
        std::vector<int> rightParenthesesCounts;

        auto bufLength = n * 2;
        auto writeIdx = 0;
        buf.resize(bufLength);
        enumFlags.push_back(kEnumFlagNone);
        leftParenthesesCounts.push_back(n);
        rightParenthesesCounts.push_back(n);

        while (!leftParenthesesCounts.empty() && !rightParenthesesCounts.empty())
        {
            if (writeIdx == bufLength)
            {
                ret.push_back(buf);
            }
            else
            {
                auto enumFlag = enumFlags.back();
                auto leftParenthesesCount = leftParenthesesCounts.back();
                auto rightParenthesesCount = rightParenthesesCounts.back();

                // 在右括号充足的前提下，左括号想加就加
                if (!(enumFlag & kEnumFlagAddLP) && leftParenthesesCount > 0)
                {
                    buf[writeIdx] = kLeftParentheses;
                    enumFlags.back() |= kEnumFlagAddLP;
                    enumFlags.push_back(kEnumFlagNone);
                    leftParenthesesCounts.push_back(leftParenthesesCount - 1);
                    rightParenthesesCounts.push_back(rightParenthesesCount);
                    ++writeIdx;
                    continue;
                }

                // 右括号不能多加，否则出现类似 ()) 的情况
                if (!(enumFlag & kEnumFlagAddRP) && rightParenthesesCount > leftParenthesesCount)
                {
                    buf[writeIdx] = kRightParentheses;
                    enumFlags.back() |= kEnumFlagAddRP;
                    enumFlags.push_back(kEnumFlagNone);
                    leftParenthesesCounts.push_back(leftParenthesesCount);
                    rightParenthesesCounts.push_back(rightParenthesesCount - 1);
                    ++writeIdx;
                    continue;
                }
            }

            --writeIdx;
            enumFlags.pop_back();
            leftParenthesesCounts.pop_back();
            rightParenthesesCounts.pop_back();
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doEnumerateParentheses(std::string *pBuf,
                                   int pairCount,
                                   int remainingLPCount,
                                   int remainingRPCount,
                                   std::function<void(std::string&)> &func)
{
    if (!pBuf || !func)
        return;

    if (remainingLPCount == 0 && remainingRPCount == 0)
    {
        func(*pBuf);
        return;
    }

    auto writeIdx = pairCount * 2 - remainingLPCount - remainingRPCount;
    if (remainingLPCount > 0)
    {
        (*pBuf)[writeIdx] = kLeftParentheses;
        doEnumerateParentheses(pBuf, pairCount, remainingLPCount - 1, remainingRPCount, func);
    }

    // 不能提前配对左括号
    if (remainingRPCount > 0 && remainingRPCount > remainingLPCount)
    {
        (*pBuf)[writeIdx] = kRightParentheses;
        doEnumerateParentheses(pBuf, pairCount, remainingLPCount, remainingRPCount - 1, func);
    }
}


static void enumerateParentheses(int pairCount, std::function<void(std::string&)> func)
{
    std::string buf;
    buf.resize(pairCount * 2);
    doEnumerateParentheses(&buf, pairCount, pairCount, pairCount, func);
}


int main()
{
    Solution solution;
    std::unordered_set<std::string> set1;
    std::unordered_set<std::string> set2;
    auto cbCollectEnumResults = [&set1](std::string &str) { set1.insert(str); };
    for (auto i = 0; i < 12; ++i)
    {
        set1.clear();
        enumerateParentheses(i, cbCollectEnumResults);

        auto res = solution.generateParenthesis(i);
        set2.clear();
        std::copy(res.cbegin(), res.cend(), std::inserter(set2, set2.begin()));

        if (set1 != set2)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
