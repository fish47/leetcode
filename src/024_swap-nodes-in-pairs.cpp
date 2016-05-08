#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>


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
    ListNode* swapPairs(ListNode *pHead)
    {
        ListNode *pCur = pHead;
        ListNode *pNext = pHead ? pHead->next : nullptr;
        ListNode *pNewHead = pNext ? pNext : pCur;
        ListNode *pUnlinked = nullptr;
        while (pCur && pNext)
        {
            // 上一次交换的后结点等到下一轮再连接
            ListNode *pNextNext = pNext->next;
            pNext->next = pCur;
            pCur->next = nullptr;
            if (pUnlinked)
                pUnlinked->next = pNext;

            pUnlinked = pCur;
            pCur = pNextNext;
            pNext = pNextNext ? pNextNext->next : nullptr;
        }

        // 留意奇数个结点的情况
        if (pUnlinked)
            pUnlinked->next = pCur;

        return pNewHead;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> vecNums, std::vector<int> vecAssertValues)
{
    std::vector<ListNode> vecNodes;
    vecNodes.reserve(vecNums.size());

    ListNode *pPrevNode = nullptr;
    for (int i = 0, n = vecNums.size(); i < n; ++i)
    {
        vecNodes.emplace_back(vecNums[i]);
        ListNode *pNewNode = &vecNodes.back();
        if (pPrevNode)
            pPrevNode->next = pNewNode;

        pPrevNode = pNewNode;
    }


    Solution solution;
    std::vector<int> vecReversed;
    ListNode *pHead = vecNodes.empty() ? nullptr : &vecNodes.front();
    ListNode *pNode = solution.swapPairs(pHead);
    while (pNode)
    {
        vecReversed.push_back(pNode->val);
        pNode = pNode->next;
    }

    if (vecReversed != vecAssertValues)
        std::printf("Test failed.\n");
}


int main()
{
    doTest({}, {});
    doTest({ 1 }, { 1 });
    doTest({ 1, 2 }, { 2, 1 });
    doTest({ 1, 2, 3 }, { 2, 1, 3 });
    doTest({ 1, 2, 3, 4 }, { 2, 1, 4, 3 });
    doTest({ 1, 2, 3, 4, 5, 6 }, { 2, 1, 4, 3, 6, 5 });
    return 0;
}

#endif
