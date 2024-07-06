#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void traversal1(TreeNode *node, vector<int> &ret)
{
    if (node == nullptr)
        return;
    ret.push_back(node->val);
    traversal(node->left, ret);
    traversal(node->right, ret);
}
vector<int> preorderTraversal(TreeNode *root)
{
    vector<int> result;
    traversal(root, result);
    return result;
}

void traversal2(TreeNode *node, vector<int> &ret)
{
    if (node == nullptr)
        return;
    traversal2(node->left, ret);
    traversal2(node->right, ret);
    ret.push_back(node->val);
}

vector<int> postorderTraversal(TreeNode *root)
{
    vector<int> result;
    traversal2(root, result);
    return result;
}

void traversal3(TreeNode *node, vector<int> &ret)
{
    if (node == nullptr)
        return;
    traversal3(node->left, ret);
    ret.push_back(node->val);
    traversal3(node->right, ret);
}
vector<int> inorderTraversal(TreeNode *root)
{
    vector<int> result;
    traversal3(root, result);
    return result;
}

vector<int> iterPreorderTraversal(TreeNode *root)
{
    // 中左右
    // 假我们是出站放入集合
    // 出站的时候加入其左右孩子，这样后入的孩子会晚出来，是中左右 所以先放右边
    // 也可以入站操作，那么就要两遍代码了
    vector<int> ret;
    stack<TreeNode *> sta;
    if (root == nullptr)
        return ret;
    sta.push(root);
    while (!sta.empty())
    {
        TreeNode *temp = sta.top();
        ret.push_back(temp->val);
        sta.pop();
        if (temp->right)
            sta.push(temp->right);
        if (temp->left)
            sta.push(temp->left);
    }
    return ret;
}

vector<int> iterInorderTraversal(TreeNode *root)
{
    // 5
    // 4 6
    // 12
    vector<int> ret;
    stack<TreeNode *> sta;
    TreeNode *cur = root;
    while (cur != nullptr || !sta.empty())
    {
        if (cur == NULL)
        {
            // 取出，放入栈顶的右孩子
            TreeNode *temp = sta.top(); // 中
            sta.pop();
            ret.push_back(temp->val);
            cur = temp->right; // 右
        }
        else
        {
            sta.push(cur);
            cur = cur->left; // 左
        }
    }
    return ret;
}

