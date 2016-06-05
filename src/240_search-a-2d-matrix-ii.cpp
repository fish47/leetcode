#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>


typedef std::vector<int>        MatrixRow;
typedef std::vector<MatrixRow>  Matrix;


class Solution {
public:
    bool searchMatrix(Matrix &matrix, int target)
    {
        if (matrix.empty() || matrix.front().empty())
            return false;

        auto rowCount = matrix.size();
        auto colCount = matrix.front().size();
        int rowIdx = 0;
        int colIdx = colCount - 1;
        while (rowIdx < rowCount && colIdx >= 0)
        {
            auto val = matrix[rowIdx][colIdx];
            if (val == target)
                return true;


            if (val > target)
            {
                // 右侧不论上方还是下方，数字只会越来越大，所以向左找
                --colIdx;
            }
            else
            {
                // 左上方的数字都小，所以向下找
                ++rowIdx;
            }
        }

        return false;
    }
};


#ifdef LEETCODE_DEBUG

static bool doTest(Matrix matrix)
{
    std::priority_queue<int> nums;
    for (auto &row : matrix)
        std::for_each(row.cbegin(), row.cend(), [&nums](const int &num) { nums.push(num); });

    if (nums.empty())
        return false;

    Solution solution;
    auto num = nums.top();
    while (!nums.empty())
    {
        bool contains = (num == nums.top());
        bool val = solution.searchMatrix(matrix, num);
        if (val != contains)
            return false;

        if (contains)
            nums.pop();

        --num;
    }

    return true;
}


int main()
{
    Matrix matrix =
    {
        { 1,   4,  7, 11, 15 },
        { 2,   5,  8, 12, 19 },
        { 3,   6,  9, 16, 22 },
        { 10, 13, 14, 17, 24 },
        { 18, 21, 23, 26, 30 },
    };

    if (!doTest(matrix))
        std::cout << "Test failed." << std::endl;

    return 0;
}

#endif
