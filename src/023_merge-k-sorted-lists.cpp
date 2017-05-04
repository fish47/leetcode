#include <iostream>
#include <vector>
#include <random>


#ifdef LEETCODE_DEBUG

struct ListNode
{

    int val;

    ListNode *next;

    ListNode(int x) : val(x), next(nullptr)
    {}

    ListNode() : ListNode(0)
    {}
};

#endif


static void appendListNode(ListNode *pNode, ListNode **ppHead, ListNode **ppTail)
{
    if (!pNode || !ppHead || !ppTail)
        return;

    if (!*ppHead)
        *ppHead = pNode;

    if (*ppTail)
        (*ppTail)->next = pNode;

    *ppTail = pNode;
}

class Solution
{
public:
    ListNode* mergeKLists(std::vector<ListNode*> &vecLists)
    {
        ListNode *pHead = nullptr;
        ListNode *pTail = nullptr;
        while (true)
        {
            // 每次只能选一个
            int minIdx = -1;
            for (int i = 0, n = vecLists.size(); i < n; ++i)
            {
                ListNode *pSubList = vecLists[i];
                if (!pSubList)
                    continue;

                if (minIdx < 0 || pSubList->val < vecLists[minIdx]->val)
                    minIdx = i;
            }

            // 所有子链表都为空
            if (minIdx < 0)
                break;

            ListNode *pSubListHead = vecLists[minIdx];
            appendListNode(pSubListHead, &pHead, &pTail);
            vecLists[minIdx] = pSubListHead->next;
        }
        return pHead;
    }
};


#ifdef LEETCODE_DEBUG

int main()
{
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomListCount(1, 50);
    std::uniform_int_distribution<> randomNodeCount(0, 50);
    std::vector<ListNode> vecNodes;
    std::vector<ListNode*> vecListHeads;
    std::vector<ListNode*> vecListTails;
    Solution solution;
    for (int i = 0; i < 10000; ++i)
    {
        auto nodeCount = randomNodeCount(randomEngine);
        vecNodes.resize(nodeCount);

        auto listCount = randomListCount(randomEngine);
        std::uniform_int_distribution<> randomList(0, listCount - 1);
        vecListHeads.resize(listCount);
        vecListTails.resize(listCount);
        std::fill(vecListHeads.begin(), vecListHeads.end(), nullptr);
        std::fill(vecListTails.begin(), vecListTails.end(), nullptr);

        for (int i = 0; i < nodeCount; ++i)
        {
            // 重置链表结点数据
            ListNode &node = vecNodes[i];
            node.val = i;
            node.next = nullptr;

            // 分到对应链表
            auto listIdx = randomList(randomEngine);
            auto &pListHead = vecListHeads[listIdx];
            auto &pListTail = vecListTails[listIdx];
            appendListNode(&node, &pListHead, &pListTail);
        }

        int count = 0;
        ListNode *pNode = solution.mergeKLists(vecListHeads);
        while (pNode)
        {
            if (pNode->val != count)
                break;

            ++count;
            pNode = pNode->next;
        }

        if (count != nodeCount)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
