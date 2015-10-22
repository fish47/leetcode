#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <list>
#include <deque>


using namespace std;


#ifdef LEETCODE_DEBUG
struct ListNode
{
    int         val;
    ListNode    *next;

    ListNode(int x) : val(x), next(nullptr)
    {}
};
#endif


static int getLinkedListLength(ListNode *head)
{
    int len = 0;
    ListNode *node = head;

    while (node)
    {
        node = node->next;
        ++len;
    }

    return len;
}


static ListNode *skipNodes(ListNode *node, int count)
{
    if (count <= 0)
        return node;

    ListNode *ret = node;
    while (ret && count > 0)
    {
        --count;
        ret = ret->next;
    }

    return ret;
}


class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        int len1 = getLinkedListLength(headA);
        int len2 = getLinkedListLength(headB);
        int lenDelta = abs(len1 - len2);

        // 如果两个链表有交点，那么一定有公共的部分
        ListNode *cmp1 = (len1 > len2) ? skipNodes(headA, lenDelta) : headA;
        ListNode *cmp2 = (len2 > len1) ? skipNodes(headB, lenDelta) : headB;

        // 如果有公共的部分，从后向前遍历一定会发现公共结点
        while (cmp1 && cmp2)
        {
            if (cmp1 == cmp2)
                return cmp1;

            cmp1 = cmp1->next;
            cmp2 = cmp2->next;
        }

        return nullptr;
    }
};


#ifdef LEETCODE_DEBUG

static ListNode *doCreateLinkedList(ListNode *pStartNode, int nodeCount, int *pnNodeID)
{
    ListNode *pHead = pStartNode;
    for (int i = 0; i < nodeCount; ++i)
    {
        ListNode *newNode = new ListNode((*pnNodeID)++);
        newNode->next = pHead;
        pHead = newNode;
    }

    return pHead;
}


static void createTestCase(ListNode **ppOutHead1,
                           ListNode **ppOutHead2,
                           ListNode **ppOutJoint)
{
    int nodeID = 0;

    if (rand() % 1)
        *ppOutJoint = doCreateLinkedList(nullptr, rand() % 10 + 1, &nodeID);
    else
        *ppOutJoint = nullptr;

    *ppOutHead1 = doCreateLinkedList(*ppOutJoint, rand() % 10 + 1, &nodeID);
    *ppOutHead2 = doCreateLinkedList(*ppOutJoint, rand() % 10 + 1, &nodeID);
}


static void doDiposeLinkedList(ListNode *pHead, ListNode *pStopNode)
{
    ListNode *node = pHead;
    while (node && node != pStopNode)
    {
        ListNode *delNode = node;
        node = node->next;

        delete delNode;
    }
}


static void disposeTestCase(ListNode *pHead1, ListNode *pHead2, ListNode *pJoint)
{
    doDiposeLinkedList(pHead1, pJoint);
    doDiposeLinkedList(pHead2, pJoint);
    doDiposeLinkedList(pJoint, nullptr);
}



int main()
{
    srand(time(0));

    Solution solution;
    for (int i = 0; i < 10000; ++i)
    {
        ListNode *pHead1 = nullptr;
        ListNode *pHead2 = nullptr;
        ListNode *pJoint = nullptr;

        createTestCase(&pHead1, &pHead2, &pJoint);

        ListNode *output = solution.getIntersectionNode(pHead1, pHead2);
        if (output != pJoint)
        {
            cout << "Bang!" << endl;
            break;
        }

        disposeTestCase(pHead1, pHead2, pJoint);
    }

    return 0;
}

#endif
