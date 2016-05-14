#include <iostream>
#include <vector>
#include <functional>
#include <ctime>


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
    static bool pushNodeIfNotNull(std::vector<TreeNode*> *pNodes, TreeNode *pNode)
    {
        if (pNodes && pNode)
        {
            pNodes->push_back(pNode);
            return true;
        }

        return false;
    }

    static bool visitNode(TreeNode *pNode, int *pIterCount, int maxCount, int *pOutValue)
    {
        if (pNode && pIterCount && pOutValue)
        {
            // 题目用的 k 是 1-based 所以要先自增
            ++(*pIterCount);
            if (*pIterCount == maxCount)
            {
                *pOutValue = pNode->val;
                return true;
            }
        }

        return false;
    }


public:
    int kthSmallest(TreeNode *pRoot, int k)
    {
        if (!pRoot)
            return 0;

        auto ret = 0;
        auto iterCount = 0;
        std::vector<TreeNode*> nodes;
        nodes.push_back(pRoot);
        while (!nodes.empty())
        {
            TreeNode *pNode = nodes.back();
            if (pushNodeIfNotNull(&nodes, pNode->left))
                continue;

            if (visitNode(pNode, &iterCount, k, &ret))
                break;

            if (pushNodeIfNotNull(&nodes, pNode->right))
                continue;

            bool found = false;
            TreeNode *pChild = pNode;
            TreeNode *pParent = nullptr;
            while (true)
            {
                nodes.pop_back();
                if (nodes.empty())
                    break;

                // 遍历完左子树的话，先回溯到父结点，再开始遍历右子树，如果有的话
                pParent = nodes.back();
                if (pChild == pParent->left)
                {
                    found = visitNode(pParent, &iterCount, k, &ret);
                    if (pushNodeIfNotNull(&nodes, pParent->right))
                        break;
                }

                pChild = pParent;
            }

            if (found)
                break;
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static void inorderTraverseTree(TreeNode *pRoot, std::function<void(TreeNode*)> func)
{
    if (!pRoot)
        return;

    inorderTraverseTree(pRoot->left, func);
    func(pRoot);
    inorderTraverseTree(pRoot->right, func);
}


static TreeNode* generateRandomBinarySearchTree(std::vector<TreeNode> *pNodes, int count)
{
    if (!pNodes || count <= 0)
        return nullptr;

    pNodes->clear();
    pNodes->reserve(count);
    for (auto i = 0; i < count; ++i)
    {
        pNodes->emplace_back(i);
        if (i == 0)
            continue;

        while (true)
        {
            TreeNode &parent = (*pNodes)[std::rand() % i];
            TreeNode **ppChild = (std::rand() % 2) ? &parent.left : &parent.right;
            if (!*ppChild)
            {
                *ppChild = &pNodes->back();
                break;
            }
        }
    }

    auto nodeValue = 0;
    TreeNode *pRoot = &pNodes->front();
    inorderTraverseTree(pRoot, [&nodeValue](TreeNode *pNode) { pNode->val = nodeValue++; });
    return pRoot;
}


static bool doTest(std::vector<TreeNode> *pNodes, Solution &solution)
{
    auto nodeCount = std::rand() % 100;
    TreeNode *pRoot = generateRandomBinarySearchTree(pNodes, nodeCount);
    for (auto i = 0; i < nodeCount; ++i)
    {
        // 题目用 1-based
        auto ret = solution.kthSmallest(pRoot, i + 1);
        if (ret != i)
            return false;
    }

    return true;
}


int main()
{
    Solution solution;
    std::vector<TreeNode> nodes;
    std::srand(std::time(nullptr));
    for (auto i = 0; i < 1000; ++i)
    {
        bool ret = doTest(&nodes, solution);
        if (!ret)
        {
            std::cout << "Test failed" << std::endl;
            break;
        }
    }
    return 0;
}

#endif
