#include <iostream>
#include <sstream>
#include <ios>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <memory>
#include <functional>
#include <random>


static const char           kOperatorAdd          = '+';
static const char           kOperatorMinus        = '-';
static const char           kOperatorMultiplies   = '*';
static const std::string    kOperatros({ kOperatorAdd, kOperatorMinus, kOperatorMultiplies });

static bool isOperator(char ch)
{
    return kOperatros.find(ch) != decltype(kOperatros)::npos;
}

static int doEvalute(int num1, int num2, char ch)
{
    switch (ch)
    {
        case kOperatorAdd:
            return num1 + num2;
        case kOperatorMinus:
            return num1 - num2;
        case kOperatorMultiplies:
            return num1 * num2;
        default:
            return 0;
    }
}


class Solution {
private:
    static bool splitNumbersAndOperators(std::string &input,
                                         std::vector<int> *pNumbers,
                                         std::vector<char> *pOperators)
    {
        if (!pNumbers || !pOperators)
            return false;

        std::string buf;
        auto &nums = *pNumbers;
        auto &ops = *pOperators;
        nums.clear();
        ops.clear();

        auto itBegin = input.cbegin();
        auto itEnd = input.cend();
        auto it = itBegin;
        auto cbIsDigit = [](char ch) { return std::isdigit(ch); };
        while (it != itEnd)
        {
            // 读数字
            auto nextIt = std::find_if_not(it, itEnd, cbIsDigit);
            if (nextIt == it)
                return false;

            buf.clear();
            buf.append(input, it - itBegin, nextIt - it);
            nums.push_back(std::stoi(buf));

            // 可能读完最后一个数字
            it = nextIt;
            if (it == itEnd)
                break;

            // 读操作符
            auto ch = *it;
            if (!isOperator(ch))
                return false;

            ops.push_back(ch);
            ++it;
        }

        // 排除 1+2+ 这样的情况
        return (nums.size() > 0
                && nums.size() > ops.size()
                && nums.size() - ops.size() == 1);
    }


    static int getResultCombinations(std::vector<int> *pResults,
                                     char op,
                                     int start1, int end1,
                                     int start2, int end2)
    {
        if (!pResults)
            return 0;

        auto &results = *pResults;
        auto orgResultCout = results.size();
        for (auto i = start1; i < end1; ++i)
        {
            auto num = results[i];
            for (auto j = start2; j < end2; ++j)
            {
                auto val = doEvalute(num, results[j], op);
                results.push_back(val);
            }
        }

        return results.size() - orgResultCout;
    }


public:
    std::vector<int> diffWaysToCompute(std::string input)
    {
        std::vector<int> nums;
        std::vector<char> ops;
        std::vector<int> results;
        if (!splitNumbersAndOperators(input, &nums, &ops))
            return results;

        /*
         * 设 f(i, j) 为 [i, j] 范围的数字可以产生的结果集合。
         * f(i, j) = { f(i, p) * f(p + 1, j) }
         */

        typedef std::pair<int, int> ResultRangeType;
        auto numCount = nums.size();
        auto rangeSize = numCount * (numCount + 1) / 2;
        auto getDPValue = [](ResultRangeType *pDP, int firstIdx, int lastIdx) -> ResultRangeType&
        {
            // 只为 firstIdx <= lastIdx 所以数组压缩存储
            auto idx = lastIdx * (lastIdx + 1) / 2 + firstIdx;
            return pDP[idx];
        };

        ResultRangeType *pDP = new ResultRangeType[rangeSize];
        std::unique_ptr<ResultRangeType[]> sp(pDP);

        // 范围内只有一个数字
        for (auto i = 0; i < numCount; ++i)
        {
            ResultRangeType &range = getDPValue(pDP, i, i);
            range.first = results.size();
            range.second = range.first + 1;
            results.push_back(nums[i]);
        }

        for (auto len = 2; len <= numCount; ++len)
        {
            for (auto i = 0; i < numCount; ++i)
            {
                auto firstIdx = i;
                auto lastIdx = i + len - 1;
                if (lastIdx >= numCount)
                    break;

                ResultRangeType &range = getDPValue(pDP, firstIdx, lastIdx);
                range.first = results.size();
                range.second = range.first;
                for (auto p = firstIdx; p < lastIdx; ++p)
                {
                    auto &left = getDPValue(pDP, firstIdx, p);
                    auto &right = getDPValue(pDP, p + 1, lastIdx);
                    range.second += getResultCombinations(&results, ops[p],
                                                          left.first, left.second,
                                                          right.first, right.second);
                }
            }
        }

        ResultRangeType &range = getDPValue(pDP, 0, numCount - 1);
        if (range.first > 0)
        {
            auto itBegin = results.begin();
            std::copy(itBegin + range.first, itBegin + range.second, itBegin);
        }
        results.erase(results.cbegin() + (range.second - range.first), results.cend());
        return results;
    }
};



