#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>


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
    ListNode* removeNthFromEnd(ListNode *pHead, int n)
    {
        // 非法参数
        if (n <= 0)
            return pHead;

        // 删除单结点最后肯定是空链表
        if (!pHead->next)
            return nullptr;

        ListNode *pRemove = pHead;
        ListNode *pNextN = pRemove;
        for (int i = 0; i < n; ++i)
        {
            pNextN = pNextN->next;

            // 要删除的倒数第 n 个结点，刚好是首结点
            if (!pNextN)
                return pHead->next;
        }

        // 使 pRemove 的第 n 个结点为空结点
        ListNode *pPrev = nullptr;
        while (pNextN)
        {
            pNextN = pNextN->next;
            pPrev = pRemove;
            pRemove = pRemove->next;
        }

        pPrev->next = pRemove->next;
        return pHead;
    }
};



#ifdef LEETCODE_DEBUG


static bool doTest(Solution &solution,
                   std::mt19937 &randomEngine,
                   std::vector<ListNode> *pVecNodes,
                   std::vector<int> *pVecNums,
                   std::vector<int> *pVecNumsCmp)
{
    std::uniform_int_distribution<> randomNodeCount(1, 10);
    int nodeCount = randomNodeCount(randomEngine);
    pVecNodes->resize(nodeCount);
    pVecNumsCmp->resize(nodeCount);

    for (int i = 0; i < nodeCount; ++i)
    {
        ListNode &node = pVecNodes->at(i);
        node.val = i;
        node.next = (i == nodeCount - 1) ? nullptr : &pVecNodes->at(i + 1);
        pVecNumsCmp->at(i) = i;
    }

    int idx = std::uniform_int_distribution<>(1, nodeCount)(randomEngine);
    ListNode *pNode = solution.removeNthFromEnd(&pVecNodes->at(0), idx);
    pVecNums->clear();
    while (pNode)
    {
        pVecNums->push_back(pNode->val);
        pNode = pNode->next;
    }

    pVecNumsCmp->erase(pVecNumsCmp->cbegin() + (nodeCount - idx));
    bool ret = (*pVecNums == *pVecNumsCmp);
    return ret;
}


int main()
{
    Solution solution;
    std::mt19937 randomEngine;
    std::vector<ListNode> vecNodes;
    std::vector<int> vecNums;
    std::vector<int> vecNumsCmp;

    for (int i = 0; i < 10000; ++i)
    {
        if (!doTest(solution, randomEngine, &vecNodes, &vecNums, &vecNumsCmp))
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
