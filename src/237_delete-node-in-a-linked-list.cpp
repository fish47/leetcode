#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#ifdef LEETCODE_DEBUG
struct ListNode
{
    int         val;
    ListNode    *next;

    ListNode(int x) : val(x), next(nullptr)
    {}
};
#endif


class Solution
{
public:
    void deleteNode(ListNode *node)
    {
        // 尾结点没办法处理，题目也说不会是尾结点
        ListNode *nextNode = node->next;
        if (!nextNode)
            return;

        // 例如要处理 1 -> 2 -> 3 -> 4 中的 2
        // 先变成 1 -> 3 -> 3 -> 4
        // 再将第 3 个结点删除
        node->val = nextNode->val;
        node->next = nextNode->next;
        delete nextNode;
    }
};


#ifdef LEETCODE_DEBUG

static bool testDeleteListNode(int nodeCount)
{
    // 构造链表
    ListNode *headNode = nullptr;
    ListNode *endNode = nullptr;
    std::vector<int> values;
    for (int i = 0; i < nodeCount; ++i)
    {
        ListNode *node = new ListNode(i);
        if (endNode)
            endNode->next = node;

        if (!headNode)
            headNode = node;

        values.push_back(i);
        endNode = node;
    }

    // 先删头结点吧，第二轮再随机选
    int deleteIdx = 0;
    ListNode *deleteNode = headNode;

    // 随机删结点，直到只剩下一个
    Solution solution;
    while (true)
    {
        // 不太可能会出现
        if (!headNode)
            return false;

        if (!headNode->next)
        {
            delete headNode;
            break;
        }

        solution.deleteNode(deleteNode);
        values.erase(values.begin() + deleteIdx);

        // 题目要求不会是最后一个
        if (values.size() > 1)
            deleteIdx = std::rand() % (values.size() - 1);

        // 遍历链表对比，并找出删除结点的指针
        int nodeIdx = 0;
        ListNode *node = headNode;
        for (auto it = values.begin(); it != values.end(); ++it)
        {
            if (!node || node->val != *it)
                return false;

            if (nodeIdx == deleteIdx)
                deleteNode = node;

            node = node->next;
            ++nodeIdx;
        }
    }

    return true;
}

int main()
{
    std::srand(std::time(0));
    for (int i = 0; i < 100000; ++i)
    {
        if (!testDeleteListNode(5))
        {
            std::printf("Bang!\n");
            break;
        }
    }
    return 0;
}

#endif
