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
    std::vector<int> inorderTraversal(TreeNode *pRoot)
    {
        std::vector<int> ret;
        if (!pRoot)
            return ret;

        std::vector<TreeNode*> nodes;
        nodes.push_back(pRoot);
        while (!nodes.empty())
        {
            // 尽可能遍历左子树
            TreeNode *pNode = nodes.back();
            if (pNode->left)
            {
                nodes.push_back(pNode->left);
                continue;
            }

            ret.push_back(pNode->val);

            // 没有左子树，直接遍右子树
            if (pNode->right)
            {
                nodes.push_back(pNode->right);
                continue;
            }


            // 遇到叶子结点就开始回溯，然后找下一次开始遍历的结点
            TreeNode *pChild = pNode;
            while (true)
            {
                nodes.pop_back();
                if (nodes.empty())
                    break;

                TreeNode *pParent = nodes.back();
                if (pChild == pParent->left)
                {
                    // 左子树遍历完，继续遍历右子树，如果有的话
                    ret.push_back(pParent->val);
                    if (pParent->right)
                    {
                        nodes.push_back(pParent->right);
                        break;
                    }
                }

                pChild = pParent;
            }
        }

        return ret;
    }
};



static TreeNode* generateRandomBinaryTree(std::vector<TreeNode> *pNodes, int nodeCount)
{
    if (!pNodes || nodeCount <= 0)
        return nullptr;

    pNodes->clear();
    pNodes->reserve(nodeCount);
    pNodes->emplace_back(0);
    for (auto i = 1; i < nodeCount; ++i)
    {
        pNodes->emplace_back(i);
        while (true)
        {
            auto &parent = pNodes->at(std::rand() % i);
            auto **ppChild = (std::rand() % 1) ? &parent.left : &parent.right;
            if (!*ppChild)
            {
                *ppChild = &pNodes->back();
                break;
            }
        }
    }

    return &pNodes->front();
}


static void calcInorderTraversalResult(TreeNode *pNode, std::vector<int> *pResult)
{
    if (!pNode || !pResult)
        return;

    calcInorderTraversalResult(pNode->left, pResult);
    pResult->push_back(pNode->val);
    calcInorderTraversalResult(pNode->right, pResult);
}


#ifdef LEETCODE_DEBUG

int main()
{
    Solution solution;
    std::vector<TreeNode> nodes;
    std::vector<int> result;
    std::srand(std::time(nullptr));
    for (auto i = 0; i < 10000; ++i)
    {
        auto nodeCount = std::rand() % 100;
        TreeNode *pHead = generateRandomBinaryTree(&nodes, nodeCount);
        auto ret = solution.inorderTraversal(pHead);
        result.clear();
        calcInorderTraversalResult(pHead, &result);
        if (ret != result)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return  0;
}

#endif
