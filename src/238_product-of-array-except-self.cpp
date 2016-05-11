#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>

class Solution
{
public:
    std::vector<int> productExceptSelf(std::vector<int> &nums)
    {
        int numCount = nums.size();
        std::vector<int> ret(numCount);
        if (numCount > 0)
            ret[0] = 1;

        /*
         * p[0] = 1
         * p[1] = 1 * p[0]
         * p[2] = 1 * p[0] * p[1]
         * p[3] = 1 * p[1] * p[2]
         */
        auto product1 = 1;
        for (auto i = 1; i < numCount; ++i)
        {
            product1 *= nums[i - 1];
            ret[i] = product1;
        }

        /*
         * p[3] *= 1
         * p[2] *= 1 * p[3]
         * p[1] *= 1 * p[2] * p[3]
         * p[0] *= 1 * p[1] * p[2] * p[3]
         */
        auto product2 = 1;
        for (auto i = numCount - 2; i >= 0; --i)
        {
            product2 *= nums[i + 1];
            ret[i] *= product2;
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

int main()
{
    std::vector<int> nums;
    std::vector<int> products;
    Solution solution;
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomValue(-100, 100);
    std::uniform_int_distribution<> randomNumCount(0, 100);
    auto cbGetRandomValue = std::bind(randomValue, randomEngine);
    for (auto i = 0; i < 1000; ++i)
    {
        auto numCount = randomNumCount(randomEngine);
        nums.clear();
        std::generate_n(std::back_inserter(nums), numCount, cbGetRandomValue);

        // 不要用除法，如果中间有 0 就不对了
        products.clear();
        for (auto i = 0; i < numCount; ++i)
        {
            auto product = 1;
            for (auto j = 0; j < numCount; ++j)
                product *= (i == j) ? 1 : nums[j];

            products.push_back(product);
        }

        auto ret = solution.productExceptSelf(nums);
        if (ret != products)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
