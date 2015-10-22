#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>
#include <string>



class Solution
{
public:
    std::string addBinary(std::string a, std::string b)
    {
        std::string ret;
        bool hasCarry = false;
        int len1 = a.size();
        int len2 = b.size();
        for (int i = 1, n = std::max(len1, len2); i <= n || hasCarry; ++i)
        {
            int val1 = (i <= len1) ? (a[len1 - i] - '0') : 0;
            int val2 = (i <= len2) ? (b[len2 - i] - '0') : 0;
            int bitSum = val1 + val2 + hasCarry;
            char ch = '0' + (bitSum & 0x01);
            ret.push_back(ch);
            hasCarry = (bitSum & 0x02);
        }

        // 删除多余的零前缀
        auto lastNonZeroIdx = ret.find_last_of('1');
        if (lastNonZeroIdx == std::string::npos)
            ret = "0";
        else
            ret.erase(lastNonZeroIdx + 1, ret.size() - lastNonZeroIdx - 1);

        std::reverse(ret.begin(), ret.end());
        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::string a,
                   std::string b,
                   std::string expected)
{
    Solution solution;
    std::string ret = solution.addBinary(a, b);
    if (ret != expected)
        std::printf("%s + %s = %s\n", a.c_str(), b.c_str(), expected.c_str());
}


int main()
{
    doTest("1", "1", "10");
    doTest("0000001", "11", "100");
    doTest("1000000000", "1", "1000000001");
    doTest("1111111111", "1111111111", "11111111110");
    return 0;
}

#endif
