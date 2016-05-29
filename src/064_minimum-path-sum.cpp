#include <iostream>
#include <vector>


typedef std::vector<int>        GridRow;
typedef std::vector<GridRow>    Grid;

class Solution
{
public:
    int minPathSum(Grid &grid)
    {
        if (grid.empty() || grid.front().empty())
            return 0;

        auto rowCount = grid.size();
        auto colCount = grid.front().size();
        std::vector<int> curRowPathSums(colCount);
        std::vector<int> prevRowPathSums(colCount);
        std::vector<int> *pCurPathSums = &curRowPathSums;
        std::vector<int> *pPrevPathSums = &prevRowPathSums;

        // f(i, j) = cell(i, j) + min{ f(i - 1, j), f(i, j - 1) }
        bool hasPrevRow = false;
        for (auto i = 0; i < rowCount; ++i)
        {
            auto &row = grid[i];
            auto &curSums = *pCurPathSums;
            auto &prevSums = *pPrevPathSums;
            curSums[0] = row[0] + prevSums[0];
            for (auto j = 1; j < colCount; ++j)
            {
                auto cellVal = row[j];
                auto val1 = cellVal + curSums[j - 1];
                auto val2 = hasPrevRow ? (cellVal + prevSums[j]) : (val1);
                curSums[j] = std::min(val1, val2);
            }

            hasPrevRow = true;
            std::swap(pPrevPathSums, pCurPathSums);
        }

        return pPrevPathSums->back();
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(Grid grid, int expected)
{
    Solution solution;
    auto ret = solution.minPathSum(grid);
    if (ret != expected)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest({
               { 4, 5, },
               { 2, 5, },
           },
           11);

    doTest({
               { 5, 6, 7, },
               { 4, 5, 1, },
               { 3, 9, 2, },
           },
           17);

    return 0;
}

#endif
