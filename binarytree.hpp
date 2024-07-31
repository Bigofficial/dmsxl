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
    traversal1(node->left, ret);
    traversal1(node->right, ret);
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
    vector<int> ret;
    stack<TreeNode *> sta;
    TreeNode *cur = root;
    while (cur != nullptr || !sta.empty())
    {
        if (cur != NULL)
        {
            sta.push(cur);
            cur = cur->left; // 左
        }
        else
        {
            // 取出，放入栈顶的右孩子
            TreeNode *temp = sta.top(); // 中
            sta.pop();
            ret.push_back(temp->val);
            cur = temp->right; // 右
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

int getHeight(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    int left = getHeight(root->left);
    if (left == -1)
        return -1;
    int right = getHeight(root->right);
    if (right == -1)
        return -1;
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
// 110 平衡二叉树
bool isBalanced(TreeNode *root)
{
    return getHeight(root) == -1 ? false : true;
}
void traversalBTP(TreeNode *node, vector<int> &path, vector<string> &result)
{
    path.push_back(node->val);
    if (node->left == nullptr && node->right == nullptr)
    {
        string sPath;
        for (int i = 0; i < path.size() - 1; i++)
        {
            sPath += to_string(path[i]);
            sPath += "->";
        }
        sPath += to_string(path[path.size() - 1]);
        result.push_back(sPath);
        return;
    }
    if (node->left)
    {
        traversalBTP(node->left, path, result);
        path.pop_back();
    }
    if (node->right)
    {
        traversalBTP(node->right, path, result);
        path.pop_back();
    }
}
// 257 二叉树的所有路径
vector<string> binaryTreePaths(TreeNode *root)
{
    vector<int> path;
    vector<string> result;
    if (root == nullptr)
        return result;
    traversalBTP(root, path, result);
    return result;
}

// 404 左叶子之和
int sumOfLeftLeaves1(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 0;

    // 求出左孩子的左叶子之和
    int leftValue = sumOfLeftLeaves(root->left);
    // 假如左孩子没有孩子
    if (root->left && !root->left->left && !root->left->right)
        leftValue = root->left->val;
    int rightValue = sumOfLeftLeaves(root->right);
    int sum = leftValue + rightValue;
    return sum;
}

int sumOfLeftLeaves2(TreeNode *root)
{
    stack<TreeNode *> sta;
    if (root == nullptr)
        return 0;
    sta.push(root);
    int result = 0;
    while (!sta.empty())
    {
        TreeNode *temp = sta.top();
        sta.pop();
        if (temp->left && temp->left->left == nullptr && temp->left->right == nullptr)
            result += temp->left->val;

        if (temp->right)
            sta.push(temp->right);
        if (temp->left)
            sta.push(temp->left);
    }
    return result;
}

// 513 找树左下角的值
int findBottomLeftValue1(TreeNode *root)
{
    queue<TreeNode *> que;
    int ret;
    que.push(root);
    while (!que.empty())
    {
        int size = que.size();
        ret = que.front()->val;
        for (int i = 0; i < size; i++)
        {
            TreeNode *temp = que.front();
            que.pop();
            if (temp->left)
                que.push(temp->left);
            if (temp->right)
                que.push(temp->right);
        }
    }
    return ret;
}

int maxDepthFBLV = INT_MIN;
int retFBLV = 0;
void traversalFBLV(TreeNode *node, int depth)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        if (depth > maxDepthFBLV)
        {
            maxDepthFBLV = depth;
            retFBLV = node->val;
        }
        return;
    }
    if (node->left)
    {
        traversalFBLV(node->left, depth + 1);
    }
    if (node->right)
    {
        traversalFBLV(node->right, depth + 1);
    }
    return;
}
int findBottomLeftValue2(TreeNode *root)
{
    if (root != nullptr)
        traversalFBLV(root, 0);
    return retFBLV;
}

bool pathTraversal(TreeNode *node, int curVal, int targetSum)
{
    if (!node->left && !node->right && curVal + node->val == targetSum)
    {
        return true;
    }
    bool left = false;
    if (node->left)
        left = pathTraversal(node->left, curVal + node->val, targetSum);
    bool right = false;
    if (node->right)
        right = pathTraversal(node->right, curVal + node->val, targetSum);
    return left || right;
}
// 112 路径总和
bool hasPathSum(TreeNode *root, int targetSum)
{
    if (root == nullptr)
        return false;
    return pathTraversal(root, 0, targetSum);
}

// 106 从中序与后序遍历序列构造二叉树
TreeNode *buildBuild(vector<int> &inorder, vector<int> &postorder, int inStart,
                     int inEnd, int postStart, int postEnd)
{
    // 排除没有左子树,或者没有右子树的情况
    if (inStart > inEnd || postStart > postEnd)
    {
        return nullptr;
    }

    TreeNode *root = new TreeNode(postorder[postEnd]);

    // 在中序中找到根节点位置 i也就相当于是左子树长度
    int i = inStart;
    while (inorder[i] != root->val)
    {
        i++;
    }

    // 构造左子树

    root->left = buildBuild(inorder, postorder, inStart, i - 1, postStart, postStart + i - inStart - 1);

    // 构造右子树

    root->right = buildBuild(inorder, postorder, i + 1, inEnd, postStart + i - inStart, postEnd - 1);
    return root;
}
TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
{
    // 找到后序遍历最后一个,确认其在中序位置,拆分中序和后序为左右
    // 对左右递归处理
    return buildBuild(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
}

// 105 从前序与中序遍历序列构造二叉树
TreeNode *preInBuild(vector<int> &preorder, vector<int> &inorder, int preStart, int preEnd, int inStart, int inEnd)
{
    // 去除异常情况
    if (preStart > preEnd || inStart > inEnd)
    {
        return nullptr;
    }
    TreeNode *root = new TreeNode(preorder[preStart]);
    // 在中序中找到根节点位置 i也就相当于是左子树长度
    int i = inStart;
    while (inorder[i] != root->val)
    {
        i++;
    }
    // 0+1, 0+1-0-1
    root->left = preInBuild(preorder, inorder, preStart + 1, preStart + i - inStart, inStart, i - 1);
    // 0+1-0
    root->right = preInBuild(preorder, inorder, preStart + i - inStart + 1, preEnd, i + 1, inEnd);
    return root;
}

TreeNode *buildTree2(vector<int> &preorder, vector<int> &inorder)
{
    return preInBuild(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
}

// 654 最大二叉树
int findMaxPos(vector<int> &nums, int start, int end)
{
    int max = INT_MIN;
    int maxPos = -1;
    for (int i = start; i <= end; i++)
    {
        if (nums[i] > max)
        {
            max = nums[i];
            maxPos = i;
        }
    }
    return maxPos;
}
// 1 2
TreeNode *rangeMaxBinaryTree(vector<int> &nums, int start, int end)
{
    // 无孩子 start == end  这个判断有没有都可以
    if (start == end)
        return new TreeNode(nums[start]);
    // 有单一孩子 左 右(end, end)
    if (start > end)
    {
        return nullptr;
    }
    int maxPos = findMaxPos(nums, start, end);
    TreeNode *root = new TreeNode(nums[maxPos]);
    // max = 1
    // 0, 0
    root->left = rangeMaxBinaryTree(nums, start, maxPos - 1);
    // 2, 1
    root->right = rangeMaxBinaryTree(nums, maxPos + 1, end);
    return root;
}
TreeNode *constructMaximumBinaryTree(vector<int> &nums)
{
    return rangeMaxBinaryTree(nums, 0, nums.size() - 1);
}

TreeNode *mergeNode(TreeNode *node1, TreeNode *node2)
{
    // 合并根节点
    if (!node1)
        return node2;
    if (!node2)
        return node1;
    node1->val += node2->val;
    node1->left = mergeNode(node1->left, node2->left);
    node1->right = mergeNode(node1->right, node2->right);
    return node1;
}
// 617 合并二叉树
TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
{
    return mergeNode(root1, root2);
}

// 700 二叉搜索树中的搜索
TreeNode *searchBST(TreeNode *root, int val)
{
    if (!root)
        return nullptr;
    if (root->val == val)
        return root;
    else if (root->val < val)
        return searchBST(root->right, val);
    else
        return searchBST(root->left, val);
}

// 98 验证二叉搜索树
bool isValid(TreeNode *root, long long  l, long long r)
{
    if (root == nullptr)
        return true;
    if(root->val <= l || root->val >= r) return false;
    // 判断左边
    bool left = isValid(root->left, l, root->val);
    // 判断右边
    bool right = isValid(root->right, root->val, r);
    return left && right;
}
//98 验证二叉搜索树
bool isValidBST(TreeNode *root)
{
    return isValid(root, LONG_LONG_MIN, LONG_LONG_MAX);
}

vector<int> vecBST;
void traversalBST(TreeNode *root)
{
    if (root == nullptr)
        return;
    traversalBST(root->left);
    vecBST.push_back(root->val);
    traversal(root->right);
}

bool isValidBST2(TreeNode *root)
{
    vec.clear();
    traversalBST(root);
    for (int i = 1; i < vecBST.size(); i++)
    {
        if (vec[i] <= vec[i - 1])
            return false;
    }
    return true;
}

vector<int> vecGMD;
void traversalGMD(TreeNode *root)
{
    if (root == nullptr)
        return;
    traversalGMD(root->left);
    vecGMD.push_back(root->val);
    traversalGMD(root->right);
}
// 530 二叉搜索树的最小绝对差
int getMinimumDifference(TreeNode *root)
{
    vecGMD.clear();
    traversalGMD(root);
    int minDif = INT_MAX;
    for (int i = 1; i < vecGMD.size(); i++)
    {
        if (vecGMD[i] - vecGMD[i - 1] < minDif)
            minDif = vecGMD[i] - vecGMD[i - 1];
    }
    return minDif;
}

int getMinimumDifference2(TreeNode *root)
{
    stack<TreeNode *> sta;
    TreeNode *cur = root;
    TreeNode *pre = nullptr;
    int result = INT_MAX;
    while (cur != nullptr || !sta.empty())
    {
        if (cur != nullptr)
        {
            sta.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = sta.top();
            sta.pop();
            if (pre != nullptr)
            {
                result = min(result, cur->val - pre->val);
            }
            pre = cur;
            cur = cur->right;
        }
    }
    return result;
}

// 501 二叉搜索树中的众数
int maxCountFM = 0;
int count = 0;
TreeNode *pre = nullptr;
vector<int> resultFM;
void traversalFM(TreeNode *cur)
{
    if (!cur)
        return;
    traversalFM(cur->left);

    if (!pre)
    {
        count = 1;
    }
    else if (pre->val == cur->val)
    {
        count++;
    }
    else
    {
        count = 1;
    }
    pre = cur;

    if (count == maxCountFM)
        resultFM.push_back(cur->val);

    if (count > maxCountFM)
    {
        maxCountFM = count;
        resultFM.clear();
        resultFM.push_back(cur->val);
    }
    traversalFM(cur->right);
    return;
}

void fmtraversal(TreeNode *cur, unordered_map<int, int> &mp)
{
    if (cur == nullptr)
        return;
    mp[cur->val]++;
    fmtraversal(cur->left, mp);
    fmtraversal(cur->right, mp);
}
bool static cmp(pair<int, int> &a, pair<int, int> &b)
{
    return a.second > b.second;
}

vector<int> traversalFM2(TreeNode *root)
{
    int count = 0;
    int maxCount = 0;
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode *> sta;
    TreeNode *cur = root;
    TreeNode *pre = nullptr;
    while (cur != nullptr || !sta.empty())
    {
        if (cur != nullptr)
        {
            sta.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = sta.top();
            sta.pop();
            if (!pre)
                count = 1;
            else if (pre->val == cur->val)
            {
                count++;
            }
            else
            {
                count = 1;
            }
            pre = cur;
            if (count == maxCount)
            {
                result.push_back(cur->val);
            }
            else if (count > maxCount)
            {
                maxCount = count;
                result.clear();
                result.push_back(cur->val);
            }
            cur = cur->right;
        }
    }
    return result;
}

vector<int> findMode(TreeNode *root)
{
    vector<int> result;
    if (root == nullptr)
        return result;
    unordered_map<int, int> mp;
    fmtraversal(root, mp);
    vector<pair<int, int>> vp(mp.begin(), mp.end());
    sort(vp.begin(), vp.end(), cmp); // 从大到小
    result.push_back(vp[0].first);
    for (int i = 1; i < vp.size(); i++)
    {
        if (vp[i].second == vp[0].second)
            result.push_back(vp[i].first);
        else
            break;
    }
    return result;
    // traversalFM(root);
    // return resultFM;
}

// 236 二叉树的最近公共祖先
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == nullptr || root == p || root == q)
        return root;
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (left && right)
        return root;
    else if (!left && right)
        return right;
    else if (left && !right)
        return left;
    else
        return nullptr;
}

// 235 二叉搜索树的最近公共祖先
TreeNode *lowestCommonAncestor2(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == nullptr || root == p || root == q)
        return root;
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (left && right)
        return root;
    else if (!left && right)
        return right;
    else if (left && !right)
        return left;
    else
        return nullptr;
}
TreeNode *traversalLCA(TreeNode *cur, TreeNode *p, TreeNode *q)
{
    if (cur == nullptr)
        return nullptr;
    // 假如一直满足那么就会到nullptr
    if (cur->val > p->val && cur->val > q->val)
    {
        TreeNode *left = traversalLCA(cur->left, p, q);
        if (left)
            return left;
    }

    if (cur->val < p->val && cur->val < q->val)
    {
        TreeNode *right = traversalLCA(cur->right, p, q);
        if (right)
            return right;
    }
    return cur;
}
TreeNode *lowestCommonAncestor3(TreeNode *root, TreeNode *p, TreeNode *q)
{
    return traversalLCA(root, p, q);
}

