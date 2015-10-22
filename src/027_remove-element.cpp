#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <memory>

class Solution
{
public:
    int removeElement(std::vector<int> &vecNums, int val)
    {
        auto itNewEnd = std::remove_if(vecNums.begin(),
                                       vecNums.end(),
                                       [val](const int &e) { return e == val; });
        return itNewEnd - vecNums.cbegin();
    }
};


#ifdef LEETCODE_DEBUG

void doTest(int val, std::vector<int> vecNums, std::vector<int> expectNums)
{
    Solution solution;
    int newLen = solution.removeElement(vecNums, val);
    vecNums.resize(newLen);
    if (vecNums != expectNums)
        std::printf("Test failed.\n");
}

int main()
{
    doTest(4, {}, {});
    doTest(3, { 1, 2, 3, 3, 4, 5 }, { 1, 2, 4, 5 });
    doTest(1, { 1, 2, 1, 1, 4 }, { 2, 4 });
    return 0;
}

#endif
