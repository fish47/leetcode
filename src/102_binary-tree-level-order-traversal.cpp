#include <cstdio>
#include <cstdlib>
#include <climits>
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

public:
    VecNodeValues levelOrder(TreeNode *pRoot)
    {
        VecNodeValues ret;
        if (!pRoot)
            return ret;


        NodeValues tmpNodeValues;
        std::list<TreeNode*> listNodes;

        listNodes.push_back(pRoot);
        auto itLastNodeOfCurLevel = --listNodes.cend();

        while (!listNodes.empty())
        {
            TreeNode *pNode = listNodes.front();
            tmpNodeValues.push_back(pNode->val);

            if (pNode->left)
                listNodes.push_back(pNode->left);

            if (pNode->right)
                listNodes.push_back(pNode->right);


            if (pNode == *itLastNodeOfCurLevel)
            {
                ret.push_back(tmpNodeValues);
                tmpNodeValues.clear();
                itLastNodeOfCurLevel = --listNodes.cend();
            }

            listNodes.pop_front();
        }

        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static void doTest(std::vector<int> vecTreeData,
                   Solution::VecNodeValues expected)
{
    TreeNode *pRoot = nullptr;
    std::vector<TreeNode> vecNodes(vecTreeData.size());
    for (int i = 0, n = vecTreeData.size(); i < n; ++i)
    {
        TreeNode &node = vecNodes[i];
        TreeNode &parent = vecNodes[(i - 1) / 2];

        int val = vecTreeData[i];
        node.left = nullptr;
        node.right = nullptr;
        node.val = val;

        if (&node == &parent)
        {
            pRoot = &node;
            continue;
        }

        TreeNode *pNode = (val <= 0) ? nullptr : &node;
        TreeNode **ppChild = (i & 1) ? &parent.left : &parent.right;
        *ppChild = pNode;
    }


    Solution solution;
    Solution::VecNodeValues ret = solution.levelOrder(pRoot);
    if (ret != expected)
        std::printf("Test failed.\n");
}


int main()
{
    doTest({}, {});

    doTest({ 3, 9, 20, 0, 0, 15, 7 },
           {
               { 3 },
               { 9, 20 },
               { 15, 7 },
           });

    doTest({ 1, 2, 3, 4 },
           {
               { 1 },
               { 2, 3 },
               { 4 },
           });

    doTest({ 1, 0, 3, 0, 0, 6 },
           {
               { 1 },
               { 3 },
               { 6 },
           });



    return 0;
}

#endif
