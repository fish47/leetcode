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
    string convertToTitle(int n)
    {
        string str;
        n = max(n, 1);

        while (n > 0)
        {
            // 1-based
            --n;

            char ch = n % 26 + 'A';
            str.push_back(ch);

            n /= 26;
        }

        reverse(str.begin(), str.end());
        return str;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(int n, string str)
{
    Solution solution;
    string output = solution.convertToTitle(n);

    if (output != str)
        printf("n=%d\nOutput=%s Correct=%s\n", n, output.c_str(), str.c_str());
}


int main()
{
    doTest(1, "A");
    doTest(2, "B");
    doTest(26, "Z");
    doTest(27, "AA");
    doTest(28, "AB");
    return 0;
}

#endif
