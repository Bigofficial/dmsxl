#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

vector<vector<int>> ret;
vector<int> path;

void backtracking(int n, int k, int startIndex)
{
    if (path.size() == k)
    {
        ret.push_back(path);
        return;
    }
    // 优化:
    // 当前已选path.size()
    // 所需 k - path.size()
    // 剩余可选 n - i
    // 即 n - i >= k- path.size()
    // i <= n - (k-path.size())
    // n = 4, k = 3 pathsize = 0
    // 4 - ( 3 - 0) = 1; //但是i可以取2
    // 这里再加1
    // i <= n - (k - path.size()) + 1
    for (int i = startIndex; i <= n; i++)
    {
        path.push_back(i);
        backtracking(n, k, i + 1);
        path.pop_back();
    }
}
// 77 组合 给定n和k,找出1-n所有可能得k个数集合
vector<vector<int>> combine(int n, int k)
{
    backtracking(n, k, 1);
    return ret;
}

int pathSum(vector<int> &vec)
{
    int sum = 0;
    for (int i : vec)
    {
        sum += i;
    }
    return sum;
}
int sumcs3 = 0;

void backtrackingcs3(int k, int n, int startIndex)
{
    if (path.size() == k)
    {
        if (sumcs3 == n)
            ret.push_back(path);
        return;
    }

    for (int i = startIndex; i <= 9; i++)
    {
        path.push_back(i);
        sumcs3 += i;
        backtrackingcs3(k, n, i + 1);
        sumcs3 -= i;
        path.pop_back();
    }
}

// 216 组合总数III 找出相加之和为n的k个数的组合
vector<vector<int>> combinationSum3(int k, int n)
{
    backtrackingcs3(k, n, 1);
    return ret;
}

const string letterMap[10] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz", // 9
};

string cur;
void backtrackinglc(string &digits, int startIndex, vector<string> &ret)
{
    if (cur.size() == digits.size())
    {
        ret.push_back(cur);
        return;
    }
    // '2' - '0' = 2
    // 这一层是由startIndex决定的,找到它对应的数字,然后取出对应的字符串
    int digit = digits[startIndex] - '0';
    string letters = letterMap[digit];
    // 这一层为这个数字对应的字母集合
    for (int i = 0; i < letters.size(); i++)
    {
        cur.push_back(letters[i]);
        backtrackinglc(digits, startIndex + 1, ret);
        cur.pop_back();
    }
}
// 17 电话号码的字母组合 找出digits可能得字母集合
vector<string> letterCombinations(string digits)
{
    vector<string> ret;
    if (digits.size() == 0)
    {
        return ret;
    }
    int size = digits.size();
    backtrackinglc(digits, 0, ret);
    return ret;
}

void backtrackingcs(vector<int> &candidates, int target, vector<vector<int>> &ret, int sum, int startIndex)
{
    if (sum >= target)
    {
        if (sum == target)
        {
            ret.push_back(path);
        }
        return;
    }
    // 可重复,所以下一层可以从i开始
    for (int i = startIndex; i < candidates.size(); i++)
    {
        path.push_back(candidates[i]);
        sum += candidates[i];
        backtrackingcs(candidates, target, ret, sum, i);
        sum -= candidates[i];
        path.pop_back();
    }
}

// 39 组合总数 给无重复的数组candidates和target,找出candidates中合为target的组合,可无限重复
vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    vector<vector<int>> ret;
    backtrackingcs(candidates, target, ret, 0, 0);
    return ret;
}

void backtrackingcs2(vector<int> &candidates, int target, vector<vector<int>> &ret, int sum, int startIndex, vector<bool> &used)
{
    if (sum >= target)
    {
        if (sum == target)
        {
            ret.push_back(path);
        }
        return;
    }

    for (int i = startIndex; i < candidates.size(); i++)
    {
        // 同一层不能一样
        if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false)
            continue;
        path.push_back(candidates[i]);
        sum += candidates[i];
        used[i] = true;
        backtrackingcs(candidates, target, ret, sum, i + 1);
        used[i] = false;
        sum -= candidates[i];
        path.pop_back();
    }
}

// 40 组合总数II 这里要去重解集和不能包括重复的组合,也就是说一层中一个数选了,那么之后这一层就不能选了(不然会导致结果集重复) 不同层可以重复
vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
    vector<vector<int>> ret;
    vector<bool> used(candidates.size(), false);
    sort(candidates.begin(), candidates.end());
    backtrackingcs2(candidates, target, ret, 0, 0, used);
    return ret;
}

