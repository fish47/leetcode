#include <iostream>
#include <vector>
#include <deque>


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
    std::vector<int> rightSideView(TreeNode *pRoot)
    {
        std::vector<int> ret;
        if (!pRoot)
            return ret;

        TreeNode *pLastNodeOfCurLevel = pRoot;
        std::deque<TreeNode*> sameLevelNodes;
        sameLevelNodes.push_back(pRoot);
        while (!sameLevelNodes.empty())
        {
            TreeNode *pNode = sameLevelNodes.front();
            sameLevelNodes.pop_front();

            if (pNode->left)
                sameLevelNodes.push_back(pNode->left);

            if (pNode->right)
                sameLevelNodes.push_back(pNode->right);

            // 题目意思就是收集每层最后一个结点
            if (pNode == pLastNodeOfCurLevel)
            {
                ret.push_back(pNode->val);
                pLastNodeOfCurLevel = sameLevelNodes.empty() ? nullptr : sameLevelNodes.back();
            }
        }

        return ret;
    }
};


#ifdef LEETCODE_DEBUG

static TreeNode* createTreeFromSerializedData(std::vector<TreeNode> *pNodes, std::vector<int> &nums)
{
    if (!pNodes || nums.empty())
        return nullptr;

    auto &nodes = *pNodes;
    auto dataSize = nums.size();
    nodes.clear();
    nodes.resize(dataSize);
    for (auto i = 0; i < dataSize; ++i)
    {
        auto &node = nodes[i];
        node.left = nullptr;
        node.right = nullptr;
        node.val = nums[i];
        if (node.val <= 0)
            continue;

        // 根结点没有父结点
        if (i == 0)
            continue;

        auto &parent = nodes[(i - 1) / 2];
        auto &branch = (i & 1) ? parent.left : parent.right;
        branch = &node;
    }

    return &nodes.front();
}


static void doTest(std::vector<int> serializedData, std::vector<int> expected)
{
    std::vector<TreeNode> nodes;
    TreeNode *pRoot = createTreeFromSerializedData(&nodes, serializedData);
    Solution solution;
    auto ret = solution.rightSideView(pRoot);
    if (ret != expected)
        std::cout << "Test failed." << std::endl;
}


int main()
{
    doTest({}, {});
    doTest({ 1, 2 }, { 1, 2 });
    doTest({ 1, 0, 3 }, { 1, 3 });
    doTest({ 1, 2, 3 }, { 1, 3 });
    doTest({ 1, 2, 3, 0, 5, 0, 4 }, { 1, 3, 4 });
    return 0;
}

#endif
