#include <iostream>
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
private:
    static const int    kNoChild    = -1;

private:
    static void resolveTreeNodeIndexes(TreeNode *pRoot,
                                       std::vector<TreeNode*> *pNodes,
                                       std::vector<int> *pLeftNodeIndexes,
                                       std::vector<int> *pRightNodeIndexes)
    {
        if (!pRoot || !pNodes || !pLeftNodeIndexes || !pRightNodeIndexes)
            return;

        pNodes->push_back(pRoot);
        for (auto i = 0; i < pNodes->size(); ++i)
        {
            auto leftChildIdx = kNoChild;
            auto rightChildIdx = kNoChild;
            TreeNode *pNode = (*pNodes)[i];
            
            if (pNode->left)
            {
                pNodes->push_back(pNode->left);
                leftChildIdx = pNodes->size() - 1;
            }

            if (pNode->right)
            {
                pNodes->push_back(pNode->right);
                rightChildIdx = pNodes->size() - 1;
            }

            pLeftNodeIndexes->push_back(leftChildIdx);
            pRightNodeIndexes->push_back(rightChildIdx);
        }
    }

public:
    int rob(TreeNode *pRoot)
    {
        /*
         * 设 f(i, 1) 为如果取 i 结点及子树后的最大收益，而 f(i, 0) 则为不取时的最大收益。
         * 注意以下性质：
         * 1. 如果根结点取了，两个子结点不能取；
         * 2. 如果根结点不取，两个子结点可取可不取；
         */

        if (!pRoot)
            return 0;

        // 将整棵树按水平遍历编号，记录每个结点的父结点索引
        std::vector<TreeNode*> nodes;
        std::vector<int> leftNodeIndexes;
        std::vector<int> rightNodeIndexes;
        resolveTreeNodeIndexes(pRoot, &nodes, &leftNodeIndexes, &rightNodeIndexes);

        int nodeCount = nodes.size();
        std::vector<int> includeDP(nodeCount, 0);
        std::vector<int> excludeDP(nodeCount, 0);
        for (int i = nodeCount - 1; i >= 0; --i)
        {
            TreeNode *pNode = nodes[i];
            auto leftIdx = leftNodeIndexes[i];
            auto rightIdx = rightNodeIndexes[i];
            bool hasLeft = (leftIdx != kNoChild);
            bool hasRight = (rightIdx != kNoChild);
            auto leftIncludeVal  = hasLeft  ? includeDP[leftIdx]  : 0;
            auto rightIncludeVal = hasRight ? includeDP[rightIdx] : 0;
            auto leftExcludeVal  = hasLeft  ? excludeDP[leftIdx]  : 0;
            auto rightExcludeVal = hasRight ? excludeDP[rightIdx] : 0;

            // 结点有没有可能是负值？
            includeDP[i] = std::max(pNode->val + leftExcludeVal + rightExcludeVal, 0);

            auto leftMaxVal = std::max(leftIncludeVal, leftExcludeVal);
            auto rightMaxVal = std::max(rightIncludeVal, rightExcludeVal);
            excludeDP[i] = std::max(leftMaxVal + rightMaxVal, 0);
        }

        return std::max(includeDP[0], excludeDP[0]);
    }
};


#ifdef LEETCODE_DEBUG


static TreeNode* buildTreeFromSerializedArray(std::vector<TreeNode> *pNodes, std::vector<int> &nums)
{
    if (!pNodes || nums.empty())
        return nullptr;

    auto numCount = nums.size();
    pNodes->clear();
    pNodes->resize(numCount);
    for (auto i = 0; i < numCount; ++i)
    {
        auto val = nums[i];
        TreeNode &node = (*pNodes)[i];
        node.val = val;
        node.left = nullptr;
        node.right = nullptr;

        if (i == 0)
            continue;

        // 如果值为零表示空结点
        TreeNode &parent = (*pNodes)[(i - 1) / 2];
        TreeNode **ppChild = (i & 1) ? &parent.left : &parent.right;
        *ppChild = (val == 0) ? nullptr : &node;
    }

    return &pNodes->front();
}


static void doTest(int expected, std::vector<int> nums)
{
    Solution solution;
    std::vector<TreeNode> nodes;
    TreeNode *pRoot = buildTreeFromSerializedArray(&nodes, nums);
    auto ret = solution.rob(pRoot);
    if (ret != expected)
        std::cout << "Test failed." << std::endl;
}


int main()
{
    doTest(7, { 3, 2, 3, 0, 3, 0, 1 });
    doTest(9, { 3, 4, 5, 1, 3, 0, 1 });
    doTest(7, { 4, 1, 0, 2, 0, 0, 0, 3 });
    return 0;
}

#endif
