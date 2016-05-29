#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>


static const int kMoveDirections[][2]   =
{
    {  1,  0 }, // 右
    {  0,  1 }, // 下
    { -1,  0 }, // 左
    {  0, -1 }, // 上
};


class Solution
{
private:
    typedef std::vector<int>        MatrixRow;
    typedef std::vector<MatrixRow>  Matrix;

    static const int            kNumberStart            = 1;
    static const int            kStartPositionX         = 0;
    static const int            kStartPositionY         = 0;
    static const int            kDirectionCount         = 4;
    static const int            kDirectionIndexX        = 0;
    static const int            kDirectionIndexY        = 1;

public:
    Matrix generateMatrix(int n)
    {
        Matrix matrix(n);
        std::for_each(matrix.begin(), matrix.end(), [n](MatrixRow &row) { row.resize(n); });

        auto num = kNumberStart;
        auto dirIdx = 0;
        int x = kStartPositionX - kMoveDirections[dirIdx][kDirectionIndexX];
        int y = kStartPositionY - kMoveDirections[dirIdx][kDirectionIndexY];
        std::array<int, kDirectionCount> lineLengths;
        std::fill(lineLengths.begin(), lineLengths.end(), n);
        while (true)
        {
            auto length = lineLengths[dirIdx];
            if (length == 0)
                break;

            const int stepX = kMoveDirections[dirIdx][kDirectionIndexX];
            const int stepY = kMoveDirections[dirIdx][kDirectionIndexY];
            for (auto i = 0; i < length; ++i)
            {
                x += stepX;
                y += stepY;
                matrix[y][x] = num;
                ++num;
            }

            // 每画一条线，就像为两个方向加上一堵墙
            auto nextDirIdx = (dirIdx + 1) % kDirectionCount;
            auto prevDirIdx = (dirIdx + kDirectionCount - 1) % kDirectionCount;
            --lineLengths[prevDirIdx];
            --lineLengths[nextDirIdx];
            dirIdx = nextDirIdx;
        }

        return matrix;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> nums)
{
    auto size = static_cast<int>(std::sqrt(nums.size()));
    std::vector<std::vector<int>> matrix(size);
    for (auto i = 0; i < size; ++i)
    {
        auto idx = i * size;
        std::copy(nums.cbegin() + idx,  nums.cbegin() + idx + size, std::back_inserter(matrix[i]));
    }

    Solution solution;
    auto ret = solution.generateMatrix(size);
    if (matrix != ret)
        std::cout << "Test failed." << std::endl;
}


int main()
{
    doTest({ 1 });
    doTest({
               1, 2,
               4, 3,
           });
    doTest({
               1, 2, 3,
               8, 9, 4,
               7, 6, 5,
           });
    doTest({
                1,  2,  3,  4,
               12, 13, 14,  5,
               11, 16, 15,  6,
               10,  9,  8,  7,
           });
    return 0;
}

#endif
