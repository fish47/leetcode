#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>


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
public:
    std::vector<int> preorderTraversal(TreeNode *pRoot)
    {
        std::vector<int> ret;
        if (!pRoot)
            return ret;

        std::vector<TreeNode*> nodeQueue;
        nodeQueue.push_back(pRoot);
        while (!nodeQueue.empty())
        {
            TreeNode *pNode = nodeQueue.back();
            ret.push_back(pNode->val);
            nodeQueue.pop_back();

            if (pNode->right)
                nodeQueue.push_back(pNode->right);

            if (pNode->left)
                nodeQueue.push_back(pNode->left);
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static TreeNode* generateRandomBinaryTree(std::vector<TreeNode> *pNodes, int nodeCount)
{
    pNodes->clear();
    pNodes->reserve(nodeCount);
    for (auto i = 0; i < nodeCount; ++i)
    {
        pNodes->emplace_back(i);
        if (i == 0)
            continue;

        while (true)
        {
            TreeNode &parent = (*pNodes)[std::rand() % i];
            TreeNode **ppChild = (std::rand() % 1) ? &parent.left : &parent.right;
            if (!*ppChild)
            {
                *ppChild = &pNodes->back();
                break;
            }
        }
    }

    return pNodes->empty() ? nullptr : &pNodes->front();
}

static void calcPreorderTraversalResult(TreeNode *pNode, std::vector<int> *pResult)
{
    if (!pNode || !pResult)
        return;

    pResult->push_back(pNode->val);
    calcPreorderTraversalResult(pNode->left, pResult);
    calcPreorderTraversalResult(pNode->right, pResult);
}


int main()
{
    Solution solution;
    std::vector<TreeNode> nodes;
    std::vector<int> result;

    std::srand(std::time(nullptr));
    for (auto i = 0; i < 1000; ++i)
    {
        auto nodeCount = std::rand() % 100;
        TreeNode *pRoot = generateRandomBinaryTree(&nodes, nodeCount);
        std::vector<int> ret = solution.preorderTraversal(pRoot);
        result.clear();
        calcPreorderTraversalResult(pRoot, &result);
        if (result != ret)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }

    return 0;
}

#endif
