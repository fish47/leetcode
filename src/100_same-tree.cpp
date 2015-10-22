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


static bool isSameWithNodeValue(TreeNode *node1, TreeNode *node2)
{
    // 包括双方都为 NULL 的情况
    if (node1 == node2)
        return true;

    // 也就是其中一方为 NULL
    if (!node1 || !node2)
        return false;

    if (!node1->left != !node2->left)
        return false;

    if (!node1->right != !node2->right)
        return false;

    return (node1->val == node2->val);
}


class Solution
{
public:
    bool isSameTree(TreeNode* root1, TreeNode* root2)
    {
        if (!root1 && !root2)
            return true;

        // 特判根结点
        if (!isSameWithNodeValue(root1, root2))
            return false;


#ifndef LEETCODE_DEBUG
        // 测试中有可能传同一棵树，走最笨的流程吧
        if (root1 == root2)
            return true;
#endif

        std::vector<TreeNode*> nodeStack1;
        std::vector<TreeNode*> nodeStack2;

        nodeStack1.push_back(root1);
        nodeStack2.push_back(root2);

        while (!nodeStack1.empty())
        {
            // 尽可能遍历左结点
            TreeNode *node1 = nodeStack1.back();
            TreeNode *node2 = nodeStack2.back();
            while (node1->left)
            {
                node1 = node1->left;
                node2 = node2->left;
                if (!isSameWithNodeValue(node1, node2))
                    return false;

                nodeStack1.push_back(node1);
                nodeStack2.push_back(node2);
            }


            if (node1->right)
            {
                // 结点只有右子树
                node1 = node1->right;
                node2 = node2->right;
                if (!isSameWithNodeValue(node1, node2))
                    return false;

                nodeStack1.push_back(node1);
                nodeStack2.push_back(node2);
            }
            else
            {
                while (true)
                {
                    TreeNode *childNode1 = nodeStack1.back();
                    TreeNode *childNode2 = nodeStack2.back();
                    nodeStack1.pop_back();
                    nodeStack2.pop_back();

                    // 当所有子树都遍历完时
                    if (nodeStack1.empty())
                        break;

                    // 遍历完 parentNode 的左子树，再遍历其右子树
                    TreeNode *parentNode1 = nodeStack1.back();
                    TreeNode *parentNode2 = nodeStack2.back();
                    if (parentNode1->right && parentNode1->left == childNode1)
                    {
                        if (parentNode2->right && parentNode2->left == childNode2)
                        {
                            node1 = parentNode1->right;
                            node2 = parentNode2->right;
                            if (!isSameWithNodeValue(node1, node2))
                                return false;

                            nodeStack1.push_back(node1);
                            nodeStack2.push_back(node2);
                            break;
                        }
                        else
                        {
                            // 结构会不会不一样？
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }
};



#ifdef LEETCODE_DEBUG

static TreeNode* generateRandomBinaryTree(TreeNode *nodes, int nodeCount)
{
    for (int i = 0; i < nodeCount; ++i)
    {
        nodes[i].left = nullptr;
        nodes[i].right = nullptr;
        nodes[i].val = i;
    }

    for (int i = 1; i < nodeCount; ++i)
    {
        bool addToLeftNode = (bool) (std::rand() % 2);
        TreeNode *newNode = &nodes[i];

        while (true)
        {
            TreeNode *parentNode = &nodes[std::rand() % i];
            TreeNode **nodePointer = addToLeftNode ? &parentNode->left : &parentNode->right;
            if (!*nodePointer)
            {
                *nodePointer = newNode;
                break;
            }
        }
    }

    return nodes;
}


static bool isSameTree(TreeNode *root1, TreeNode *root2)
{
    if (root1 == root2)
        return true;

    return isSameWithNodeValue(root1, root2)
           && isSameTree(root1->left, root2->left)
           && isSameTree(root1->right, root2->right);
}


int main()
{
    TreeNode nodes1[100];
    TreeNode nodes2[100];
    Solution solution;

    std::srand(std::time(0));

    for (int i = 0; i < 100000; ++i)
    {
        // 同一棵树结构肯定是一样的
        TreeNode *root = generateRandomBinaryTree((TreeNode*) nodes1, sizeof(nodes1) / sizeof(TreeNode));
        if (!solution.isSameTree(root, root))
        {
            std::printf("Bang!\n");
            break;
        }

        // 再试一下可能不同构的树
        int nodeCount1 = std::rand() % 10 + 1;
        int nodeCount2 = std::rand() % 10 + 1;
        TreeNode *root1 = generateRandomBinaryTree((TreeNode*) nodes1, nodeCount1);
        TreeNode *root2 = generateRandomBinaryTree((TreeNode*) nodes2, nodeCount2);
        if (isSameTree(root1, root2) != solution.isSameTree(root1, root2))
        {
            std::printf("Bang!\n");
            break;
        }
    }

    return 0;
}

#endif
