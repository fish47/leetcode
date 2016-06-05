#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <algorithm>


typedef std::vector<int>        BoardRow;
typedef std::vector<BoardRow>   Board;

static const int    kCachedRowCount                 = 2;
static const int    kLiveCellMinNeighborCount       = 2;
static const int    kLiveCellMaxNeighborCount       = 3;
static const int    kDeadCellRebornNeighborCount    = 3;


static bool getCellLiveState(Board &borad,
                             int rowCount,
                             int colCount,
                             int orgY,
                             int orgX,
                             int offsetY,
                             int offsetX)
{
    auto x = orgX + offsetX;
    auto y = orgY + offsetY;
    if (x >= 0 && x < colCount && y >= 0 && y < rowCount)
        return borad[y][x];

    return false;
}


static int getLiveNeighborCellCount(Board &borad, int rowCount, int colCount, int y, int x)
{
    auto liveNeighborCount = 0;
    liveNeighborCount += getCellLiveState(borad, rowCount, colCount, y, x, -1, -1);
    liveNeighborCount += getCellLiveState(borad, rowCount, colCount, y, x, -1,  0);
    liveNeighborCount += getCellLiveState(borad, rowCount, colCount, y, x, -1,  1);
    liveNeighborCount += getCellLiveState(borad, rowCount, colCount, y, x,  0, -1);
    liveNeighborCount += getCellLiveState(borad, rowCount, colCount, y, x,  0,  1);
    liveNeighborCount += getCellLiveState(borad, rowCount, colCount, y, x,  1, -1);
    liveNeighborCount += getCellLiveState(borad, rowCount, colCount, y, x,  1,  0);
    liveNeighborCount += getCellLiveState(borad, rowCount, colCount, y, x,  1,  1);
    return liveNeighborCount;
}


static bool getNextCellState(bool val, int liveCount)
{
    if (val)
        return (kLiveCellMinNeighborCount <= liveCount && liveCount <= kLiveCellMaxNeighborCount);
    else
        return (liveCount == kDeadCellRebornNeighborCount);
}


class Solution
{
public:
    void gameOfLife(Board &board)
    {
        auto rowCount = board.size();
        auto colCount = board.empty() ? 0 : board.front().size();
        if (rowCount <= 0 || colCount <= 0)
            return;

        auto cachedRowIdx = 0;
        BoardRow cachedRows[kCachedRowCount];
        for (auto i = 0; i < rowCount; ++i)
        {
            // 淘汰并提交最老的缓存
            auto &cachedRow = cachedRows[cachedRowIdx];
            if (i >= kCachedRowCount)
                board[i - kCachedRowCount].swap(cachedRow);

            cachedRow.resize(colCount);
            for (auto j = 0; j < colCount; ++j)
            {
                auto count = getLiveNeighborCellCount(board, rowCount, colCount, i, j);
                cachedRow[j] = getNextCellState(board[i][j], count);
            }

            cachedRowIdx = (cachedRowIdx + 1) % kCachedRowCount;
        }

        // 提交剩下的缓存
        auto commitCount = kCachedRowCount;
        if (rowCount < kCachedRowCount)
        {
            commitCount = rowCount;
            cachedRowIdx = 0;
        }

        for (auto i = rowCount - commitCount; i < rowCount; ++i)
        {
            board[i].swap(cachedRows[cachedRowIdx]);
            cachedRowIdx = (cachedRowIdx + 1) % kCachedRowCount;
        }
    }
};


#ifdef LEETCODE_DEBUG

static void getNextGameOfLifeState(Board &curState, Board *pNextState)
{
    if (!pNextState)
        return;

    auto rowCount = curState.size();
    auto colCount = (rowCount > 0) ? curState.front().size() : 0;
    if (rowCount <= 0 || colCount <= 0)
        return;

    auto &nextState = *pNextState;
    nextState.resize(rowCount);
    for (auto i = 0; i < rowCount; ++i)
    {
        nextState[i].resize(colCount);
        for (auto j = 0; j < colCount; ++j)
        {
            auto liveCount = getLiveNeighborCellCount(curState, rowCount, colCount, i, j);
            nextState[i][j] = getNextCellState(curState[i][j], liveCount);
        }
    }
}


static void createRandomGameOfLiveState(Board *pState,
                                        std::function<int()> randomState,
                                        int rowCount,
                                        int colCount)
{
    if (!pState || !randomState || rowCount <= 0 || colCount <= 0)
        return;

    auto &state = *pState;
    state.resize(rowCount);
    for (auto &row : state)
    {
        row.resize(colCount);
        for (auto &cell : row)
            cell = randomState();
    }
}



static void printState(Board &board)
{
    for (auto &row : board)
    {
        for (auto &cell : row)
            std::cout << cell << " ";

        std::cout << std::endl;
    }
}

int main()
{
    Board state;
    Board nextState;
    Solution solution;
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomRowCount(0, 100);
    std::uniform_int_distribution<> randomColCount(0, 100);
    std::uniform_int_distribution<> randomState(0, 1);
    auto cbRandomState = std::bind(randomState, randomEngine);
    for (auto i = 0; i < 1000; ++i)
    {
        auto rowCount = randomRowCount(randomEngine);
        auto colCount = randomColCount(randomEngine);
        state.clear();
        nextState.clear();
        createRandomGameOfLiveState(&state, cbRandomState, rowCount, colCount);
        getNextGameOfLifeState(state, &nextState);
        solution.gameOfLife(state);
        if (state != nextState)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
