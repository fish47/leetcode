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
    bool hasCycle(ListNode *pHead)
    {
        if (!pHead)
            return false;

        ListNode *pOneStep = pHead;
        ListNode *pTwoStep = pHead;
        while (true)
        {
            pOneStep = pOneStep->next;
            if (!pOneStep)
                return false;

            ListNode *pNext = pTwoStep->next;
            pTwoStep = pNext ? pNext->next : nullptr;
            if (!pTwoStep)
                return false;

            // 如果链表有环，走一步和走两步终早会相遇的
            if (pOneStep == pTwoStep)
                return true;
        }

        return false;
    }
};


#ifdef LEETCODE_DEBUG

static ListNode* createLinkedList(std::vector<ListNode> *pVecNodes, std::vector<int> &vecNodeValues)
{
    if (vecNodeValues.empty())
        return nullptr;

    ListNode *pPrevNode = nullptr;
    pVecNodes->clear();
    pVecNodes->reserve(vecNodeValues.size());

    for (int i = 0, n = vecNodeValues.size(); i < n; ++i)
    {
        int val = vecNodeValues[i];
        auto cbFindByValue = [val](const ListNode &node) { return node.val == val; };
        auto it = std::find_if(pVecNodes->cbegin(), pVecNodes->cend(), cbFindByValue);
        ListNode *pNode = (it == pVecNodes->cend()) ? nullptr : &const_cast<ListNode&>(*it);
        if (!pNode)
        {
            pVecNodes->emplace_back(val);
            pNode = &pVecNodes->back();
        }

        if (pPrevNode)
            pPrevNode->next = pNode;

        pPrevNode = pNode;
    }

    return &pVecNodes->front();
}


static void doTest(std::vector<int> vecNums, bool bHasCircle)
{
    std::vector<ListNode> vecNodes;
    ListNode *pHead = createLinkedList(&vecNodes, vecNums);
    Solution solution;
    if (solution.hasCycle(pHead) != bHasCircle)
        std::printf("Test failed!\n");
}


int main()
{
    doTest({}, false);
    doTest({ 1, 2, 1 }, true);
    doTest({ 1, 2, 3, 4 }, false);
    doTest({ 1, 2, 3, 4, 5, 1 }, true);
    return 0;
}

#endif
