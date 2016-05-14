#include <iostream>
#include <vector>


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
    ListNode* oddEvenList(ListNode *pHead)
    {
        if (!pHead || !pHead->next)
            return pHead;

        ListNode *pOddHead = pHead;
        ListNode *pOddTail = pOddHead;
        ListNode *pEvenHead = pOddHead->next;
        ListNode *pEvenTail = pEvenHead;

        bool isOdd = true;
        ListNode *pNode = pHead;
        while (pNode)
        {
            ListNode *pNextNode = pNode->next;
            ListNode **ppTail = isOdd ? &pOddTail : &pEvenTail;
            (*ppTail)->next = pNode;
            *ppTail = pNode;
            pNode = pNextNode;
            isOdd = !isOdd;
        }

        pOddTail->next = pEvenHead;
        pEvenTail->next = nullptr;
        return pOddHead;
    }
};




#ifdef LEETCODE_DEBUG

static bool doCheckListNode(ListNode **ppInOutNode, int valStart, int valStep, int count)
{
    if (!ppInOutNode)
        return false;

    auto val = valStart;
    for (auto i = 0; i < count; ++i)
    {
        ListNode *pNode = *ppInOutNode;
        if (!pNode || pNode->val != val)
            return false;

        val += valStep;
        *ppInOutNode = pNode->next;
    }

    return true;
}

static bool doTest(Solution &solution, std::vector<ListNode> *pNodes, int count)
{
    if (!pNodes)
        return false;

    // 因为题目用 1-based
    ListNode *pPrevNode = nullptr;
    pNodes->clear();
    pNodes->reserve(count);
    for (auto i = 1; i <= count; ++i)
    {
        pNodes->emplace_back(i);

        ListNode *pCur = &pNodes->back();
        if (pPrevNode)
            pPrevNode->next = pCur;

        pPrevNode = pCur;
    }

    auto oddNumCount = (count + 1) / 2;
    auto evenNumCount = count - oddNumCount;
    ListNode *pNode = solution.oddEvenList(&pNodes->front());
    bool ret = true;
    ret &= doCheckListNode(&pNode, 1, 2, oddNumCount);
    ret &= doCheckListNode(&pNode, 2, 2, evenNumCount);
    return ret;
}


int main()
{
    Solution solution;
    std::vector<ListNode> nodes;
    for (auto i = 0; i < 1000; ++i)
    {
        bool ret = doTest(solution, &nodes, i);
        if (!ret)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
