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
    typedef vector<int>         IntVector;
    typedef vector<IntVector>   IntVectors;

    IntVectors generate(int numRows)
    {
        IntVectors ret;
        for (int rowIdx = 0; rowIdx < numRows; ++rowIdx)
        {
            IntVector row;
            row.push_back(1);

            // 除了首尾的其他元素都遵守以下公式
            // f(x, y) = f(x, y - 1) + f(x - 1, y - 1)
            IntVector *prevRow = (rowIdx > 0) ? &ret[rowIdx - 1] : nullptr;
            for (int i = 1, n = rowIdx - 1; i <= n; ++i)
            {
                int val = (*prevRow)[i - 1] + (*prevRow)[i];
                row.push_back(val);
            }

            if (rowIdx > 0)
                row.push_back(1);

            ret.push_back(row);
        }

        return ret;
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
    Solution::IntVectors output = solution.generate(10);

    for (int i = 0; i < 10; ++i)
    {
        Solution::IntVector &row = output[i];
        const int *curTestCaseRow = TESTCASE_DATA[i];

        bool bNotMatched = false;
        int numIdx = 0;
        int rowSize = row.size();
        while (curTestCaseRow[numIdx] > 0 && numIdx < rowSize)
        {
            if (curTestCaseRow[numIdx] != row[numIdx])
            {
                bNotMatched = true;
                break;
            }

            ++numIdx;
        }

        bNotMatched |= (numIdx != rowSize);

        if (bNotMatched)
        {
            cout << "RowIdx: " << i << endl;
            break;
        }
    }

    return 0;
}


#endif