#ifdef LEETCODE_DEBUG

static std::vector<int> doCalcExpressionResults(std::vector<int> &nums,
                                                std::vector<char> &ops,
                                                int firstNumIdx,
                                                int lastNumIdx)
{
    std::vector<int> ret;
    if (firstNumIdx == lastNumIdx)
    {
        ret.push_back(nums[firstNumIdx]);
    }
    else if (firstNumIdx + 1 == lastNumIdx)
    {
        auto val = doEvalute(nums[firstNumIdx], nums[lastNumIdx], ops[firstNumIdx]);
        ret.push_back(val);
    }
    else
    {
        for (auto idx = firstNumIdx; idx < lastNumIdx; ++idx)
        {
            auto op = ops[idx];
            auto results1 = doCalcExpressionResults(nums, ops, firstNumIdx, idx);
            auto results2 = doCalcExpressionResults(nums, ops, idx + 1, lastNumIdx);
            for (auto num1 : results1)
            {
                for (auto num2 : results2)
                {
                    auto val = doEvalute(num1, num2, op);
                    ret.push_back(val);
                }
            }
        }
    }

    return ret;
}


static void calcExpressionResults(std::vector<int> *pResults, std::string input)
{
    if (!pResults)
        return;

    pResults->clear();

    std::vector<int> nums;
    std::vector<char> ops;
    std::stringstream ss(input);
    while (ss)
    {
        int num;
        ss >> num;
        if (!ss)
            break;

        nums.push_back(num);

        char ch;
        ss >> ch;
        if (!ss || !isOperator(ch))
            break;

        ops.push_back(ch);
    }

    if (!ss.eof() || nums.size() <= 0 || nums.size() <= ops.size())
        return;

    *pResults = doCalcExpressionResults(nums, ops, 0, nums.size() - 1);
}


static void createRandomExpression(std::string *pOutString,
                                   int numCount,
                                   std::function<int()> &randomNum,
                                   std::function<int()> &randomOpIdx)
{
    if (!pOutString || !randomNum || !randomNum || numCount <= 0)
        return;

    auto &str = *pOutString;
    str.clear();

    str.append(std::to_string(randomNum()));
    for (auto i = 1; i < numCount; ++i)
    {
        auto ch = kOperatros[randomOpIdx()];
        str.push_back(ch);
        str.append(std::to_string(randomNum()));
    }
}


int main()
{
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomNumCount(1, 10);
    std::uniform_int_distribution<> randomNumValue(1, 30);
    std::uniform_int_distribution<> randomOpIndex(0, kOperatros.size() - 1);
    std::function<int()> cbRandomNumVal = std::bind(randomNumValue, randomEngine);
    std::function<int()> cbRandomOpIdx = std::bind(randomOpIndex, randomEngine);

    Solution solution;
    std::vector<int> results;
    std::string expression;

    for (auto i = 0; i < 1000; ++i)
    {
        auto numCount = randomNumCount(randomEngine);
        createRandomExpression(&expression, numCount, cbRandomNumVal, cbRandomOpIdx);
        auto ret = solution.diffWaysToCompute(expression);
        calcExpressionResults(&results, expression);
        std::sort(results.begin(), results.end());
        std::sort(ret.begin(), ret.end());
        if (ret != results)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }

    return 0;
}

#endif
