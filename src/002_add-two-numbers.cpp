#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

#ifdef LEETCODE_DEBUG

struct ListNode
{
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr)
    {}
};

#endif


class Solution
{
private:
    static const int kDecimalBase   = 10;

public:
    ListNode* addTwoNumbers(ListNode *pList1, ListNode *pList2)
    {
        if (!pList1)
            return pList2;

        if (!pList2)
            return pList1;

        int carry = 0;
        ListNode *pHead = nullptr;
        ListNode *pPrev = nullptr;
        ListNode *pNode1 = pList1;
        ListNode *pNode2 = pList2;
        while (pNode1 || pNode2 || carry)
        {
            auto val1 = pNode1 ? pNode1->val : 0;
            auto val2 = pNode2 ? pNode2->val : 0;
            auto sum = val1 + val2 + carry;
            auto nodeVal = sum % kDecimalBase;
            carry = sum / kDecimalBase;

            ListNode *pNewNode = new ListNode(nodeVal);
            if (pPrev)
                pPrev->next = pNewNode;
            else
                pHead = pNewNode;

            if (pNode1)
                pNode1 = pNode1->next;

            if (pNode2)
                pNode2 = pNode2->next;

            pPrev = pNewNode;
        }

        return pHead;
    }
};


#ifdef LEETCODE_DEBUG

static const char kZeroChar     = '0';

static ListNode* convertIntToReversedLinkedList(int num, std::vector<ListNode> &vecNodes)
{
    std::string nums = std::to_string(num);
    std::reverse(nums.begin(), nums.end());
    vecNodes.clear();
    for (auto ch : nums)
        vecNodes.emplace_back(ch - kZeroChar);

    ListNode *pPrev = nullptr;
    for (auto &node : vecNodes)
    {
        if (pPrev)
            pPrev->next = &node;
        pPrev = &node;
    }

    return &vecNodes.front();
}


static int convertReservedLinkedListToInt(ListNode *pList)
{
    if (!pList)
        return 0;

    std::string nums;
    ListNode *pNode = pList;
    while (pNode)
    {
        nums.push_back(kZeroChar + (char) pNode->val);
        pNode = pNode->next;
    }

    std::reverse(nums.begin(), nums.end());
    return std::stoi(nums);
}


static void freeLinkedList(ListNode *pHead)
{
    ListNode *pNode = pHead;
    while (pNode)
    {
        ListNode *pNext = pNode->next;
        delete pNode;
        pNode = pNext;
    }
}


static void doTest(int num1, int num2,
                   std::vector<ListNode> &vecNodes1,
                   std::vector<ListNode> &vecNodes2,
                   Solution &solution)
{
    vecNodes1.clear();
    vecNodes2.clear();

    ListNode *pHead1 = convertIntToReversedLinkedList(num1, vecNodes1);
    ListNode *pHead2 = convertIntToReversedLinkedList(num2, vecNodes2);
    ListNode *pReturn = solution.addTwoNumbers(pHead1, pHead2);
    int sum = convertReservedLinkedListToInt(pReturn);
    freeLinkedList(pReturn);
    if (sum != num1 + num2)
        std::printf("Test failed.\n");
}


int main()
{
    Solution solution;
    std::vector<ListNode> vecNodes1;
    std::vector<ListNode> vecNodes2;
    doTest(123, 2, vecNodes1, vecNodes2, solution);
    doTest(129, 2, vecNodes1, vecNodes2, solution);
    doTest(111, 999, vecNodes1, vecNodes2, solution);
    doTest(1, 999, vecNodes1, vecNodes2, solution);
    doTest(999, 1, vecNodes1, vecNodes2, solution);
    return 0;
}

#endif
