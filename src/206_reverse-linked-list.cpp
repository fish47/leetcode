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
    ListNode* reverseList(ListNode *pHead)
    {
        if (!pHead)
            return pHead;

        ListNode *pNode = pHead;
        ListNode *pNextNode = pNode->next;
        while (pNextNode)
        {
            ListNode *pNextNextNode = pNextNode->next;
            pNextNode->next = pNode;
            pNode = pNextNode;
            pNextNode = pNextNextNode;
        }

        // 之前的头结点变成尾结点
        pHead->next = nullptr;

        // 特判单结点情况
        return pNextNode ? pNextNode : pNode;
    }
};


#ifdef LEETCODE_DEBUG

static bool doTest(Solution &solution,
                   std::mt19937 &randomEngine,
                   std::vector<ListNode> *pVecNodes)
{
    std::uniform_int_distribution<> randomNodeCount(1, 1000);
    std::uniform_int_distribution<> randomNodeValue(0, 10000);
    int nodeCount = randomNodeCount(randomEngine);
    pVecNodes->resize(nodeCount);

    for (int i = 0; i < nodeCount; ++i)
    {
        ListNode *pCurNode = &pVecNodes->at(i);
        ListNode *pNextNode = (i + 1 >= nodeCount) ? nullptr : &pVecNodes->at(i + 1);
        pCurNode->val = randomNodeValue(randomEngine);
        pCurNode->next = pNextNode;
    }

    auto it = pVecNodes->crbegin();
    ListNode *pNode = solution.reverseList(&pVecNodes->at(0));
    while (true)
    {
        bool bIsEndNode = !pNode;
        bool bIsEndIt = (it == pVecNodes->crend());
        if (bIsEndNode && bIsEndIt)
            return true;

        if (bIsEndNode || bIsEndIt)
            break;

        const ListNode &iterNode = *it;
        if (pNode != &iterNode)
            return false;

        pNode = pNode->next;
        ++it;
    }

    return false;
}


int main()
{
    Solution solution;
    std::mt19937 randomEngine;
    std::vector<ListNode> vecNodes;

    for (int i = 0; i < 10000; ++i)
    {
        bool ret = doTest(solution, randomEngine, &vecNodes);
        if (!ret)
        {
            std::printf("Test failed\n");
            break;
        }
    }

    return 0;
}

#endif
