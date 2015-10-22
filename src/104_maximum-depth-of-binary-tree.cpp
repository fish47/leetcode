#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <ctime>
#include <vector>


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
    int maxDepth(TreeNode *root)
    {
        if (!root)
            return 0;

        // 默认从根结点出发，树高度为 1
        int ret = 0;
        std::vector<TreeNode*> nodeStack;
        nodeStack.push_back(root);

        // 下面使用中序遍历
        while (!nodeStack.empty())
        {
            // 尽可能走左子树的尽头
            TreeNode *node = nodeStack.back();
            while (node->left)
            {
                nodeStack.push_back(node->left);
                node = node->left;
            }
            ret = std::max(ret, (int) nodeStack.size());


            if (node->right)
            {
                // 步入右子树
                nodeStack.push_back(node->right);
            }
            else
            {
                // 左子树已走尽，又没有右结点，说明是叶子结点
                while (true)
                {
                    TreeNode *childNode = nodeStack.back();
                    nodeStack.pop_back();

                    // 根结点的左右子树都遍历完
                    if (nodeStack.empty())
                        break;

                    // 如果 childNode == parentNode->right ，说明 parentNode 的所有子树都遍历完
                    TreeNode *parentNode = nodeStack.back();
                    TreeNode *rightNode = parentNode->right;
                    if (rightNode && childNode == parentNode->left)
                    {
                        nodeStack.push_back(rightNode);
                        break;
                    }
                }
            }
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static TreeNode* generateRandomBinaryTree(TreeNode *pNodes, int nodeCount)
{
    std::srand(std::time(0));
    std::memset(pNodes, 0, sizeof(TreeNode) * nodeCount);

    for (int i = 1; i < nodeCount; ++i)
    {
        TreeNode *pNewNode = &pNodes[i];
        while (true)
        {
            bool leftNode = (bool) (std::rand() % 2);
            TreeNode *parent = &pNodes[std::rand() % i];
            TreeNode **ppNode = leftNode ? &parent->left : &parent->right;
            if (!*ppNode)
            {
                *ppNode = pNewNode;
                break;
            }
        }
    }

    return pNodes;
}


static int getMaxBinaryTreeDepth(TreeNode *root, int rootDepth)
{
    if (!root)
        return rootDepth - 1;

    int leftTreeDepth = getMaxBinaryTreeDepth(root->left, rootDepth + 1);
    int rightTreeDepth = getMaxBinaryTreeDepth(root->right, rootDepth + 1);
    return std::max(leftTreeDepth, rightTreeDepth);
}


int main()
{
    TreeNode nodes[20];
    Solution solution;

    for (int i = 0; i < 100000; ++i)
    {
        int nodeCount = sizeof(nodes) / sizeof(TreeNode);
        TreeNode *root = generateRandomBinaryTree((TreeNode*) nodes, nodeCount);
        int ret1 = solution.maxDepth(root);
        int ret2 = getMaxBinaryTreeDepth(root, 1);

        if (ret1 != ret2)
        {
            std::printf("Bang!\n");
            break;
        }
    }

    return 0;
}
#endif
