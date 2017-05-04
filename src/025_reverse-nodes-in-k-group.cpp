#include <iostream>
#include <random>
#include <vector>
#include <algorithm>


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

static inline ListNode* getNextNodeSafe(ListNode *pNode)
{
    return pNode ? pNode->next : nullptr;
}

static void reverseLinkedList(ListNode *pHead, ListNode *pLast)
{
    ListNode *pNode = pHead;
    ListNode *pPrev = nullptr;
    while (pNode)
    {
        ListNode *pNext = pNode->next;
        if (pPrev)
            pNode->next = pPrev;

        if (pNode == pLast)
            break;

        pPrev = pNode;
        pNode = pNext;
    }
}

class Solution
{
public:
    ListNode* reverseKGroup(ListNode *pHead, int k)
    {
        if (k <= 1)
            return pHead;

        ListNode *pIterate = pHead;
        ListNode *pNewHeade = nullptr;
        ListNode *pPrevSubLineTail = nullptr;
        while (pIterate)
        {
            int nextCount = 1;
            ListNode *pSubListHead = pIterate;
            ListNode *pSubListLast = pSubListHead;
            while (pSubListLast && nextCount < k)
            {
                ++nextCount;
                pSubListLast = pSubListLast->next;
            }

            // 剩余结点不足 k 个
            if (!pSubListLast)
            {
                // 题目明明说 k 小于等于链表长度的囧
                if (!pNewHeade)
                    pNewHeade = pHead;
                break;
            }

            // 整条子链头尾反转
            ListNode *pNextSubLineHead = getNextNodeSafe(pSubListLast);
            reverseLinkedList(pSubListHead, pSubListLast);
            pSubListHead->next = pNextSubLineHead;
            if (pPrevSubLineTail)
                pPrevSubLineTail->next = pSubListLast;
            if (!pNewHeade)
                pNewHeade = pSubListLast;

            pIterate = pNextSubLineHead;
            pPrevSubLineTail = pSubListHead;
        }
        return pNewHeade;
    }
};


#ifdef LEETCODE_DEBUG

static void reverseKGroupValues(std::vector<int> &vecValues, int k)
{
    if (vecValues.empty() || k <= 0)
        return;

    int loopCount = vecValues.size() / k;
    for (int i = 0; i < loopCount; ++i)
    {
        auto itBegin = vecValues.begin() + i * k;
        auto itEnd = itBegin + k;
        std::reverse(itBegin, itEnd);
    }
}


int main()
{
    std::mt19937 randomEngine;
    std::uniform_int_distribution<> randomNodeCount(0, 5);
    Solution solution;
    std::vector<int> vecValues;
    std::vector<ListNode> vecNodes;
    for (int i = 0; i < 100000; ++i)
    {
        auto count = randomNodeCount(randomEngine);
        vecNodes.resize(count);
        vecValues.resize(count);
        for (int i = 0; i < count; ++i)
        {
            auto val = i;
            ListNode &node = vecNodes[i];
            vecValues[i] = val;
            node.val = val;
            node.next = (i == count - 1) ? nullptr : &vecNodes[i + 1];
            if (i > 0)
                vecNodes[i - 1].next = &node;
        }

        std::uniform_int_distribution<> randomK(0, count + 5);
        auto k = randomK(randomEngine);
        bool isEmptyList = (count == 0);
        ListNode *pHead = isEmptyList ? nullptr : &vecNodes.front();
        ListNode *pRet = solution.reverseKGroup(pHead, k);
        reverseKGroupValues(vecValues, k);

        bool succeed = true;
        if (isEmptyList)
        {
            succeed = (pRet == nullptr);
        }
        else
        {
            ListNode *pNode = pRet;
            for (int i = 0; i < count; ++i)
            {
                if (!pNode || pNode->val != vecValues[i])
                {
                    succeed = false;
                    break;
                }
                pNode = pNode->next;
            }
        }

        if (!succeed)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
