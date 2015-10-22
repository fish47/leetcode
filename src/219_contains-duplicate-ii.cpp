#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <utility>


class Solution
{
private:
    typedef std::pair<int,int>  NumAndIndex;

public:
    bool containsNearbyDuplicate(std::vector<int> &vecNums, int k)
    {
        // 肯定不重复
        if (vecNums.size() < 2)
            return false;


        std::vector<NumAndIndex> vecNumAndIndexes(vecNums.size());
        for (int i = 0, n = vecNums.size(); i < n; ++i)
        {
            NumAndIndex &numAndIdx = vecNumAndIndexes[i];
            numAndIdx.first = vecNums[i];
            numAndIdx.second = i;
        }
        std::sort(vecNumAndIndexes.begin(), vecNumAndIndexes.end());


        for (int i = 0, n = vecNumAndIndexes.size() - 1; i < n; ++i)
        {
            NumAndIndex &cur = vecNumAndIndexes[i];
            NumAndIndex &next = vecNumAndIndexes[i + 1];

            // 在 k 范围内找到重复的元素
            if (cur.first == next.first && next.second - cur.second <= k)
                return true;
        }

        return false;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> vecNums, int k, bool expected)
{
    Solution solution;
    if (solution.containsNearbyDuplicate(vecNums, k) != expected)
        std::printf("Test failed.\n");
}

int main()
{
    doTest({}, 0, false);
    doTest({}, 5, false);
    doTest({ 1, 0, 1, 1 }, 1, true);
    doTest({ 5, 2, 3, 4, 5 }, 4, true);
    doTest({ 5, 2, 3, 4, 5 }, 3, false);
    doTest({ 5, 2, 1, 4, 9 }, 1, false);
    return 0;
}

#endif
