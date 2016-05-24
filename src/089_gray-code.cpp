#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <type_traits>


class Solution
{
public:
    std::vector<int> grayCode(int n)
    {
        /*
         * 00
         * 01
         * ------ 对称轴
         * 11
         * 10
         *
         *
         * 000
         * 001
         * 011
         * 010
         * ------ 对称轴
         * 110
         * 111
         * 101
         * 100
         *
         */

        std::vector<int> ret;
        if (n < 0)
            return ret;

        ret.push_back(0);
        if (n == 0)
            return ret;

        ret.push_back(1);

        for (auto i = 1; i < n; ++i)
        {
            auto mask = 1 << i;
            auto codeCount = ret.size();
            for (auto j = 0; j < codeCount; ++j)
            {
                auto idx = codeCount - j - 1;
                ret.push_back(ret[idx] | mask);
            }
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(int n, std::vector<std::string> expected)
{
    std::vector<int> nums;
    for (auto str : expected)
    {
        std::bitset<64> bits(str);
        nums.push_back(bits.to_ulong());
    }

    Solution solution;
    auto ret = solution.grayCode(n);
    if (ret != nums)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest(0, { "0" });
    doTest(1, { "0", "1" });
    doTest(2, { "00", "01", "11", "10" });
    doTest(3, { "000", "001", "011", "010", "110", "111", "101", "100" });
    return 0;
}

#endif
