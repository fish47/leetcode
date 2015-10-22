#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <bitset>


class Solution
{
public:
    bool canWinNim(int n)
    {
        if (n <= 0)
            return false;

        return (n % 4 != 0);
    }
};


#ifdef LEETCODE_DEBUG

static bool canWin(int n)
{
    if (n <= 3)
        return true;


    std::bitset<3> winFlags;
    winFlags.set();
    for (int i = 4; i <= n; ++i)
    {
        // 分别尝试取 1 / 2 / 3 颗石子，如果能令对方进入必输状态，就算赢了
        bool canWin = !winFlags.all();

        winFlags >>= 1;
        if (canWin)
            winFlags.set(2);

    }

    return winFlags.test(2);
}


int main()
{
    Solution solution;
    for (int i = 1; i < 1000; ++i)
    {
        if (solution.canWinNim(i) != canWin(i))
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
