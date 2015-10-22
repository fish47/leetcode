#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
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


static ListNode *advanceListNode(ListNode *pStart, int count)
{
    ListNode *pRet = pStart;
    for (int i = 0; i < count && pStart; ++i)
        pRet = pRet->next;

    return pRet;
}


class Solution
{
public:
    bool isPalindrome(ListNode *pHead)
    {
        // 其实题目没定义囧
        if (!pHead)
            return true;


        int nodeCount = 0;
        for (ListNode *pNode = pHead; pNode; pNode = pNode->next)
            ++nodeCount;

        // 跳到回文串的中间偏右的第一个结点
        ListNode *pRight = advanceListNode(pHead, (nodeCount + 1) / 2);

        int palindromePartHalfLen = nodeCount / 2;
        for (int i = 0; i < palindromePartHalfLen; ++i)
        {
            ListNode *pLeft = advanceListNode(pHead, palindromePartHalfLen - i - 1);
            if (pLeft->val != pRight->val)
                return false;

            pRight = pRight->next;
        }

        return true;
    }
};


#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> vecNums, bool expected)
{
    std::vector<ListNode> vecNodes(vecNums.size());
    for (int i = 0, n = vecNodes.size(); i < n; ++i)
    {
        ListNode *pNext = (i + 1 < n) ? &vecNodes[i + 1] : nullptr;
        ListNode *pCur = &vecNodes[i];
        pCur->val = vecNums[i];
        pCur->next = pNext;
    }

    Solution solution;
    ListNode *pNode = vecNodes.empty() ? nullptr : &vecNodes[0];
    if (solution.isPalindrome(pNode) != expected)
        std::printf("Test failed.\n");
}


int main()
{
    doTest({}, true);
    doTest({ 1 }, true);
    doTest({ 1, 2, 1 }, true);
    doTest({ 1, 2, 2, 1 }, true);
    return 0;
}

#endif