vector<vector<string>> retPartition;
// 下标只能到s.size() - 1
// 0 1 2;
//
void backtrackingPartition(const string &s, int startIndex)
{
    if (startIndex >= s.size())
    {
        retPartition.push_back(path);
        return;
    }

    for (int i = startIndex; i < s.size(); i++)
    {
        if (isPalindrome(s, startIndex, i))
        {
            // s[startIndex, i]
            //  0 0
            string str = s.substr(startIndex, i - startIndex + 1);
            path.push_back(str); // a
            backtrackingPartition(s, i + 1);
            path.pop_back();
        }
        else
        {
            continue;
        }
    }
}

bool isPalindrome(const string &s, int start, int end)
{
    for (int i = start, j = end; i <= j; i++, j--)
    {
        if (s[i] != s[j])
        {
            return false;
        }
    }
    return true;
}
// 131 分割回文串
vector<vector<string>> partition(string s)
{
    backtrackingPartition(s, 0);
    return retPartition;
}

vector<string> retIp;
bool isValid(const string &s, int start, int end)
{
    if (start > end)
    {
        return false;
    }
    // 取出开头为0的数字
    if (s[start] == '0' && start != end)
    {
        return false;
    }
    int num = 0;
    for (int i = start; i <= end; i++)
    {
        // 去除不在数字范围的
        if (s[i] > '9' || s[i] < '0')
        {
            return false;
        }
        num = num * 10 + (s[i] - '0');
        // 要小于255
        if (num > 255)
        {
            return false;
        }
    }
    return true;
}
void backtrackingIp(string &s, int startIndex, int pointNum)
{
    if (pointNum == 3)
    {
        if (isValid(s, startIndex, s.size() - 1))
        {
            retIp.push_back(s);
        }
        return;
    }

    for (int i = startIndex; i < s.size(); i++)
    {
        if (isValid(s, startIndex, i))
        {
            s.insert(i + 1, ".");
            pointNum++;
            backtrackingIp(s, i + 2, pointNum);
            pointNum--;
            s.erase(s.begin() + i + 1);
        }
        else
        {
            break;
        }
    }
}

// 93 复原ip地址
vector<string> restoreIpAddresses(string s)
{
    retIp.clear(); // 清理全局变量
    if (s.size() < 4 || s.size() > 12)
        return retIp;
    backtrackingIp(s, 0, 0);
    return retIp;
}

#if 0
vector<vector<int>> ret;
vector<int> subset;
void backtrackingSubSet(vector<int> &nums, int startIndex)
{
    ret.push_back(subset);
    if (subset.size() == nums.size())
    {
        return;
    }

    for (int i = startIndex; i < nums.size(); i++)
    {
        subset.push_back(nums[i]);
        backtrackingSubSet(nums, i + 1);
        subset.pop_back();
    }
}
// 78 子集
vector<vector<int>> subsets(vector<int> &nums)
{
    
    backtrackingSubSet(nums, 0);

    return ret;
}
#endif

#if 0
vector<vector<int> > ret;
vector<int> subset;
void backTrackingSSWD(vector<int> &nums, int startIndex, vector<bool> &used){
    ret.push_back(subset);
    if(subset.size() == nums.size()){
        return;
    }
    
    for(int i = startIndex; i < nums.size();i++){
        //同一层要去重 [1,1,2] 前面的1拿过了,那么就不能拿了 false才表示是同一层啊,使用过
        if(i > 0 && nums[i] == nums[i - 1]&& used[i-1] == false){
            continue;
        }
        subset.push_back(nums[i]);
        used[i] = true;
        backTrackingSSWD(nums, i + 1, used);
        subset.pop_back();
        used[i] = false;
    }
}
// 90 子集II
vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    vector<bool> used(nums.size(), false);
    backTrackingSSWD(nums, 0, used);
    return ret;
}
#endif

#if 0 
vector<vector<int>> ret;
vector<int> sequence;

void backtrackingFS(vector<int> &nums, int startIndex)
{
    if (sequence.size() > 1)
    {
        ret.push_back(sequence);
    }
    unordered_set<int> uset;
    for (int i = startIndex; i < nums.size(); i++)
    {
        // 递减
        if (!sequence.empty() && nums[i] < sequence.back()
            // 重复
            || uset.find(nums[i]) != uset.end())
        {
            continue;
        }
        uset.insert(nums[i]); // 本层使用过
        sequence.push_back(nums[i]);
        backtrackingFS(nums, i + 1);
        sequence.pop_back();
    }
}
// 491 非递减子序列
vector<vector<int>> findSubsequences(vector<int> &nums)
{
    // 选取 每一层表示选择一个元素, 只能选一个,下一层表示继续选元素
    backtrackingFS(nums, 0);
    return ret;
}

#endif

#if 0
vector<vector<int>> ret;
vector<int> per;

void backtrackingPermute(vector<int> &nums, vector<bool> &used)
{
    if (per.size() == nums.size())
    {
        ret.push_back(per);
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        //[1,2,3]
        //去除选了1之后不能再选1
        if (used[i] == true)
            continue;
        per.push_back(nums[i]);
        used[i] = true;
        backtrackingPermute(nums, used);
        used[i] = false;
        per.pop_back();
    }
}

