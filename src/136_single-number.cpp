#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <ctime>


using namespace std;

class Solution
{
public:
    int singleNumber(int A[], int n)
    {
        /*
         * 例如有以下的序列
         * 01001
         * 10111
         * 01001
         *
         * 唯一的数字是 10111
         *
         * 如果对应位有奇数个 1 ，最终答案对应位也是 1 ，有奇数个 0 同理。
         * 可以想象为，从上到下对每位做"溢出加法"。
         */
        int ret = 0;
        for (int i = 0; i < n; ++i)
            ret ^= A[i];
        return ret;
    }
};


#ifdef LEETCODE_DEBUG
int main()
{
    vector<int> nums;
    Solution solution;
    int arr[1000];

    srand(time(0));

    for (int i = 0; i < 10000; ++i)
    {
        nums.clear();

        int numCount = rand() % 40 + 1;
        for (int i = 0; i < numCount; ++i)
        {
            nums.push_back(i);
            nums.push_back(i);
        }

        random_shuffle(nums.begin(), nums.end());

        int answer = nums[nums.size() - 1];
        nums.pop_back();

        copy(nums.begin(), nums.end(), arr);

        if (answer != solution.singleNumber(arr, nums.size()))
        {
            printf("Bang!");
            break;
        }
    }

    return 0;
}
#endif