// 我们都是在出站处理的，所以是出站顺序 决定我们遍历顺序，而不是访问顺序
vector<int> iterPostorderTraversal(TreeNode *root)
{
    vector<int> ret;
    stack<TreeNode *> sta;
    if (root == nullptr)
        return ret;
    sta.push(root);
    while (!sta.empty())
    {
        TreeNode *temp = sta.top();
        sta.pop();
        ret.push_back(temp->val);
        if (temp->left)
            sta.push(temp->left);
        if (temp->right)
            sta.push(temp->right);
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

// 统一的迭代遍历
vector<int> uniIterPreorderTraversal(TreeNode *root)
{
    vector<int> ret;
    stack<TreeNode *> sta;
    if (root != nullptr)
        sta.push(root);
    while (!sta.empty())
    {
        TreeNode *temp = sta.top();
        if (temp != nullptr)
        {
            sta.pop();
            if (temp->right)
                sta.push(temp->right);
            if (temp->left)
                sta.push(temp->left);
            sta.push(temp);
            sta.push(nullptr);
        }
        else
        {
            sta.pop();
            TreeNode *temp = sta.top();
            ret.push_back(temp->val);
            sta.pop();
        }
    }
    return ret;
}

// 统一的迭代遍历
vector<int> uniIterInorderTraversal(TreeNode *root)
{
    vector<int> ret;
    stack<TreeNode *> sta;
    if (root != nullptr)
        sta.push(root);
    while (!sta.empty())
    {
        TreeNode *temp = sta.top();
        if (temp != nullptr)
        {
            sta.pop();
            if (temp->right)
                sta.push(temp->right);
            sta.push(temp);
            sta.push(nullptr);
            if (temp->left)
                sta.push(temp->left);
        }
        else
        {
            sta.pop();
            TreeNode *temp = sta.top();
            ret.push_back(temp->val);
            sta.pop();
        }
    }
    return ret;
}

// 统一的迭代遍历
vector<int> uniIterPostorderTraversal(TreeNode *root)
{
    vector<int> ret;
    stack<TreeNode *> sta;
    if (root != nullptr)
        sta.push(root);
    while (!sta.empty())
    {
        TreeNode *temp = sta.top();
        if (temp != nullptr)
        {
            sta.pop();
            sta.push(temp);
            sta.push(nullptr);

            if (temp->right)
                sta.push(temp->right);
            if (temp->left)
                sta.push(temp->left);
        }
        else
        {
            sta.pop();
            TreeNode *temp = sta.top();
            ret.push_back(temp->val);
            sta.pop();
        }
    }
    return ret;
}

vector<vector<int>> levelOrder(TreeNode *root)
{
    queue<TreeNode *> que;
    vector<vector<int>> ret;
    if (root != nullptr)
        que.push(root);
    while (!que.empty())
    {
        int size = que.size();
        vector<int> vec;

        for (int i = 0; i < size; i++)
        {
            TreeNode *temp = que.front();
            que.pop();
            vec.push_back(temp->val);
            if (temp->left)
                que.push(temp->left);
            if (temp->right)
                que.push(temp->right);
        }
        ret.push_back(vec);
    }
    return ret;
}

// 226 翻转二叉树
TreeNode *invertTree(TreeNode *root)
{
    queue<TreeNode *> que;
    if (root == nullptr)
        return nullptr;
    que.push(root);
    while (!que.empty())
    {
        TreeNode *temp = que.front();
        que.pop();
        if (temp->left)
            que.push(temp->left);
        if (temp->right)
            que.push(temp->right);
        TreeNode *swp = temp->left;
        temp->left = temp->right;
        temp->right = swp;
    }
    return root;
}

bool compare_sym(TreeNode *left, TreeNode *right)
{
    if (left == nullptr && right != nullptr)
        return false;
    if (left != nullptr && right == nullptr)
        return false;
    if (left == nullptr && right == nullptr)
        return true;
    if (left->val != right->val)
        return false;
    bool outside = compare_sym(left->left, right->right);
    bool inside = compare_sym(left->right, right->left);
    return outside && inside;
}
// 101 对称二叉树
bool isSymmetric(TreeNode *root)
{
    if (root == nullptr)
        return true;
    return compare_sym(root->left, root->right);
}

// 104二叉树的最大深度
int maxDepth(TreeNode *root)
{
    queue<TreeNode *> que;
    int depth = 0;
    if (root != nullptr)
    {
        que.push(root);
    }
    while (!que.empty())
    {
        int levelSize = que.size();
        for (int i = 0; i < levelSize; i++)
        {
            TreeNode *temp = que.front();
            que.pop();
            if (temp->left)
                que.push(temp->left);
            if (temp->right)
                que.push(temp->right);
        }
        depth++;
    }
    return depth;
}

int getDepth(TreeNode *node)
{
    if (node == nullptr)
        return 0;
    int left = getDepth(node->left);
    int right = getDepth(node->right);
    return 1 + max(left, right);
}
int recursiveMaxDepth(TreeNode *root)
{
    return getDepth(root);
}

// 111 二叉树的最小深度
int minDepth1(TreeNode *root)
{
    queue<TreeNode *> que;
    int minDep = INT16_MAX;
    int depth = 0;
    if (root == nullptr)
        return 0;
    if (root != nullptr)
        que.push(root);
    while (!que.empty())
    {
        int levelSize = que.size();
        depth++;
        for (int i = 0; i < levelSize; i++)
        {
            TreeNode *temp = que.front();
            que.pop();
            if (temp->left == nullptr && temp->right == nullptr)
                minDep = min(minDep, depth);
            if (temp->left != nullptr)
                que.push(temp->left);
            if (temp->right != nullptr)
                que.push(temp->right);
        }
    }
    return minDep;
}

int getMinDep(TreeNode *node)
{
    if (node == nullptr)
        return 0;
    int left = getMinDep(node->left);
    int right = getMinDep(node->right);

    if (node->left == nullptr && node->right != nullptr)
        return 1 + right;
    if (node->right == nullptr && node->left != nullptr)
        return 1 + left;
    return 1 + min(left, right);
}
int minDepth(TreeNode *root)
{
    return getMinDep(root);
}

int countTraversal(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    int left = countTraversal(root->left);
    int right = countTraversal(root->right);
    return left + right + 1;
}
// 222 完全二叉树的节点个数
int countNodes(TreeNode *root)
{
    return countTraversal(root);
}


int getHeight(TreeNode* root){
    if(root == nullptr) return 0;
    int left = getHeight(root->left);
    if(left == -1) return -1;
    int right = getHeight(root->right);
    if(right == -1) return -1;
    return abs(left - right) > 1 ? -1 : 1 + max(left, right);
}

// bool recBalance(TreeNode* root){
//     if(root == nullptr) return true;
//     bool left =  recBalance(root->left);
//     bool right = recBalance(root->right);
//     int leftHeight = getHeight(root->left);
//     int rightHeight = getHeight(root->right);
//     if(!left || !right){
//         return false;
//     }
//     return abs(leftHeight - rightHeight) > 1 ? false : true;
// }
//110 平衡二叉树
bool isBalanced(TreeNode *root)
{
    return getHeight(root) == -1 ? false : true;
}