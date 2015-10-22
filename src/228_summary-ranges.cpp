#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>


static const char   *kFormatNumberRange     = "%d->%d";
static const char   *kFormatSingleNumber    = "%d";

class Solution
{
public:
    std::vector<std::string> summaryRanges(std::vector<int> &nums)
    {
        std::vector<std::string> ret;
        if (nums.empty())
            return ret;

        int rangeStart = nums[0];
        int rangeEnd = rangeStart;
        char buf[1024];
        for (int i = 0, n = nums.size(); i < n; ++i)
        {
            int nextNum = (i + 1 < n) ? nums[i + 1] : rangeStart;
            bool isMerged = (nextNum == rangeEnd + 1);

            if (isMerged)
                rangeEnd = nextNum;

            if (!isMerged || i + 1 == n)
            {
                const char *format = (rangeStart == rangeEnd)
                                     ? kFormatSingleNumber
                                     : kFormatNumberRange;

                int len = std::sprintf(buf, format, rangeStart, rangeEnd);
                if (len > 0)
                {
                    ret.resize(ret.size() + 1);
                    ret.back().clear();
                    ret.back().append(buf, len);
                }

                rangeStart = nextNum;
                rangeEnd = nextNum;
            }
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> nums,
                   std::vector<std::string> expected)
{
    Solution solution;
    std::vector<std::string> ret = solution.summaryRanges(nums);
    if (ret != expected)
        std::printf("Test failed.\n");
}

int main()
{
    doTest({}, {});

    doTest({ 0,1,2,4,5,7 },
           {
               "0->2",
               "4->5",
               "7",
           });

    doTest({ 0, 2, 4, 6 },
           {
               "0",
               "2",
               "4",
               "6",
           });

    doTest({ 0, 1, 2, 4, 5, 6 },
           {
               "0->2",
               "4->6",
           });

    doTest({ 0, 1, 2, 3, 4, 5, 6 },
           {
               "0->6",
           });

    return 0;
}

#endif
