#include <cstdio>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <functional>


class Solution
{
public:
    double findMedianSortedArrays(std::vector<int> &vecNums1, std::vector<int> &vecNums2)
    {
        int count1 = vecNums1.size();
        int count2 = vecNums2.size();
        if (count1 > count2)
            return findMedianSortedArrays(vecNums2, vecNums1);

        if (count1 == 0)
        {
            int mid = (count2 - 1) / 2;
            if (count2 % 2 == 1)
                return vecNums2[mid];

            int left = vecNums2[mid];
            int right = vecNums2[mid + 1];
            return (left + right) / 2.0F;
        }

        // 如果数组长度为单数，先忽略 vecNums2 的最后一个元素
        int halfCount = (count1 + count2) / 2;
        int allCount = halfCount * 2;
        int count2Tmp = allCount - count1;

        int low = 0;
        int high = std::min(count1, halfCount) + 1;
        int a1 = 0;
        int a2 = 0;
        int b1 = 0;
        int b2 = 0;
        while (low <= high)
        {
            // 假设由 idx1 和 idx 能分割出两堆长度相同的数字，并且左边都小于右边
            // A[0:idx1) | A[idx1:count1)
            // B[0:idx2) | B[idx2:count2)
            int mid = (high + low) / 2;
            int idx1 = mid;
            int idx2 = halfCount - idx1;

            // 注意可能全部分到一边的情况
            a1 = (idx1 <= 0) ? vecNums2[idx2 - 1] : vecNums1[idx1 - 1];
            a2 = (idx1 >= count1) ? vecNums2[idx2] : vecNums1[idx1];
            b1 = (idx2 <= 0) ? vecNums1[idx1 - 1] : vecNums2[idx2 - 1];
            b2 = (idx2 >= count2Tmp) ? vecNums1[idx1] : vecNums2[idx2];

            if (idx1 > 0 && a1 > b2)
            {
                // 分割位置在 idx1 左边
                // [ 2  3  4 (7) ]
                // [ 0  1  5  6 (8) 9 ]
                high = mid - 1;
            }
            else if (idx1 < count1 && b1 > a2)
            {
                // 分割位置在 idx1 右边
                // [ 2 (3) 4  7 ]
                // [ 0  1  5  6 (8) 9 ]
                low = mid + 1;
            }
            else
            {
                break;
            }
        }

        int leftMax = std::max(a1, b1);
        int rightMin = std::min(a2, b2);
        if (allCount == count1 + count2)
            return (leftMax + rightMin) / 2.0F;

        // 将最初忽略的元素重新插回来，会影响中位数结果
        std::array<int, 3> nums = { leftMax, rightMin, vecNums2.back() };
        std::sort(nums.begin(), nums.end());
        return nums[1];
    }
};


#ifdef LEETCODE_DEBUG

int main()
{
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomNumCount(1, 100);
    std::uniform_int_distribution<> randomSelect(0, 1);
    std::vector<int> vecNums;
    std::vector<int> vecNums1;
    std::vector<int> vecNums2;
    Solution solution;
    for (int i = 0; i < 100000; ++i)
    {
        int count = randomNumCount(randomEngine);
        for (int j = 0; j < count; ++j)
        {
            std::vector<int> &vecOutput = randomSelect(randomEngine) ? vecNums1 : vecNums2;
            vecOutput.push_back(j);
            vecNums.push_back(j);
        }

        double val1 = (count - 1) / 2.0F;
        double val2 = solution.findMedianSortedArrays(vecNums1, vecNums2);
        if (val1 != val2)
        {
            std::printf("Test failed.\n");
            break;
        }

        vecNums.clear();
        vecNums1.clear();
        vecNums2.clear();
    }
    return 0;
}

#endif
