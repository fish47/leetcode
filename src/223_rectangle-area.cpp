#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <tuple>


class Solution
{
private:
    static void normalizeRect(int &l, int &t, int &r, int &b)
    {
        if (l > r)
            std::swap(l, r);

        if (t > b)
            std::swap(t, b);
    }


    static int getIntersectedArea(int l1, int b1, int r1, int t1,
                                  int l2, int b2, int r2, int t2)
    {
        // 水平不相交
        if (r2 <= l1 || r1 <= l2)
            return 0;

        // 竖直不相交
        if (b2 <= t1 || b1 <= t2)
            return 0;

        int poses[4];
        poses[0] = l1;
        poses[1] = r1;
        poses[2] = l2;
        poses[3] = r2;
        std::sort(poses, poses + 4);
        int width = poses[2] - poses[1];

        poses[0] = t1;
        poses[1] = b1;
        poses[2] = t2;
        poses[3] = b2;
        std::sort(poses, poses + 4);
        int height = poses[2] - poses[1];

        return width * height;
    }


public:
    int computeArea(int l1, int b1, int r1, int t1, int l2, int b2, int r2, int t2)
    {
        normalizeRect(l1, t1, r1, b1);
        normalizeRect(l2, t2, r2, b2);

        int area1 = (r1 - l1) * (b1 - t1);
        int area2 = (r2 - l2) * (b2 - t2);
        int area3 = getIntersectedArea(l1, b1, r1, t1, l2, b2, r2, t2);
        return area1 + area2 - area3;
    }
};



#ifdef LEETCODE_DEBUG


static void doTest(std::tuple<int, int, int, int> tupRect1,
                   std::tuple<int, int, int, int> tupRect2,
                   int expected)
{
    int l1 = std::get<0>(tupRect1);
    int t1 = std::get<1>(tupRect1);
    int r1 = std::get<2>(tupRect1);
    int b1 = std::get<3>(tupRect1);

    int l2 = std::get<0>(tupRect2);
    int t2 = std::get<1>(tupRect2);
    int r2 = std::get<2>(tupRect2);
    int b2 = std::get<3>(tupRect2);

    Solution solution;
    int ret = solution.computeArea(l1, b1, r1, t1, l2, b2, r2, t2);
    if (ret != expected)
        std::printf("Test failed.\n");
}


int main()
{
    doTest(std::make_tuple(0, 0, 10, 10),
           std::make_tuple(-10, -10, 5, 5),
           300);

    doTest(std::make_tuple(0, 0, 10, 10),
           std::make_tuple(-10, -10, 0, 0),
           200);

    doTest(std::make_tuple(0, 0, 10, 10),
           std::make_tuple(0, 0, 5, 5),
           100);

    doTest(std::make_tuple(0, 0, 10, 10),
           std::make_tuple(-10, 0, -5, 5),
           125);

    doTest(std::make_tuple(0, 0, 10, 10),
           std::make_tuple(20, 0, 25, 5),
           125);

    doTest(std::make_tuple(0, 0, 10, 10),
           std::make_tuple(0, 20, 5, 25),
           125);

    doTest(std::make_tuple(0, 0, 10, 10),
           std::make_tuple(0, -20, 5, -15),
           125);

    // 反转数据
    doTest(std::make_tuple(10, 10, 0, 0),
           std::make_tuple(5, 5, 0, 0),
           100);

    return 0;
}

#endif
