#include <iostream>
#include <vector>
#include <cstdlib>
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


class BSTIterator
{
private:
    std::vector<TreeNode*>      m_vecNodes;

private:
    void pushLeftChildren(TreeNode *pChild)
    {
        while (pChild)
        {
            m_vecNodes.push_back(pChild);
            pChild = pChild->left;
        }
    }


public:
    BSTIterator(TreeNode *pRoot)
    {
        pushLeftChildren(pRoot);
    }

    bool hasNext()
    {
        return !m_vecNodes.empty();
    }

    int next()
    {
        if (m_vecNodes.empty())
            return 0;

        auto pNode = m_vecNodes.back();
        auto ret = pNode->val;
        m_vecNodes.pop_back();
        pushLeftChildren(pNode->right);
        return ret;
    }
};



#ifdef LEETCODE_DEBUG

static TreeNode* createRandomBinaryTree(std::vector<TreeNode> *pNodes, int count)
{
    if (!pNodes || count <= 0)
        return nullptr;


    auto &nodes = *pNodes;
    nodes.resize(count);
    for (auto i = 0; i < count; ++i)
    {
        auto &node = nodes[i];
        node.val = i;
        node.left = nullptr;
        node.right = nullptr;

        if (i == 0)
            continue;

        while (true)
        {
            auto &parent = nodes[std::rand() % i];
            auto &branch = (std::rand() & 1) ? parent.left : parent.right;
            if (!branch)
            {
                branch = &node;
                break;
            }
        }
    }

    return &nodes.front();
}


static void calcInorderTraverseResult(TreeNode *pRoot, std::vector<int> *pResult)
{
    if (!pRoot || !pResult)
        return;

    calcInorderTraverseResult(pRoot->left, pResult);
    pResult->push_back(pRoot->val);
    calcInorderTraverseResult(pRoot->right, pResult);
}


int main()
{
    std::vector<int> result1;
    std::vector<int> result2;
    std::vector<TreeNode> nodes;
    std::srand(std::time(nullptr));
    for (auto i = 0; i < 10000; ++i)
    {
        auto count = std::rand() % 100;
        auto pRoot = createRandomBinaryTree(&nodes, count);

        BSTIterator it(pRoot);
        result1.clear();
        while (it.hasNext())
            result1.push_back(it.next());

        result2.clear();
        calcInorderTraverseResult(pRoot, &result2);

        if (result1 != result2)
        {
            std::cout << "Test failed." << std::endl;
            break;
        }
    }
    return 0;
}

#endif
