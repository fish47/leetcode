#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <random>


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


typedef void VisitNodeCallback(void *pVisitCtx, TreeNode *pNode);

static void iterateTree(TreeNode *pRoot,
                        void *pVisitCtx,
                        VisitNodeCallback cbNodeVisited,
                        VisitNodeCallback cbSubtreeVisited)
{
    if (!pRoot)
        return;


    std::vector<TreeNode*> vecNodes;
    vecNodes.push_back(pRoot);

    // 中序遍历
    while (!vecNodes.empty())
    {
        TreeNode *pNode = vecNodes.back();
        if (cbNodeVisited)
            cbNodeVisited(pVisitCtx, pNode);


        // 尽可能走到左子树的尽头
        TreeNode *pChildLeft = pNode->left;
        if (pChildLeft)
        {
            vecNodes.push_back(pChildLeft);
            continue;
        }

        TreeNode *pChildRight = pNode->right;
        if (pChildRight)
        {
            vecNodes.push_back(pChildRight);
            continue;
        }


        // 叶子结点
        while (true)
        {
            TreeNode *pChild = vecNodes.back();
            if (cbSubtreeVisited)
                cbSubtreeVisited(pVisitCtx, pChild);

            vecNodes.pop_back();
            TreeNode *pParent = vecNodes.empty() ? nullptr : vecNodes.back();

            if (!pParent)
                break;

            // 右子树遍历完就要向上回溯
            if (pParent->right == pChild)
                continue;

            // 左子树遍历完就遍历右子树
            TreeNode *pParentRight = pParent->right;
            if (pParent->left == pChild && pParentRight)
            {
                vecNodes.push_back(pParentRight);
                break;
            }
        }
    }
}


class Solution
{
public:
    TreeNode* invertTree(TreeNode *pRoot)
    {
        auto cbSwapChildren = [](void *pVisitCtx, TreeNode *pNode)
        {
            std::swap(pNode->left, pNode->right);
        };

        iterateTree(pRoot, nullptr, nullptr, cbSwapChildren);
        return pRoot;
    }
};



#ifdef LEETCODE_DEBUG

static void iterateTreeRecursively(TreeNode *pRoot,
                                   std::vector<int> *pVecVisitNode,
                                   std::vector<int> *pVecVisitSubtree)
{
    if (!pRoot)
        return;

    pVecVisitNode->push_back(pRoot->val);
    iterateTreeRecursively(pRoot->left, pVecVisitNode, pVecVisitSubtree);
    iterateTreeRecursively(pRoot->right, pVecVisitNode, pVecVisitSubtree);
    pVecVisitSubtree->push_back(pRoot->val);
}


static TreeNode* generateRandomBinaryTree(std::mt19937 &randomEngine,
                                          std::vector<TreeNode> *pVecNodes,
                                          std::vector<TreeNode*> *pVecAvailableNodes)
{
    std::uniform_int_distribution<> randomNodeCount(1, 4);
    int nodeCount = randomNodeCount(randomEngine);
    pVecNodes->resize(nodeCount);
    pVecAvailableNodes->clear();

    for (int i = 0; i < nodeCount; ++i)
    {
        TreeNode &node = pVecNodes->at(i);
        node.left = nullptr;
        node.right = nullptr;
        node.val = i;
        pVecAvailableNodes->push_back(&node);
    }

    std::random_shuffle(pVecAvailableNodes->begin(), pVecAvailableNodes->end());


    // 没有说结点值一定要按顺序
    for (int i = 1; i < nodeCount; ++i)
    {
        TreeNode **ppChild = nullptr;
        std::uniform_int_distribution<> randomIdx(0, i - 1);
        while (true)
        {
            int selectNodeIdx = randomIdx(randomEngine);
            TreeNode *pNode = pVecAvailableNodes->at(selectNodeIdx);
            bool selectLeft = (randomIdx(randomEngine) % 2 == 0);
            ppChild = selectLeft ? &pNode->left : &pNode->right;
            if (!*ppChild)
                break;
        }

        *ppChild = pVecAvailableNodes->at(i);
    }

    return pVecAvailableNodes->at(0);
}


static bool doTest(TreeNode *pRoot,
                   std::vector<int> *pVecVisitNode,
                   std::vector<int> *pVecVisitNodeCmp,
                   std::vector<int> *pVecVisitSubtree,
                   std::vector<int> *pVecVisitSubtreeCmp)
{
    pVecVisitNode->clear();
    pVecVisitNodeCmp->clear();
    pVecVisitSubtree->clear();
    pVecVisitSubtreeCmp->clear();

    struct VisitContext
    {
        std::vector<int>    *pVecNodes;
        std::vector<int>    *pVecSubtree;
    };
    VisitContext ctx;

    auto cbVisitNode = [](void *pCtx, TreeNode *pNode)
    {
        VisitContext *pVisitCtx = reinterpret_cast<VisitContext*>(pCtx);
        pVisitCtx->pVecNodes->push_back(pNode->val);
    };

    auto cbVisitSubtree = [](void *pCtx, TreeNode *pNode)
    {
        VisitContext *pVisitCtx = reinterpret_cast<VisitContext*>(pCtx);
        pVisitCtx->pVecSubtree->push_back(pNode->val);
    };


    // 递归
    iterateTreeRecursively(pRoot, pVecVisitNodeCmp, pVecVisitSubtreeCmp);

    // 非递归
    ctx.pVecNodes = pVecVisitNode;
    ctx.pVecSubtree = pVecVisitSubtree;
    iterateTree(pRoot, &ctx, cbVisitNode, cbVisitSubtree);

    return (*pVecVisitNode == *pVecVisitNodeCmp
            && *pVecVisitSubtree == *pVecVisitSubtreeCmp);
}


int main()
{
    std::mt19937 randomEngine;
    std::vector<TreeNode> vecNodes;
    std::vector<TreeNode*> vecNodePtrs;
    std::vector<int> vecVisitNode;
    std::vector<int> vecVisitNodeCmp;
    std::vector<int> vecVisitSubtree;
    std::vector<int> vecVisitSubtreeCmp;

    for (int i = 0; i < 100000; ++i)
    {
        TreeNode *pRoot = generateRandomBinaryTree(randomEngine,
                                                   &vecNodes,
                                                   &vecNodePtrs);

        bool passed = doTest(pRoot,
                             &vecVisitNode,
                             &vecVisitNodeCmp,
                             &vecVisitSubtree,
                             &vecVisitSubtreeCmp);

        if (!passed)
        {
            std::printf("Test failed!\n");
            break;
        }
    }

    return 0;
}

#endif
