#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>


using namespace std;

class Solution
{
public:
    void rotate(int nums[], int n, int k)
    {
        k %= n;

        // reverse() 是绕中心旋转，转两次就会恢复原来的顺序
        reverse(nums, nums + n);
        reverse(nums, nums + k);
        reverse(nums + k, nums + n);
    }
};



#ifdef LEETCODE_DEBUG

static bool doTest(int numArray[], list<int> &result)
{
    int idx = 0;
    list<int>::iterator it = result.begin();
    list<int>::iterator endIt = result.end();

    while (it != endIt)
    {
        if (*it != numArray[idx])
            return false;

        ++idx;
        ++it;
    }

    return true;
}

int main()
{
    vector<int> nums;
    list<int> rotatedNums;
    int numArray[20];
    Solution solution;

    srand(time(0));

    for (int i = 0; i < 10000; ++i)
    {
        int numCount = rand() % 10 + 1;
        int rotateCount = rand() % 30;

        nums.clear();
        for (int i = 0; i < numCount; ++i)
            nums.push_back(i);

        copy(nums.begin(), nums.end(), numArray);
        solution.rotate(numArray, numCount, rotateCount);

        rotatedNums.clear();
        copy(nums.begin(), nums.end(), back_inserter(rotatedNums));
        for (int j = 0; j < rotateCount; ++j)
        {
            int tmp = rotatedNums.back();
            rotatedNums.pop_back();
            rotatedNums.push_front(tmp);
        }

        if (!doTest(numArray, rotatedNums))
        {
            cout << "Bang!" << endl;
            break;
        }
    }

    return 0;
}

#endif
