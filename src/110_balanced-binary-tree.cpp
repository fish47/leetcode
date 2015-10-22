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
#include <memory>
#include <cstring>


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


class Solution
{
private:
    struct IterateContext
    {
        TreeNode    *pNode;
        int         *pReturn;
        int         nLeftHeight;
        int         nRightHeight;
    };


    void pushNextNode(std::vector<IterateContext> *pVecContexts,
                      TreeNode *pNextNode,
                      int *pReturn)
    {
        pVecContexts->resize(pVecContexts->size() + 1);

        IterateContext &newCtx = pVecContexts->back();
        newCtx.pNode = pNextNode;
        newCtx.pReturn = pReturn;
        newCtx.nLeftHeight = INT_MIN;
        newCtx.nRightHeight = INT_MIN;
    }


public:
    bool isBalanced(TreeNode* pRoot)
    {
        if (!pRoot)
            return true;


        std::vector<IterateContext> vecContexts;
        pushNextNode(&vecContexts, pRoot, nullptr);

        while (!vecContexts.empty())
        {
            IterateContext &topCtx = vecContexts.back();
            TreeNode *pNode = topCtx.pNode;

            if (topCtx.nLeftHeight < 0)
            {
                TreeNode *pLeft = pNode->left;
                if (pLeft)
                {
                    pushNextNode(&vecContexts, pLeft, &topCtx.nLeftHeight);
                    continue;
                }

                topCtx.nLeftHeight = 0;
            }

            if (topCtx.nRightHeight < 0)
            {
                TreeNode *pRight = pNode->right;
                if (pRight)
                {
                    pushNextNode(&vecContexts, pRight, &topCtx.nRightHeight);
                    continue;
                }

                topCtx.nRightHeight = 0;
            }


            // 达到不平衡条件，提早退出吧
            int leftH = topCtx.nLeftHeight;
            int rightH = topCtx.nRightHeight;
            if (std::abs(leftH - rightH) > 1)
                return false;


            if (topCtx.pReturn)
                *topCtx.pReturn = std::max(leftH, rightH) + 1;

            vecContexts.pop_back();
        }


        return true;
    }
};



#ifdef LEETCODE_DEBUG

static void calcIsBalanced(TreeNode *pNode, int *pHeight, bool *pIsBalanced)
{
    if (!pNode)
    {
        *pHeight = 0;
        *pIsBalanced = true;
        return;
    }

    bool isLeftBalanced = false;
    bool isRightBalanced = false;
    int leftHeight = 0;
    int rightHeight = 0;

    calcIsBalanced(pNode->left, &leftHeight, &isLeftBalanced);
    calcIsBalanced(pNode->right, &rightHeight, &isRightBalanced);

    *pHeight = std::max(leftHeight, rightHeight) + 1;
    *pIsBalanced = isLeftBalanced
                   && isRightBalanced
                   && (std::abs(leftHeight - rightHeight) <= 1);
}


static TreeNode* generateRandomTree(std::mt19937 &randomEngine,
                                    std::vector<TreeNode> *pVecNodes)
{
    std::uniform_int_distribution<> randomNodeCount(1, 100);
    int nodeCount = randomNodeCount(randomEngine);
    pVecNodes->resize(nodeCount);

    for (int i = 0; i < nodeCount; ++i)
    {
        TreeNode &node = pVecNodes->at(i);
        node.left = nullptr;
        node.right = nullptr;
        node.val = i;

        if (i == 0)
            continue;

        TreeNode **ppNode = nullptr;
        std::uniform_int_distribution<> randomSelectNodeIdx(0, i - 1);
        std::uniform_int_distribution<> randomSelectLeft(0, 1);
        while (true)
        {
            int nodeIdx = randomSelectNodeIdx(randomEngine);
            bool selectLeft = randomSelectLeft(randomEngine);
            TreeNode &randomNode = pVecNodes->at(nodeIdx);
            ppNode = selectLeft ? &randomNode.left : &randomNode.right;

            if (!*ppNode)
                break;
        }

        *ppNode = &node;
    }

    return &pVecNodes->at(0);
}


int main()
{
    std::mt19937 randomEngine;
    Solution solution;
    std::vector<TreeNode> vecNodes;

    for (int i = 0; i < 10000; ++i)
    {
        TreeNode *pRoot = generateRandomTree(randomEngine, &vecNodes);
        bool ret1 = solution.isBalanced(pRoot);
        bool ret2 = false;
        int height = 0;
        calcIsBalanced(pRoot, &height, &ret2);
        if (ret1 != ret2)
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
