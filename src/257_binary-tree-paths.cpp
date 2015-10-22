#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <string>
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



static const char   *kStringFormatTrailingPath  = "->%d";
static const char   *kStringFormatStartNode     = "%d";

static int addPathString(char *pBuf, TreeNode *pNode, std::string *pStr)
{
    if (!pBuf || !pNode || !pStr)
        return 0;

    const char *pFormat = pStr->empty()
                          ? kStringFormatStartNode
                          : kStringFormatTrailingPath;

    int len = std::sprintf(pBuf, pFormat, pNode->val);
    pStr->append(pBuf, len);
    return len;
}


class Solution
{
private:
    struct TreeIterateContext
    {
        bool        bHasVisitLeft;
        bool        bHasVisitRight;
        int         nPathStringLen;
        TreeNode    *pNode;

        TreeIterateContext() : bHasVisitLeft(false),
                               bHasVisitRight(false),
                               nPathStringLen(0),
                               pNode(nullptr)
        {}
    };


public:
    std::vector<std::string> binaryTreePaths(TreeNode *pRoot)
    {
        std::string strTmp;
        std::vector<std::string> vecPaths;
        std::vector<TreeIterateContext> vecContexts;
        char buf[1024];

        if (pRoot)
        {
            vecContexts.resize(1);
            vecContexts.back().pNode = pRoot;
        }

        while (!vecContexts.empty())
        {
            TreeIterateContext &ctx = vecContexts.back();

            // 第一次遍历此结点
            if (!ctx.bHasVisitLeft && !ctx.bHasVisitRight)
                ctx.nPathStringLen = addPathString(buf, ctx.pNode, &strTmp);

            // 遍历左子树
            if (!ctx.bHasVisitLeft)
            {
                ctx.bHasVisitLeft = true;
                if (ctx.pNode->left)
                {
                    vecContexts.resize(vecContexts.size() + 1);
                    vecContexts.back().pNode = ctx.pNode->left;
                    continue;
                }
            }

            // 遍历右子树
            if (!ctx.bHasVisitRight)
            {
                ctx.bHasVisitRight = true;
                if (ctx.pNode->right)
                {
                    vecContexts.resize(vecContexts.size() + 1);
                    vecContexts.back().pNode = ctx.pNode->right;
                    continue;
                }
            }


            // 遍历到叶子就可以得出一条路径
            if (!ctx.pNode->left && !ctx.pNode->right)
                vecPaths.push_back(strTmp);

            vecContexts.pop_back();
            strTmp.erase(strTmp.end() - ctx.nPathStringLen, strTmp.end());
        }

        return vecPaths;
    }
};


#ifdef LEETCODE_DEBUG


static TreeNode* buildTreeFromSerializedArray(std::vector<TreeNode> *pVecNode,
                                              std::vector<int> &vecNodeValues)
{
    if (vecNodeValues.empty())
        return nullptr;

    pVecNode->resize(vecNodeValues.size());
    for (int i = 0, n = vecNodeValues.size(); i < n; ++i)
    {
        TreeNode *pNode = &pVecNode->at(i);
        pNode->left = nullptr;
        pNode->right = nullptr;
        pNode->val = vecNodeValues[i];

        TreeNode *pParent = (i > 0) ? &pVecNode->at((i - 1) / 2) : nullptr;
        if (pParent && pNode->val > 0)
        {
            if (i & 0x01)
                pParent->left = pNode;
            else
                pParent->right = pNode;
        }
    }
    return &pVecNode->at(0);
}


static void doTest(std::vector<int> vecNodeVaules,
                   std::vector<std::string> vecCompare)
{
    std::vector<TreeNode> vecNodes;
    TreeNode *pNode = buildTreeFromSerializedArray(&vecNodes, vecNodeVaules);

    Solution solution;
    std::vector<std::string> vecRet = solution.binaryTreePaths(pNode);
    if (vecRet != vecCompare)
        std::printf("Test failed.\n");
}


int main()
{
    doTest({}, {});

    doTest({ 1, 2, 3, 0, 5 },
           {
               "1->2->5",
               "1->3",
           });

    doTest({ 1, 2, 3, 4, 5 },
           {
               "1->2->4",
               "1->2->5",
               "1->3",
           });

    return 0;
}

#endif
