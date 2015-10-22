#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>


using namespace std;


class Solution
{
public:
    vector<int> getRow(int rowIndex)
    {
        vector<int> nums;
        nums.push_back(1);

        for (int i = 1; i <= rowIndex; ++i)
        {
            // 除了首尾的其他元素都遵守以下公式
            // f(x, y) = f(x, y - 1) + f(x - 1, y - 1)
            int prevNum = nums[0];
            for (int j = 1, sumEndIdx = i; j < sumEndIdx; ++j)
            {
                int prevNumBak = prevNum;
                prevNum = nums[j];
                nums[j] += prevNumBak;
            }

            nums.push_back(1);
        }

        return nums;
    }
};



#ifdef LEETCODE_DEBUG

static const int TESTCASE_DATA[][20] =
{
    { 1, 0 },
    { 1, 1, 0 },
    { 1, 2, 1, 0 },
    { 1, 3, 3, 1, 0 },
    { 1, 4, 6, 4, 1, 0 },
    { 1, 5, 10, 10, 5, 1, 0 },
    { 1, 6, 15, 20, 15, 6, 1, 0 },
    { 1, 7, 21, 35, 35, 21, 7, 1, 0 },
    { 1, 8, 28, 56, 70, 56, 28, 8, 1, 0 },
    { 1, 9, 36, 84, 126, 126, 84, 36, 9, 1, 0 },
    { 0 },
};


int main()
{
    Solution solution;

    for (int rowIdx = 0; TESTCASE_DATA[rowIdx][0] > 0; ++rowIdx)
    {
        vector<int> output = solution.getRow(rowIdx);
        const int *curTestCaseData = TESTCASE_DATA[rowIdx];

        bool bNotMatched = false;
        int numIdx = 0;
        int vecSize = output.size();
        while (curTestCaseData[numIdx] > 0 && numIdx < vecSize)
        {
            if (curTestCaseData[numIdx] != output[numIdx])
            {
                bNotMatched = true;
                break;
            }

            ++numIdx;
        }


        bNotMatched |= (numIdx != vecSize);

        if (bNotMatched)
        {
            cout << "RowIdx: " << rowIdx << endl;
            break;
        }
    }
    return 0;
}

#endif
