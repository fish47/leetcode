#include <iostream>
#include <vector>
#include <cmath>


typedef std::vector<int>                NumCombination;
typedef std::vector<NumCombination>     NumCombinations;

static const int    kMinSplitNumber     = 1;
static const int    kMaxSplitNumber     = 9;

class Solution
{
private:
    static const int    kNoSplitNumber          = -1;
    static const int    kFirstPrevSplitNumber   = kMinSplitNumber - 1;

private:
    static int getSequenceSum(int first, int count)
    {
        if (count <= 0)
            return 0;

        auto average = (first + first + count - 1) * 0.5;
        return static_cast<int>(average * count);
    }

    static int getMinSplitNumber(int num, int splitCount, int prevSplit)
    {
        // 分割数是递增的，例如 7 = 1 + 5 + 1 就是不合法的分割
        auto ret1 = prevSplit + 1;
        if (getSequenceSum(ret1, splitCount) > num)
            return kNoSplitNumber;

        // 如果后面分割都取最大值，当前分割就是最小值了
        // num = ret + ... + (kMaxSplitNumber - 1) + kMaxSplitNumber
        int remainingSplitCount = splitCount - 1;
        auto sequenceStart = kMaxSplitNumber - (remainingSplitCount - 1);
        auto trailingSeqSum = (remainingSplitCount > 0) ? getSequenceSum(sequenceStart, remainingSplitCount) : 0;
        auto ret2 = num - trailingSeqSum;

        return std::max(ret1, ret2);
    }

    static int getMaxSplitNumber(int num, int splitCount, int prevSplit)
    {
        // num = (ret) + (ret + 1) + ... + (ret + splitCount - 1)
        // num = (ret + ret + splitCount - 1) / 2 * splitCount
        float split = (num - 0.5 + splitCount * 0.5 ) / splitCount;
        if (split < prevSplit + 1)
            return kNoSplitNumber;

        auto ret = std::ceil(split);
        if (ret > kMaxSplitNumber)
            return kNoSplitNumber;

        return ret;
    }


public:
    NumCombinations combinationSum3(int k, int n)
    {
        NumCombinations ret;
        if (k < kMinSplitNumber || k > kMaxSplitNumber)
            return ret;

        if (n < getSequenceSum(kMinSplitNumber, k))
            return ret;

        if (n > getSequenceSum(kMaxSplitNumber - (k - 1), k))
            return ret;


        auto firstMinSplit = getMinSplitNumber(n, k, kFirstPrevSplitNumber);
        auto leftNum = n - firstMinSplit;
        auto leftSplitCount = k - 1;
        NumCombination combination;
        combination.push_back(firstMinSplit);

        while (true)
        {
            if (leftSplitCount == 0)
            {
                if (leftNum == 0)
                    ret.push_back(combination);
            }
            else
            {
                auto prevSplit = combination.empty() ? kFirstPrevSplitNumber : combination.back();
                auto nextMinSplit = getMinSplitNumber(leftNum, leftSplitCount, prevSplit);
                if (nextMinSplit != kNoSplitNumber)
                {
                    --leftSplitCount;
                    leftNum -= nextMinSplit;
                    combination.push_back(nextMinSplit);
                    continue;
                }
            }

            // 回退到下一个合法的枚举状态
            while (true)
            {
                ++leftSplitCount;
                leftNum += combination.back();
                combination.pop_back();

                // 特别注意只切割一份的情况
                if (combination.empty())
                    break;

                int prevSplitIdx = combination.size() - 2;
                auto prevSplit = (prevSplitIdx >= 0) ? combination[prevSplitIdx] : kFirstPrevSplitNumber;
                auto num = leftNum + combination.back();
                auto count = leftSplitCount + 1;
                auto curSplit = ++combination.back();
                auto maxSplit = getMaxSplitNumber(num, count, prevSplit);
                if (maxSplit != kNoSplitNumber && curSplit <= maxSplit)
                {
                    --leftNum;
                    break;
                }
            }

            if (combination.empty())
                break;
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static void doCalcNumCombinations(NumCombinations &combs, NumCombination &tmp, int num, int splitCount)
{
    if (splitCount < 0)
        return;

    if (splitCount == 0)
    {
        if (num == 0)
            combs.push_back(tmp);

        return;
    }

    int prevSplitIdx = tmp.size() - splitCount - 1;
    auto prevSplit = (prevSplitIdx >= 0) ? tmp[prevSplitIdx] : kMinSplitNumber - 1;
    auto minSplit = std::max(kMinSplitNumber, prevSplit + 1);
    for (auto split = minSplit; split <= kMaxSplitNumber; ++split)
    {
        auto idx = tmp.size() - splitCount;
        tmp[idx] = split;
        doCalcNumCombinations(combs, tmp, num - split, splitCount - 1);
    }
}


static void calcNumCombinations(int num, int splitCount, NumCombinations *pCombs)
{
    if (!pCombs || splitCount <= 0)
        return;

    if (num > splitCount * kMaxSplitNumber || num < splitCount * kMinSplitNumber)
        return;

    NumCombination combination;
    combination.resize(splitCount);
    doCalcNumCombinations(*pCombs, combination, num, splitCount);
}


int main()
{
    Solution solution;
    NumCombinations combinations;
    for (auto i = 1; i <= 9; ++i)
    {
        bool failed = false;
        for (auto j = 1; j <= 81; ++j)
        {
            auto ret = solution.combinationSum3(i, j);
            combinations.clear();
            calcNumCombinations(j, i, &combinations);
            if (ret != combinations)
            {
                failed = true;
                break;
            }
        }

        if (failed)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
