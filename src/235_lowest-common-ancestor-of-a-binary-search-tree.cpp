#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <memory>


#ifdef LEETCODE_DEBUG
struct TreeNode
{
    int         val;
    TreeNode    *left;
    TreeNode    *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr)
    {}

    TreeNode() : TreeNode(0)
    {}
};
#endif


static TreeNode** selectChildNodePtr(TreeNode *pParent, TreeNode *pDest)
{
    if (pParent == pDest)
        return nullptr;

    return (pDest->val < pParent->val) ? &pParent->left : &pParent->right;
}

static TreeNode* selectChildNode(TreeNode *pParent, TreeNode *pDest)
{
    TreeNode **ppChildNode = selectChildNodePtr(pParent, pDest);
    return ppChildNode ? *ppChildNode : nullptr;
}


class Solution
{
public:
    TreeNode* lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (p == q)
            return p;

        TreeNode *pNode = root;
        while (pNode)
        {
            // 原来 "Binary Search Tree" 是没有相同值结点的
            TreeNode *pNext1 = selectChildNode(pNode, p);
            TreeNode *pNext2 = selectChildNode(pNode, q);

            if (pNext1 != pNext2)
                break;

            pNode = pNext1;
        }

        return pNode;
    }
};



#ifdef LEETCODE_DEBUG

static bool addTreeNode(TreeNode **ppRoot, TreeNode *pNewNode)
{
    // 空树
    TreeNode *pNode = *ppRoot;
    if (!pNode)
    {
        *ppRoot = pNewNode;
        return true;
    }

    while (pNode)
    {
        // 合适的插入位置，当时一定是没指向结点的
        TreeNode **ppNextNode = selectChildNodePtr(pNode, pNewNode);
        if (*ppNextNode == nullptr)
        {
            *ppNextNode = pNewNode;
            return true;
        }

        pNode = *ppNextNode;
    }

    return false;
}


static bool findNode(TreeNode *pRoot,
                     TreeNode *pDestNode,
                     std::vector<TreeNode*> *outPaths)
{
    outPaths->clear();
    outPaths->push_back(pRoot);

    TreeNode *pNode = pRoot;
    while (pNode != pDestNode)
    {
        pNode = selectChildNode(pNode, pDestNode);
        if (!pNode)
        {
            outPaths->clear();
            return false;
        }

        outPaths->push_back(pNode);
    }

    return true;
}


static bool doTest(int treeNodeCount, int testCount, std::mt19937 funcRandomNum)
{
    std::vector<int> vecNodeValues(treeNodeCount);
    for (int i = 0, n = vecNodeValues.size(); i < n; ++i)
        vecNodeValues[i] = i;

    std::shuffle(vecNodeValues.begin(), vecNodeValues.end(), funcRandomNum);

    TreeNode *pRoot = nullptr;
    std::vector<TreeNode> vecNodes(treeNodeCount);
    for (int i = 0, n = vecNodeValues.size(); i < n; ++i)
    {
        TreeNode *pNode = &vecNodes[i];
        pNode->val = vecNodeValues[i];
        if (!addTreeNode(&pRoot, pNode))
        {
            std::printf("Failed to build tree.\n");
            return false;
        }
    }


    Solution solution;
    std::vector<TreeNode*> vecPaths1;
    std::vector<TreeNode*> vecPaths2;
    for (int i = 0; i < testCount; ++i)
    {
        TreeNode *pNode1 = &vecNodes[funcRandomNum() % treeNodeCount];
        TreeNode *pNode2 = &vecNodes[funcRandomNum() % treeNodeCount];

        bool found1 = findNode(pRoot, pNode1, &vecPaths1);
        bool found2 = findNode(pRoot, pNode2, &vecPaths2);
        if (!(found1 && found2))
        {
            std::printf("Failed to find tree node.\n");
            return false;
        }


        TreeNode *pResult = nullptr;
        int minPathCount = std::min(vecPaths1.size(), vecPaths2.size());
        for (int j = 0; j < minPathCount; ++j)
        {
            if (vecPaths1[j] != vecPaths2[j])
                break;

            pResult = vecPaths1[j];
        }

        if (!pResult)
        {
            std::printf("Failed to find ancestor.\n");
            return false;
        }


        if (pResult != solution.lowestCommonAncestor(pRoot, pNode1, pNode2))
        {
            std::printf("Test failed.\n");
            return false;
        }
    }

    return true;
}



int main()
{
    std::random_device rd;
    std::mt19937 funcRandomNum(rd());

    for (int i = 0; i < 10000; ++i)
    {
        int nodeCount = funcRandomNum() % 1000 + 1;
        bool ret = doTest(nodeCount, 1000, funcRandomNum);
        if (!ret)
            break;
    }

    return 0;
}

#endif
