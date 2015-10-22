#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>


using namespace std;


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
    struct DFSContext
    {
        bool        bHasVisitedLeft;
        bool        bHasVisitedRight;
        TreeNode    *pCurNode;

        DFSContext() : bHasVisitedLeft(false),
                       bHasVisitedRight(false),
                       pCurNode(nullptr)
        {}
    };


public:
    int minDepth(TreeNode *root)
    {
        if (!root)
            return 0;

        vector<DFSContext> vecCtx;
        DFSContext tmpCtx;

        tmpCtx.bHasVisitedLeft = tmpCtx.bHasVisitedRight = false;
        tmpCtx.pCurNode = root;
        vecCtx.push_back(tmpCtx);

        int ret = INT_MAX;
        int curDepth = 1;

        while (!vecCtx.empty())
        {
            DFSContext &curCtx = vecCtx.back();
            TreeNode *pCurNode = curCtx.pCurNode;
            TreeNode *pLeftNode = pCurNode->left;
            TreeNode *pRightNode = pCurNode->right;

            // 如果左右结点为空，立刻标记为已遍历
            curCtx.bHasVisitedLeft |= !pLeftNode;
            curCtx.bHasVisitedRight |= !pRightNode;

            if (!pLeftNode && !pRightNode)
            {
                // 叶子到根的深度
                ret = min(ret, curDepth);
            }
            else
            {
                // 越向下走深度只会越大
                if (curDepth >= ret)
                    curCtx.bHasVisitedLeft = curCtx.bHasVisitedRight = true;
            }

            if (curCtx.bHasVisitedLeft && curCtx.bHasVisitedRight)
            {
                // 左右子树都遍历完才退栈
                --curDepth;
                vecCtx.pop_back();

                if (vecCtx.empty())
                    continue;

                DFSContext &parentCtx = vecCtx.back();
                TreeNode *pParentNode = parentCtx.pCurNode;
                if (pCurNode == pParentNode->left)
                    parentCtx.bHasVisitedLeft = true;
                else if (pCurNode == pParentNode->right)
                    parentCtx.bHasVisitedRight = true;
            }
            else
            {
                // 继续向下遍历
                tmpCtx.bHasVisitedLeft = tmpCtx.bHasVisitedRight = false;
                tmpCtx.pCurNode = !curCtx.bHasVisitedLeft ? pLeftNode : pRightNode;
                vecCtx.push_back(tmpCtx);

                ++curDepth;
            }
        }

        return ret;
    }
};




#ifdef LEETCODE_DEBUG

static int doCalcMinDepth(TreeNode *pCurNode, int curDepth)
{
    if (!pCurNode)
        return 0;

    TreeNode *pLeftNode = pCurNode->left;
    TreeNode *pRightNode = pCurNode->right;
    if (!pLeftNode && !pRightNode)
        return curDepth;

    int leftMinDepth = pLeftNode ? doCalcMinDepth(pLeftNode, curDepth + 1) : INT_MAX;
    int rightMinDepth = pRightNode ? doCalcMinDepth(pRightNode, curDepth + 1) : INT_MAX;
    return min(leftMinDepth, rightMinDepth);
}


static void disposeTestCase(vector<TreeNode*> &vecTreeNodes)
{
    for (int i = 0, n = vecTreeNodes.size(); i < n; ++i)
        delete vecTreeNodes[i];

    vecTreeNodes.clear();
}



static TreeNode* createTestCase(vector<TreeNode*> &vecInTreeNodes, int *pMinDepth)
{
    disposeTestCase(vecInTreeNodes);

    TreeNode *pHeadNode = new TreeNode(rand() % 30);
    vecInTreeNodes.push_back(pHeadNode);

    int nodeCount = rand() % 300;
    for (int i = 0; i < nodeCount; ++i)
    {
        TreeNode *pNode = new TreeNode(rand() % 30);
        int inTreeNodeCount = vecInTreeNodes.size();
        while (true)
        {
            // 从树中随机选一个父结点
            int randIdx = rand() % inTreeNodeCount;
            TreeNode *pParent = vecInTreeNodes[randIdx];
            if (!pParent->left)
            {
                pParent->left = pNode;
                break;
            }
            else if (!pParent->right)
            {
                pParent->right = pNode;
                break;
            }
        }

        vecInTreeNodes.push_back(pNode);
    }


    *pMinDepth = doCalcMinDepth(pHeadNode, 1);
    return pHeadNode;
}


int main()
{
    srand(time(0));

    vector<TreeNode*> vecTreeNodes;
    Solution solution;

    for (int i = 0; i < 10000; ++i)
    {
        int correct = 0;
        TreeNode *pHead = createTestCase(vecTreeNodes, &correct);
        int output = solution.minDepth(pHead);

        disposeTestCase(vecTreeNodes);

        if (output != correct)
        {
            cout << "Bang!" << endl;
            break;
        }
    }

    return 0;
}

#endif
