#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <functional>
#include <algorithm>
#include <cmath>


#ifdef LEETCODE_DEBUG
struct TreeNode
{
    int         val;
    TreeNode    *left;
    TreeNode    *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr)
    {}
};
#endif


class Solution
{
private:
    static TreeNode* doCreateBalancedBinaryTree(int count)
    {
        if (count <= 0)
            return nullptr;

        TreeNode *pRoot = new TreeNode(0);
        std::queue<TreeNode*> nodesQueue;
        nodesQueue.push(pRoot);
        for (auto i = 1; i < count; ++i)
        {
            TreeNode *pNewNode = new TreeNode(0);
            TreeNode *pNode = nodesQueue.front();
            if (!pNode->left)
            {
                pNode->left = pNewNode;
            }
            else
            {
                pNode->right = pNewNode;
                nodesQueue.pop();
            }
            nodesQueue.push(pNewNode);
        }

        return pRoot;
    }


    static bool pushNodeIfNotNull(std::vector<TreeNode*> *pNodes, TreeNode *pNode)
    {
        if (!pNodes || !pNode)
            return false;

        pNodes->push_back(pNode);
        return true;
    }


    static void doInorderTraverseTree(TreeNode *pRoot, std::function<void(TreeNode*)> func)
    {
        if (!pRoot)
            return;

        std::vector<TreeNode*> nodes;
        nodes.push_back(pRoot);
        while (!nodes.empty())
        {
            TreeNode *pNode = nodes.back();
            if (pushNodeIfNotNull(&nodes, pNode->left))
                continue;

            func(pNode);

            if (pushNodeIfNotNull(&nodes, pNode->right))
                continue;

            TreeNode *pChild = pNode;
            nodes.pop_back();
            while (!nodes.empty())
            {
                TreeNode *pParent = nodes.back();
                if (pParent->left == pChild)
                {
                    func(pParent);
                    if (pushNodeIfNotNull(&nodes, pParent->right))
                        break;
                }

                nodes.pop_back();
                pChild = pParent;
            }
        }
    }


public:
    TreeNode* sortedArrayToBST(std::vector<int> &nums)
    {
        auto idx = 0;
        TreeNode *pRoot = doCreateBalancedBinaryTree(nums.size());
        doInorderTraverseTree(pRoot, [&nums, &idx](TreeNode *pNode) { pNode->val = nums[idx++]; });
        return pRoot;
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

static int calcTreeDepth(TreeNode *pRoot)
{
    if (!pRoot)
        return 0;

    return 1 + std::max(calcTreeDepth(pRoot->left), calcTreeDepth(pRoot->right));
}


static bool doTest(Solution &solution,
                   std::vector<TreeNode*> *pNodes,
                   std::vector<int> *pNums1,
                   std::vector<int> *pNums2,
                   std::map<TreeNode*, int> *pLevels,
                   int count)
{
    if (!pNodes || !pNums1 || !pNums2 || !pLevels || count < 0)
        return false;

    pNodes->clear();
    pNums1->clear();
    pNums2->clear();
    pLevels->clear();

    auto startNum = 1000;
    std::generate_n(std::back_inserter(*pNums1), count, [&startNum]() { return startNum++; });

    TreeNode *pRoot = solution.sortedArrayToBST(*pNums1);

    // 对比中序遍历结果
    bool ret = true;
    inorderTraverseTree(pRoot, [pNums2](TreeNode *pNode) { pNums2->push_back(pNode->val); });
    ret = ret && (*pNums1 == *pNums2);

    // 二叉树深度
    auto maxLevel = calcTreeDepth(pRoot);
    if (count > 0)
        ret = ret && (std::pow(2, maxLevel - 1) <= count && count < std::pow(2, maxLevel));

    // 销毁树
    inorderTraverseTree(pRoot, [pNodes](TreeNode *pNode) { pNodes->push_back(pNode); });
    std::for_each(pNodes->cbegin(), pNodes->cend(), [](const TreeNode *pNode) { delete pNode; });

    return ret;
}


int main()
{
    Solution solution;
    std::vector<TreeNode*> nodes;
    std::vector<int> nums1;
    std::vector<int> nums2;
    std::map<TreeNode*, int> levels;
    for (auto i = 0; i < 1000; ++i)
    {
        if (!doTest(solution, &nodes, &nums1, &nums2, &levels, i))
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
