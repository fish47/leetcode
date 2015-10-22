#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <bitset>


class Solution
{
private:
    static const int    kMinGridSize    = 3;
    static const int    kMinBoardSize   = 9;
    static const int    kDigitCount     = 9;
    static const char   kMinDigit       = '0';
    static const char   kMaxDigit       = '9';

public:
    typedef std::vector<char>           BoardRow;
    typedef std::vector<BoardRow>       Board;
    typedef std::bitset<kDigitCount>    DigitFlags;


private:
    static bool isValidBoardSize(int size)
    {
        return (size > 0 && size % kMinBoardSize == 0);
    }


    static bool doCheckDigits(Board &board, DigitFlags &flags,
                              int rowIdx, int colIdx,
                              int gridRowCount, int gridColCount)
    {
        flags.reset();

        for(int i = 0; i < gridRowCount; ++i)
        {
            for (int j = 0; j < gridColCount; ++j)
            {
                char ch = board[rowIdx + i][colIdx + j];
                if (kMinDigit <= ch && ch <= kMaxDigit)
                {
                    // 如果数字重复
                    int pos = ch - kMinDigit - 1;
                    if (flags.test(pos))
                        return false;

                    flags.set(pos);
                }
            }
        }

        return true;
    }


    static bool doCheckBoard(Board &board, DigitFlags &flags,
                             int colStep, int rowStep)
    {
        int rowCount = board.size();
        int colCount = board[0].size();

        for (int i = 0; i < rowCount; i += rowStep)
        {
            for (int j = 0; j < colCount; j += colStep)
            {
                bool ret = doCheckDigits(board, flags, i, j, rowStep, colStep);
                if (!ret)
                    return false;
            }
        }

        return true;
    }


public:
    bool isValidSudoku(Board board)
    {
        int rowCount = board.size();
        if (!isValidBoardSize(rowCount))
            return false;

        int colCount = board[0].size();
        if (!isValidBoardSize(colCount))
            return false;

        // 会不会有不同的列数？
        auto cbIsSameColCount = [colCount](const BoardRow &row) { return row.size() == colCount; };
        if (!std::all_of(board.cbegin(), board.cend(), cbIsSameColCount))
            return false;


        // 测行
        std::bitset<kMinBoardSize> digitFlags;
        if (!doCheckBoard(board, digitFlags, kMinBoardSize, 1))
            return false;

        // 测列
        if (!doCheckBoard(board, digitFlags, 1, kMinBoardSize))
            return false;

        // 测格
        if (!doCheckBoard(board, digitFlags, kMinGridSize, kMinGridSize))
            return false;

        return true;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(Solution::Board board, bool expected)
{
    Solution solution;
    if (solution.isValidSudoku(board) != expected)
        std::printf("Test failed.\n");
}

int main()
{
    // sample
    doTest({
               { '5', '3', '.', '.', '7', '.', '.', '.', '.' },
               { '6', '.', '.', '1', '9', '5', '.', '.', '.' },
               { '.', '9', '8', '.', '.', '.', '.', '6', '.' },
               { '8', '.', '.', '.', '6', '.', '.', '.', '3' },
               { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
               { '7', '.', '.', '.', '2', '.', '.', '.', '6' },
               { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
               { '.', '.', '.', '4', '1', '9', '.', '.', '5' },
               { '.', '.', '.', '.', '8', '.', '.', '7', '9' },
           },
           true);

    // 不规则行
    doTest({
               { '5', '3', '.', '.', '7', '.', '.', '.', '.' },
               { '6', '.', '.', '1', '9', '5', '.', '.', '.' },
               { '.', '9', '8', '.', '.', '.', '.', '6', '.' },
               { '8', '.', '.', '.', '6', '.', '.', '.', '3' },
               { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
               { '7', '.', '.', '.', '2', '.', '.', '.', '6' },
               { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
               { '.', '.', '.', '4', '1', '9', '.', '.', '5' },
               { '.', '.', '.', '.', '8', '.', '.', '7', '9' },
               { '.', '.', '.', '.', '8', '.', '.', '7', '9' },
           },
           false);

    // 不规则列
    doTest({
               { '5', '3', '.', '.', '7', '.', '.', '.', '.' },
               { '6', '.', '.', '1', '9', '5', '.', '.', '.' },
               { '.', '9', '8', '.', '.', '.', '.', '6', '.' },
               { '8', '.', '.', '.', '6', '.', '.', '.', '3' },
               { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
               { '7', '.', '.', '.', '2', '.', '.', '.', '6' },
               { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
               { '.', '.', '.', '4', '1', '9', '.', '.', '5' },
               { '.' },
           },
           false);


    // 数字重复
    doTest({
               { '5', '3', '.', '.', '7', '.', '.', '.', '.' },
               { '6', '.', '.', '1', '9', '5', '.', '.', '.' },
               { '6', '9', '8', '.', '.', '.', '.', '6', '.' },
               { '8', '.', '.', '.', '6', '.', '.', '.', '3' },
               { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
               { '7', '.', '.', '.', '2', '.', '.', '.', '6' },
               { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
               { '.', '.', '.', '4', '1', '9', '.', '.', '5' },
               { '.', '.', '.', '.', '8', '.', '.', '7', '9' },
           },
           false);

    return 0;
}

#endif
