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

    void reset()
    {
        left = nullptr;
        right = nullptr;
        val = 0;
    }
};
#endif


class Solution
{
public:
    bool isSymmetric(TreeNode *pRoot)
    {
        if (!pRoot)
            return true;

        std::vector<TreeNode*> vecNodes;
        vecNodes.push_back(pRoot->left);
        vecNodes.push_back(pRoot->right);

        while (!vecNodes.empty())
        {
            int nodeCount = vecNodes.size();
            TreeNode *pLeft = vecNodes[nodeCount - 1];
            TreeNode *pRight = vecNodes[nodeCount - 2];
            vecNodes.pop_back();
            vecNodes.pop_back();

            // 左右根都是空结点
            if (!pLeft && !pRight)
                continue;

            // 其中一个根结点为空
            if (!pLeft || !pRight)
                return false;

            // 根结点值不相同
            if (pLeft->val != pRight->val)
                return false;


            // 有可能左根有左子树，右根没有右子树，或反之
            // 这些情况留到下一轮处理
            vecNodes.push_back(pLeft->left);
            vecNodes.push_back(pRight->right);

            vecNodes.push_back(pLeft->right);
            vecNodes.push_back(pRight->left);
        }

        return true;
    }
};



#ifdef LEETCODE_DEBUG

static TreeNode** selectNodeChild(TreeNode *pNode, bool needToSelectLeft)
{
    return needToSelectLeft ? &pNode->left : &pNode->right;
}

static TreeNode* generateSymetricTree(std::mt19937 &randomEngine,
                                      std::vector<TreeNode> *pVecNodes)
{
    std::uniform_int_distribution<> randomSelectNode(0, 1);
    std::uniform_int_distribution<> randonNodeCount(1, 100);
    int halfNodeCount = randonNodeCount(randomEngine);
    int nodeCount = halfNodeCount * 2;
    pVecNodes->resize(nodeCount + 1);

    TreeNode *pRoot = &pVecNodes->at(nodeCount);
    pRoot->reset();
    pRoot->val = halfNodeCount;

    TreeNode *pRootLeft = &pVecNodes->at(0);
    TreeNode *pRootRight = &pVecNodes->at(halfNodeCount);
    pRootLeft->reset();
    pRootLeft->val = 0;
    pRootRight->reset();
    pRootRight->val = 0;

    pRoot->left = pRootLeft;
    pRoot->right = pRootRight;


    for (int i = 1; i < halfNodeCount; ++i)
    {
        int appendNodeIdx = 0;
        bool needToSelectLeft = randomSelectNode(randomEngine);
        std::uniform_int_distribution<> randomNodeIdx(0, i - 1);
        while (true)
        {
            appendNodeIdx = randomNodeIdx(randomEngine);
            TreeNode *pNode = &pVecNodes->at(appendNodeIdx);
            TreeNode **ppChild = selectNodeChild(pNode, needToSelectLeft);
            if (!*ppChild)
                break;
        }


        // [0, nodeCount) 的结点是对称轴左侧
        // [nodeCount, nodeCount * 2) 的结点是对称轴右侧
        TreeNode *pNewNode1 = &pVecNodes->at(i);
        TreeNode *pNewNode2 = &pVecNodes->at(i + halfNodeCount);
        pNewNode1->reset();
        pNewNode1->val = i;
        pNewNode2->reset();
        pNewNode2->val = i;


        TreeNode *pAppendNode1 = &pVecNodes->at(appendNodeIdx);
        TreeNode *pAppendNode2 = &pVecNodes->at(appendNodeIdx + halfNodeCount);
        TreeNode **ppChild1 = selectNodeChild(pAppendNode1, needToSelectLeft);
        TreeNode **ppChild2 = selectNodeChild(pAppendNode2, !needToSelectLeft);
        *ppChild1 = pNewNode1;
        *ppChild2 = pNewNode2;
    }

    return pRoot;
}


static bool isSymmetricTree(TreeNode *pLeft, TreeNode *pRight)
{
    if (!pLeft && !pRight)
        return true;

    // 其中一个为空，但另一个不为空
    if (!pLeft != !pRight)
        return false;

    if (pLeft->val != pRight->val)
        return false;

    if (!isSymmetricTree(pLeft->left, pRight->right))
        return false;

    if (!isSymmetricTree(pLeft->right, pRight->left))
        return false;

    return true;
}


int main()
{
    std::mt19937 randomEngine;
    Solution solution;
    std::vector<TreeNode> vecNodes;

    for (int i = 0; i < 10000; ++i)
    {
        TreeNode *pRoot = generateSymetricTree(randomEngine, &vecNodes);
        bool ret1 = solution.isSymmetric(pRoot);
        bool ret2 = isSymmetricTree(pRoot->left, pRoot->right);
        if (ret1 != ret2)
        {
            std::printf("Test failed.\n");
            break;
        }
    }

    return 0;
}

#endif
