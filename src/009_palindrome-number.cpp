#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <array>


using namespace std;


static const std::array<int, 10> kDigitWeights =
{
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
};


class Solution
{
public:
    bool isPalindrome(int x)
    {
        // 负数不算
        if (x < 0)
            return false;

        // 例如 x = 10 虽然在 i = 0 位置，但有 2 位数字
        int num = x;
        auto itPos = std::lower_bound(kDigitWeights.cbegin(), kDigitWeights.cend(), num);
        int digitCount = itPos - kDigitWeights.cbegin() + (*itPos == num);

        while (num)
        {
            int highWeight = kDigitWeights[digitCount - 1];
            int lowWeight = kDigitWeights[1];

            int highDigit = num / highWeight;
            int lowDigit = num % lowWeight;
            if (highDigit != lowDigit)
                return false;

            num -= highDigit * highWeight;
            num /= lowWeight;
            digitCount -= 2;
        }

        return true;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(int num, bool expected)
{
    Solution solution;
    if (solution.isPalindrome(num) != expected)
        std::printf("expected: %d  num: %d\n", expected, num);
}

int main()
{
    doTest(0, true);
    doTest(1, true);
    doTest(11, true);
    doTest(212, true);
    doTest(100, false);
    doTest(123454321, true);
    doTest(1234554321, true);
    return 0;
}

#endif
