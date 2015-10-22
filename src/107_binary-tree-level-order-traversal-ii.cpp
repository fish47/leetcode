#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <list>


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
    typedef std::vector<int>            NodeValues;
    typedef std::vector<NodeValues>     VecNodeValues;

    VecNodeValues levelOrderBottom(TreeNode *pRoot)
    {
        NodeValues tmpNodeValues;
        VecNodeValues vecNodeValues;
        std::list<TreeNode*> lstNodeQueue;

        if (!pRoot)
            return vecNodeValues;

        lstNodeQueue.push_back(pRoot);
        auto itLastNodeOfCurLevel = lstNodeQueue.cbegin();

        while (!lstNodeQueue.empty())
        {
            TreeNode *pNode = lstNodeQueue.front();
            tmpNodeValues.push_back(pNode->val);

            if (pNode->left)
                lstNodeQueue.push_back(pNode->left);

            if (pNode->right)
                lstNodeQueue.push_back(pNode->right);

            // 当前深度的最后一个结点
            if (pNode == *itLastNodeOfCurLevel)
            {
                vecNodeValues.push_back(tmpNodeValues);
                tmpNodeValues.clear();

                // 下一层的最后一个结点
                itLastNodeOfCurLevel = lstNodeQueue.end();
                --itLastNodeOfCurLevel;
            }

            lstNodeQueue.pop_front();
        }

        std::reverse(vecNodeValues.begin(), vecNodeValues.end());
        return vecNodeValues;
    }
};



#ifdef LEETCODE_DEBUG


static TreeNode* generateRandomTree(std::mt19937 &randomEngine,
                                    std::vector<TreeNode> *pVecNodes)
{
    std::uniform_int_distribution<> randomNodeCount(1, 100);
    std::uniform_int_distribution<> randomSelectLeft(0, 1);

    int nodeCount = randomNodeCount(randomEngine);
    pVecNodes->resize(nodeCount);

    for (int i = 0; i < nodeCount; ++i)
    {
        TreeNode &newNode = pVecNodes->at(i);
        newNode.reset();
        newNode.val = i;

        TreeNode **ppChild = nullptr;
        for (int j = 0; j < i; ++j)
        {
            TreeNode &node = pVecNodes->at(j);
            bool needToSelectLeft = randomSelectLeft(randomEngine);
            ppChild = needToSelectLeft ? &node.left : &node.right;
            if (!*ppChild)
                break;
        }

        if (ppChild)
            *ppChild = &newNode;
    }

    return &pVecNodes->at(0);
}


static TreeNode* doCreateTreeBySerializedArray(std::vector<int> &vecData,
                                               std::vector<TreeNode> *pVecNodes)
{
    pVecNodes->resize(vecData.size());

    for (int i = 0, n = vecData.size(); i < n; ++i)
    {
        int nodeVal = vecData[i];
        TreeNode &node = pVecNodes->at(i);
        node.reset();
        node.val = nodeVal;

        if (i == 0)
            continue;

        bool isLeftChild = (i & 1);
        bool isNullNode = (nodeVal <= 0);
        TreeNode &parent = pVecNodes->at((i - 1) / 2);
        TreeNode **ppChild = isLeftChild ? &parent.left : &parent.right;
        *ppChild = isNullNode ? nullptr : &node;
    }

    return &pVecNodes->at(0);
}


static void doTest(std::vector<int> vecTreeData,
                   Solution::VecNodeValues expected)
{
    std::vector<TreeNode> vecNodes;
    TreeNode *pRoot = doCreateTreeBySerializedArray(vecTreeData, &vecNodes);
    Solution solution;
    Solution::VecNodeValues ret = solution.levelOrderBottom(pRoot);
    if (ret != expected)
        std::printf("Test failed.\n");
}


int main()
{
    doTest({ 3, 9, 20, 0, 0, 15, 7 },
           {
               { 15, 7 },
               { 9, 20 },
               { 3 },
           });

    doTest({ 1, 2, 3, 4, 5, 6, 7 },
           {
               { 4, 5, 6, 7 },
               { 2, 3 },
               { 1 },
           });

    return 0;
}

#endif
