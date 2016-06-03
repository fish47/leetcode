#include <iostream>
#include <vector>
#include <algorithm>


typedef std::vector<int>        MatrixRow;
typedef std::vector<MatrixRow>  Matrix;

class Solution
{
public:
    void rotate(Matrix &matrix)
    {
        /*
         * 左右侧交换
         * 0 1 2      2 1 0
         * 3 4 5  ->  5 4 3
         * 6 7 8      8 7 6
         */
        auto size = matrix.size();
        auto swapCount = size / 2;
        for (auto i = 0; i < size; ++i)
        {
            auto &row = matrix[i];
            for (auto j = 0; j < swapCount; ++j)
                std::swap(row[j], row[size - j - 1]);
        }

        /*
         * 左上右下沿对角线交换
         * 2 1 0      6 3 0
         * 5 4 3  ->  7 4 1
         * 8 7 6      8 5 2
         */
        for (auto i = 0; i < size; ++i)
        {
            auto count = size - i - 1;
            for (auto j = 0; j < count; ++j)
                std::swap(matrix[i][j], matrix[size - j - 1][size - i - 1]);
        }
    }
};



#ifdef LEETCODE_DEBUG

static void createRandomMatrix(Matrix *pMatrix, int size)
{
    if (!pMatrix || size < 0)
        return;

    auto val = 0;
    auto &maxtrix = *pMatrix;
    maxtrix.resize(size);
    for (auto i = 0; i < size; ++i)
    {
        auto &row = maxtrix[i];
        row.resize(size);
        for (auto j = 0; j < size; ++j)
            row[j] = val++;
    }
}


static void rotateMatrix(Matrix &matrix, Matrix *pRotated)
{
    if (!pRotated)
        return;

    auto size = matrix.size();
    auto &rotated = *pRotated;
    rotated.resize(size);
    std::for_each(rotated.begin(), rotated.end(), [size](MatrixRow &row) { row.resize(size); });

    auto colIdx = 0;
    for (auto it = matrix.crbegin(); it != matrix.crend(); ++it)
    {
        auto &row = *it;
        for (auto i = 0; i < size; ++i)
            rotated[i][colIdx] = row[i];

        ++colIdx;
    }
}


int main()
{
    Matrix matrix;
    Matrix rotated;
    Solution solution;
    for (auto i = 1; i < 100; ++i)
    {
        createRandomMatrix(&matrix, i);
        rotateMatrix(matrix, &rotated);

        solution.rotate(matrix);
        if (matrix != rotated)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
