#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>



class Solution
{
public:
    bool containsDuplicate(std::vector<int> &vecNums)
    {
        std::set<int> numSet(vecNums.begin(), vecNums.end());
        return numSet.size() != vecNums.size();
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> vecNums, bool expected)
{
    Solution solution;
    if (solution.containsDuplicate(vecNums) != expected)
        std::printf("Test failed.\n");
}


int main()
{
    doTest({}, false);
    doTest({ 1 }, false);
    doTest({ 1, 2, 3 }, false);
    doTest({ 1, 2, 1 }, true);
    return 0;
}

#endif
