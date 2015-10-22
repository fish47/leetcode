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
    ListNode* deleteDuplicates(ListNode *pHead)
    {
        if (!pHead)
            return pHead;

        ListNode *pLastNode = pHead;
        ListNode *pNode = pHead->next;
        while (pNode)
        {
            if (pLastNode->val != pNode->val)
            {
                pLastNode->next = pNode;
                pLastNode = pNode;
            }

            pNode = pNode->next;
        }

        pLastNode->next = nullptr;
        return pHead;
    }
};


#ifdef LEETCODE_DEBUG

static ListNode* generateRandomSortedList(std::mt19937 &randomEngine,
                                          std::vector<ListNode> *pVecNodes,
                                          std::vector<int> *pVecNodeValues)
{
    std::uniform_int_distribution<> randomCount(1, 30);
    std::uniform_int_distribution<> randomNodeVal(0, 10);
    int nodeCount = randomCount(randomEngine);
    pVecNodes->resize(nodeCount);
    pVecNodeValues->resize(nodeCount);

    for (int i = 0; i < nodeCount; ++i)
    {
        ListNode &node = pVecNodes->at(i);
        int nodeVal = randomNodeVal(randomEngine);
        node.next = nullptr;
        node.val = nodeVal;
        pVecNodeValues->at(i) = nodeVal;
    }

    std::sort(pVecNodes->begin(),
              pVecNodes->end(),
              [](ListNode &n1, ListNode &n2) { return (n1.val < n2.val); });

    for (int i = 0, n = nodeCount - 1; i < n; ++i)
        pVecNodes->at(i).next = &pVecNodes->at(i + 1);

    return &pVecNodes->at(0);
}


static bool doTest(Solution &solution,
                   ListNode *pHead,
                   std::vector<int> *pVecNodeValues,
                   std::vector<int> *pVecNodeValuesCmp)
{
    // 去重1
    *pVecNodeValuesCmp = *pVecNodeValues;
    std::sort(pVecNodeValuesCmp->begin(), pVecNodeValuesCmp->end());
    auto itNewEnd = std::unique(pVecNodeValuesCmp->begin(), pVecNodeValuesCmp->end());
    pVecNodeValuesCmp->erase(itNewEnd, pVecNodeValuesCmp->end());

    // 去重2
    ListNode *pNewHead = solution.deleteDuplicates(pHead);
    ListNode *pNode = pNewHead;
    pVecNodeValues->clear();
    while (pNode)
    {
        pVecNodeValues->push_back(pNode->val);
        pNode = pNode->next;
    }

    return (*pVecNodeValues == *pVecNodeValuesCmp);
}


int main()
{
    std::mt19937 randomEngine;
    Solution solution;
    std::vector<ListNode> vecNodes;
    std::vector<int> vecNodeValues;
    std::vector<int> vecNodeValuesCmp;

    for (int i = 0; i < 10000; ++i)
    {
        ListNode *pHead = generateRandomSortedList(randomEngine, &vecNodes, &vecNodeValues);
        bool ret = doTest(solution, pHead, &vecNodeValues, &vecNodeValuesCmp);
        if (!ret)
        {
            std::printf("Test failed\n");
            break;
        }
    }

    return 0;
}

#endif