// 46 全排列
vector<vector<int>> permute(vector<int> &nums)
{
    vector<bool> used(nums.size(), false);
    backtrackingPermute(nums, used);
    return ret;
}

#endif

#if 0
vector<vector<int>> ret;
vector<int> per;
void backtrackingPU(vector<int> &nums, vector<bool> &used)
{
    if (per.size() == nums.size())
    {
        ret.push_back(per);
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        if (used[i] == true)
        {
            continue;
        }
        // 这里判断前一个是否一样,是否used为false,false才表示同一层啊,英文循环下一轮肯定置为false了,true是用来给不同层用的
        if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false)
        {
            continue;
        }
        per.push_back(nums[i]);
        used[i] = true;
        backtrackingPU(nums, used);
        used[i] = false;
        per.pop_back();
    }
}

// 47 全排列II
vector<vector<int>> permuteUnique(vector<int> &nums)
{
    vector<bool> used(nums.size(), false);
    sort(nums.begin(), nums.end());
    backtrackingPU(nums, used);
    return ret;
}

#endif

#if 0
unordered_map<string, map<string, int>> targets;
//<起飞机场, <落地机场, 机票数量>>
bool backtrackingFindItinerary(vector<vector<string>> &tickets, vector<string>& result)
{
    if(result.size() == tickets.size() + 1){
        return true;
    }
    //获得result中的最后一个作为起始机场,去targets里面找出来 <落地机场, 数量>
    for(pair<const string, int>& target : targets[result[result.size() - 1]]){
        if(target.second > 0){
            result.push_back(target.first);
            target.second--;
            //这里因为只要找一条线, 假如全部遍历完的话就是false,说明这个机票不合理.要用别的机票,所以要加回去
            //假如是正确的直接返回就好了.
            if(backtrackingFindItinerary(ticketNum, result)) return true;
            result.pop_back();
            target.second++;
        }
    }
    return false;
}


// 332 重新安排行程
vector<string> findItinerary(vector<vector<string>> &tickets)
{
    vector<string> result;
    for(vector<string>& vec : tickets){
        targets[vec[0]][vec[1]]++;
    }
    result.push_back("JFK");
    backtrackingFindItinerary(tickets, result);

}
#endif

#if 0
vector<vector<string>> ret;
bool isValid(int x, int y, vector<string> &sol, int n)
{

    // 判断行, 默认这一行只有你会是Q了,判断这一列
    for (int i = 0; i < n; i++)
    {
        if (sol[i][] == 'Q')
        {
            return false;
        }
    }
    // 判断对角线 只需往前看
    for (int i = x - 1, j = y + 1; i >= 0 && j < n; i--, j++)
    {
        if (sol[i][j] == 'Q')
            return false;
    }

    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (sol[i][j] == 'Q')
            return false;
    }
    return true;
}

void backtrackingNQ(int row, int n, vector<string> sol)
{
    if (row == n)
    {
        ret.push_back(sol);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (isValid(row, i, sol, n))
        {
            sol[row][i] = 'Q';
            backtrackingNQ(row + 1, n, sol);
            sol[row][i] = '.';
        }
        else
        {
            continue;
        }
    }
}
// 51 NQueen
vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> solution(n, string(n, '.'));
    backtrackingNQ(0, n, solution);
    return ret;
}

#endif

bool isValid(int row, int col, vector<vector<char>> &board, int num)
{
    // 判断这一列是否合法
    for (int i = 0; i < 9; i++)
    {
        if (board[i][col] == num)
        {
            return false;
        }
    }
    // 判断这一行是否合法
    for (int i = 0; i < 9; i++)
    {
        if (board[row][i] == num)
        {
            return false;
        }
    }
    // 判断这个3*3宫格是否合法
    // 得到3*3宫格的起始
    // 0 / 3 = 0 第0个格子 
    // 1 / 3 = 0 第0个格子

    // 3/3 = 1 第一个格子 起始位置为:3
    int rowNum = (row / 3) * 3;
    int colNum = (col / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[rowNum + i][colNum + j] == num)
            {
                return false;
            }
        }
    }
    return true;
}

bool backtrackingSolveSudoku(vector<vector<char>> &board){
    for(int i = 0; i < board.size(); i++){
        for(int j =0; j < board[0].size(); j++){
            if(board[i][j] == '.'){
                for(char k = '1'; k <= '9'; k++){
                    if(isValid(i, j, board, k)){
                        board[i][j] = k;
                        if(backtrackingSolveSudoku(board)) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}
// 37 解数独
void solveSudoku(vector<vector<char>> &board)
{
    backtrackingSolveSudoku(board);
}