#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <string>
#include <algorithm>


using namespace std;

class Solution
{
public:
    int titleToNumber(string s)
    {
        /*
         * 变进制简单应用
         */

        int ret = 0;
        for (int i = 0, n = s.length(); i < n; ++i)
        {
            ret *= 26;

            char ch = s[i];
            if (isupper(ch))
                ret += ch - 'A' + 1;
            else
                ret += ch - 'a' + 1;
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void assertEqulas(string str, int val)
{
    Solution solution;
    int cmp = solution.titleToNumber(str);

    if (cmp != val)
        printf("s=%s\nOutput=%d Correct=%d\n", str.c_str(), cmp, val);
}

int main()
{
    assertEqulas("A", 1);
    assertEqulas("a", 1);
    assertEqulas("Z", 26);
    assertEqulas("AB", 28);
    assertEqulas("ab", 28);
    return 0;
}

#endif
