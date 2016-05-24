#include <iostream>
#include <vector>
#include <algorithm>


class Solution
{
public:
    std::vector<int> intersect(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        std::vector<int> ret;
        std::vector<int> nums1Bak = nums1;
        std::vector<int> nums2Bak = nums2;
        std::sort(nums1Bak.begin(), nums1Bak.end());
        std::sort(nums2Bak.begin(), nums2Bak.end());
        std::set_intersection(nums1Bak.cbegin(), nums1Bak.cend(),
                              nums2Bak.cbegin(), nums2Bak.cend(),
                              std::back_inserter(ret));

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> nums1, std::vector<int> nums2, std::vector<int> expected)
{
    Solution solution;
    std::vector<int> ret = solution.intersect(nums1, nums2);
    if (ret != expected)
        std::cout << "Test failed." << std::endl;
}

int main()
{
    doTest({ 2, 1, 2, 1 }, { 3, 2, 1, 2 }, { 1, 2, 2 });
    doTest({ 2, 2, 2, 2, 1, 1, 1 }, { 1, 2, 1 }, { 1, 1, 2 });
    return 0;
}

#endif
