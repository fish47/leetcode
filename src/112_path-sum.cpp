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
    bool hasPathSum(TreeNode *root, int sum)
    {
        // 空树累计不为零囧？
        if (!root)
            return false;

        vector<DFSContext> vecCtx;
        DFSContext tmpCtx;

        tmpCtx.bHasVisitedLeft = tmpCtx.bHasVisitedRight = false;
        tmpCtx.pCurNode = root;
        vecCtx.push_back(tmpCtx);

        int curSum = 0;
        while (!vecCtx.empty())
        {
            DFSContext &curCtx = vecCtx.back();
            TreeNode *pCurNode = curCtx.pCurNode;
            TreeNode *pLeftNode = pCurNode->left;
            TreeNode *pRightNode = pCurNode->right;

            curSum += pCurNode->val;

            // 如果左右结点为空，立刻标记为已遍历
            curCtx.bHasVisitedLeft |= !pLeftNode;
            curCtx.bHasVisitedRight |= !pRightNode;

            if (!pLeftNode && !pRightNode && curSum == sum)
                return true;

            if (curCtx.bHasVisitedLeft && curCtx.bHasVisitedRight)
            {
                // 左右子树都遍历完才退栈
                curSum -= pCurNode->val;
                vecCtx.pop_back();

                if (vecCtx.empty())
                    continue;

                DFSContext &parentCtx = vecCtx.back();
                TreeNode *pParentNode = parentCtx.pCurNode;
                if (pCurNode == pParentNode->left)
                    parentCtx.bHasVisitedLeft = true;
                else if (pCurNode == pParentNode->right)
                    parentCtx.bHasVisitedRight = true;

                // 因为每次遍历结点都会加一次
                curSum -= pParentNode->val;
            }
            else
            {
                // 继续向下遍历
                tmpCtx.bHasVisitedLeft = tmpCtx.bHasVisitedRight = false;
                tmpCtx.pCurNode = !curCtx.bHasVisitedLeft ? pLeftNode : pRightNode;
                vecCtx.push_back(tmpCtx);
            }
        }

        return false;
    }
};




#ifdef LEETCODE_DEBUG

static void doSearchPathSums(TreeNode *pCurNode, int curSum, set<int> &pathSums)
{
    curSum += pCurNode->val;

    TreeNode *pLeftNode = pCurNode->left;
    TreeNode *pRightNode = pCurNode->right;

    if (pLeftNode)
        doSearchPathSums(pLeftNode, curSum, pathSums);

    if (pRightNode)
        doSearchPathSums(pRightNode, curSum, pathSums);

    if (!pLeftNode && !pRightNode)
        pathSums.insert(curSum);
}


static void disposeTestCase(vector<TreeNode*> &vecTreeNodes)
{
    for (int i = 0, n = vecTreeNodes.size(); i < n; ++i)
        delete vecTreeNodes[i];

    vecTreeNodes.clear();
}



static TreeNode *createTestCase(set<int> &pathSums,
                                vector<TreeNode*> &vecInTreeNodes)
{
    pathSums.clear();
    disposeTestCase(vecInTreeNodes);

    TreeNode *pHeadNode = new TreeNode(rand() % 30);
    vecInTreeNodes.push_back(pHeadNode);

    int nodeCount = rand() % 30;
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


    doSearchPathSums(pHeadNode, 0, pathSums);

    return pHeadNode;
}


int main()
{
    srand(time(0));

    set<int> pathSums;
    vector<TreeNode*> vecTreeNodes;
    Solution solution;

    for (int i = 0; i < 10000; ++i)
    {
        bool bPassed = true;
        TreeNode *pHead = createTestCase(pathSums, vecTreeNodes);

        // 检查应该返回为 true 的值
        set<int>::iterator it = pathSums.begin();
        set<int>::iterator endIt = pathSums.end();
        while (it != endIt)
        {
            if (!solution.hasPathSum(pHead, *it))
            {
                bPassed = false;
                break;
            }

            ++it;
        }


        // 检查应该返回为 false 的值
        for (int j = 0, n = pathSums.size(); j < n; ++j)
        {
            int checkVal = 0;
            while (true)
            {
                checkVal = rand() % 100;
                if (pathSums.find(checkVal) == endIt)
                    break;
            }

            if (solution.hasPathSum(pHead, checkVal))
            {
                bPassed = false;
                break;
            }
        }


        disposeTestCase(vecTreeNodes);

        if (!bPassed)
        {
            cout << "Bang!" << endl;
            break;
        }
    }

    return 0;
}

#endif
