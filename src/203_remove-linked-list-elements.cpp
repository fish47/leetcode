#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>


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
    ListNode* removeElements(ListNode *pHead, int val)
    {
        ListNode *pNewHead = pHead;
        ListNode *pNewTail = nullptr;
        ListNode *pNode = pHead;
        while (pNode)
        {
            ListNode *pNext = pNode->next;
            if (pNode->val == val)
            {
                // 下一个才有可能是最前的有效结点
                if (pNode == pNewHead)
                    pNewHead = pNext;

                if (pNewTail)
                    pNewTail->next = pNext;
            }
            else
            {
                // 记录最后的有效结点
                pNewTail = pNode;
            }

            pNode = pNext;
        }

        return pNewHead;
    }
};



#ifdef LEETCODE_DEBUG

static bool doTest(Solution &solution,
                   std::mt19937 &randomEngine,
                   std::vector<ListNode> *pVecNodes,
                   std::vector<int> *pVecNums,
                   std::vector<int> *pVecCmp)
{
    std::uniform_int_distribution<> randomNodeCount(0, 100);
    std::uniform_int_distribution<> randomNodeValue(0, 10);

    int nodeCont = randomNodeCount(randomEngine);
    pVecNodes->resize(nodeCont);
    pVecCmp->resize(nodeCont);

    ListNode *pHead = nullptr;
    for (int i = 0; i < nodeCont; ++i)
    {
        int nodeValue = randomNodeValue(randomEngine);
        pVecCmp->at(i) = nodeValue;

        ListNode &node = pVecNodes->at(i);
        ListNode *pNext = (i + 1 >= nodeCont) ? nullptr : &pVecNodes->at(i + 1);
        node.next = pNext;
        node.val = nodeValue;

        if (!pHead)
            pHead = &node;
    }


    int removeValue = randomNodeValue(randomEngine);
    ListNode *pNode = solution.removeElements(pHead, removeValue);
    pVecNums->clear();
    while (pNode)
    {
        pVecNums->push_back(pNode->val);
        pNode = pNode->next;
    }

    auto itNewEnd = std::remove(pVecCmp->begin(), pVecCmp->end(), removeValue);
    pVecCmp->erase(itNewEnd, pVecCmp->cend());

    return (*pVecNums == *pVecCmp);
}

int main()
{
    Solution solution;
    std::mt19937 randomEngine;
    std::vector<ListNode> vecNodes;
    std::vector<int> vecNums;
    std::vector<int> vecCmp;

    for (int i = 0; i < 100000; ++i)
    {
        bool ret = doTest(solution, randomEngine, &vecNodes, &vecNums, &vecCmp);
        if (!ret)
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