// 701 二叉搜索树中的插入操作
TreeNode *insertIntoBST(TreeNode *root, int val)
{
    if (root == nullptr)
    {
        TreeNode *node = new TreeNode(val);
        return node;
    }
    // 节点值更大,那么就插入到左孩子
    if (root->val > val)
        root->left = insertIntoBST(root->left, val);
    // 节点更小,插入到右孩子
    if (root->val < val)
        root->right = insertIntoBST(root->right, val);
    return root;
}

// 450 删除二叉搜索树的节点
TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == nullptr)
        return root;
    if (root->val == key)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr)
        {
            TreeNode *ret = root->right;
            delete root;
            return ret;
        }
        else if (root->right == nullptr)
        {
            TreeNode *ret = root->left;
            delete root;
            return ret;
        }
        else
        {
            TreeNode *cur = root->right;
            while (cur->left != nullptr)
            {
                cur = cur->left;
            }
            cur->left = root->left;
            TreeNode *temp = root;
            root = root->right;
            delete temp;
            return root;
        }
    }
    if (root->val > key)
        root->left = deleteNode(root->left, key);
    if (root->val < key)
        root->right = deleteNode(root->right, key);
    return root;
}

// 699 修建二叉搜索树
TreeNode *trimBST(TreeNode *root, int low, int high)
{
    if (root == nullptr)
        return root;
    if (root->val > high)
    {
        TreeNode *left = trimBST(root->left, low, high);
        return left;
    }
    if (root->val < low)
    {
        TreeNode *right = trimBST(root->right, low, high);
        return right;
    }
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}

TreeNode *traversalSTBST(vector<int> &nums, int left, int right)
{
    if (left > right)
        return nullptr;
    int mid = left + ((right - left) / 2);
    TreeNode *root = new TreeNode(nums[mid]);
    root->left = traversalSTBST(nums, left, mid - 1);
    root->right = traversalSTBST(nums, mid + 1, right);
    return root;
}
// 108 将有序数组转换成二叉搜索树
TreeNode *sortedArrayToBST(vector<int> &nums)
{
    return traversalSTBST(nums, 0, nums.size() - 1);
}

// 538 把二叉搜索树转换为累加树
int preCBST = 0;
void traversalCBST(TreeNode* cur){
    if(cur == nullptr) return;
    traversalCBST(cur->right);
    cur->val = cur->val + preCBST;
    preCBST = cur->val;
    traversalCBST(cur->left);
}
TreeNode *convertBST(TreeNode *root)
{
    traversalCBST(root);
    return root;
}