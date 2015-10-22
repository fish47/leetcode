#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <memory>


#ifdef LEETCODE_DEBUG
struct ListNode
{
    int         val;
    ListNode    *next;

    ListNode(int x) : val(x), next(nullptr)
    {}

    ListNode() : ListNode(0)
    {}
};
#endif


class Solution
{
public:
    ListNode* mergeTwoLists(ListNode *pList1, ListNode *pList2)
    {
        // 不看 Discuss 根本不知道是按升序排列囧囧囧
        // 也没办法猜，例如有两个链表分别是 [1,1] 和 [2,2] ，排序顺序直接影响结果

        ListNode *pNewTail = nullptr;
        ListNode *pNewHead = nullptr;
        ListNode *pHead1 = pList1;
        ListNode *pHead2 = pList2;

        while (pHead1 || pHead2)
        {
            // 从两个链表中选最小值的结点
            ListNode *pNode = nullptr;
            if (!pHead1)
                pNode = pHead2;
            else if (!pHead2)
                pNode = pHead1;
            else
                pNode = (pHead1->val < pHead2->val) ? pHead1 : pHead2;

            // 从对应链表中移除
            if (pNode == pHead1)
                pHead1 = pHead1->next;
            else
                pHead2 = pHead2->next;

            // 连接
            if (pNewTail)
                pNewTail->next = pNode;

            // 第一个元素就是表头
            if (!pNewHead)
                pNewHead = pNode;

            pNewTail = pNode;
        }

        return pNewHead;
    }
};


#ifdef LEETCODE_DEBUG

static bool doTest(std::mt19937 &randomEngine,
                   std::uniform_int_distribution<> &randomSelectList,
                   Solution &solution,
                   std::vector<ListNode> *pVecNodes)
{
    std::uniform_int_distribution<> randomNodeCount(1, 5);

    ListNode *pNewHead1 = nullptr;
    ListNode *pNewHead2 = nullptr;
    ListNode *pNewTail1 = nullptr;
    ListNode *pNewTail2 = nullptr;
    int nodeCount = randomNodeCount(randomEngine);
    pVecNodes->resize(nodeCount);
    for (int i = 0; i < nodeCount; ++i)
    {
        ListNode *pNode = &pVecNodes->at(i);
        pNode->val = i;
        pNode->next = nullptr;

        bool bSelectList1 = randomSelectList(randomEngine);
        ListNode **ppTail = bSelectList1 ? &pNewTail1 : &pNewTail2;
        ListNode **ppHead = bSelectList1 ? &pNewHead1 : &pNewHead2;

        if (!*ppTail)
            *ppHead = pNode;
        else
            (*ppTail)->next = pNode;

        *ppTail = pNode;
    }

    ListNode *pRet = solution.mergeTwoLists(pNewHead1, pNewHead2);
    ListNode *pNode = pRet;
    auto itNode = pVecNodes->cbegin();
    while (pNode)
    {
        if (itNode == pVecNodes->cend())
            return false;

        if (pNode != &(*itNode))
            return false;

        pNode = pNode->next;
        ++itNode;
    }

    return (itNode == pVecNodes->cend());
}


int main()
{
    Solution solution;
    std::mt19937 randomEngine;
    std::vector<ListNode> vecNodes;

    for (int i = 0; i < 10000; ++i)
    {
        std::uniform_int_distribution<> selectBoth(0, 1);
        bool ret1 = doTest(randomEngine, selectBoth, solution, &vecNodes);

        std::uniform_int_distribution<> selectList2(0, 0);
        bool ret2 = doTest(randomEngine, selectList2, solution, &vecNodes);

        if (!ret1 || !ret2)
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
