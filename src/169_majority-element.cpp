#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <climits>
#include <algorithm>
#include <vector>


using namespace std;


class Solution
{
public:
    int majorityElement(vector<int> &num)
    {
        sort(num.begin(), num.end());
        return num[num.size() / 2];
    }
};


#ifdef LEETCODE_DEBUG

int main()
{
    srand(time(0));

    vector<int> input;
    vector<int> inputBak;
    Solution solution;

    for (int i = 0; i < 10000; ++i)
    {
        input.clear();

        int size = rand() % 20 + 2;
        int correct = rand() % 100;

        // 填充超过一半的数字
        int correctNumExtraCount = rand() % (size / 2) + 1;
        for (int j = 0, n = size / 2 + correctNumExtraCount; j < n; ++j)
            input.push_back(correct);

        for (int j = 0, n = size - input.size(); j < n; ++j)
            input.push_back(rand() % 100);

        random_shuffle(input.begin(), input.end());

        inputBak = input;
        int ret = solution.majorityElement(input);
        if (ret != correct)
        {
            printf("Sample: ");
            for (int j = 0, n = inputBak.size(); j < n; ++j)
                printf("%d ", inputBak[i]);
            printf("\n");

            printf("Ouput: %d\nCorrect: %d\n", ret, correct);
            break;
        }

    }
    return 0;
}

#endif
