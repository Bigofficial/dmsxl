#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
using namespace std;
// 242有效字母的异位词
bool isAnagram(string s, string t)
{
    unordered_map<char, int> char_map;
    for (int i = 0; i < s.size(); i++)
    {
        char_map[s[i]]++;
    }
    for (int i = 0; i < t.size(); i++)
    {
        char_map[t[i]]--;
    }

    for (auto it : char_map)
    {
        if (it.second != 0)
        {
            return false;
        }
    }
    return true;
}

// 349 两个数组的交集
vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
{
    unordered_set<int> my_set;
    vector<int> ret;
    for (auto it : nums1)
    {
        my_set.insert(it);
    }
    for (auto it : nums2)
    {
        if (my_set.find(it) != my_set.end())
        {
            ret.push_back(it);
            my_set.erase(it);
        }
    }
    return ret;
}

// 202快乐数
bool isHappy(int n)
{
    unordered_set<int> used_num;

    while (1)
    {
        int sum = 0;
        // n = 100  n%10=0
        while (n)
        {
            sum += ((n % 10) * (n % 10));
            n = n / 10;
        }
        if (sum == 1)
            return true;
        if (used_num.find(sum) != used_num.end()) //  之前有
            return false;
        used_num.insert(sum);
        n = sum;
    }
}

// 两数之和
vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> complementary;
    for (int i = 0; i < nums.size(); i++)
    {
        if (complementary.find(nums[i]) != complementary.end())
            return vector<int>{complementary[nums[i]], i};
        complementary.insert({target - nums[i], i});
    }
    return {};
}

// 454四数相加II
int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4)
{
    unordered_map<int, int> AB;
    int count = 0;
    for (auto it1 : nums1)
    {
        for (auto it2 : nums2)
        {
            AB[it1 + it2]++;
        }
    }

    for (auto it1 : nums3)
    {
        for (auto it2 : nums4)
        {
            if (AB.find(0 - it1 - it2) != AB.end())
            {
                count += AB[0 - it1 - it2];
            }
        }
    }
    return count;
}

// 383赎金信
bool canConstruct(string ransomNote, string magazine)
{
    unordered_map<char, int> mag;
    for (int i = 0; i < magazine.size(); i++)
    {
        mag[magazine[i]]++;
    }
    for (int i = 0; i < ransomNote.size(); i++)
    {
        mag[ransomNote[i]]--;
        if (mag[ransomNote[i]] < 0)
            return false;
    }
    return true;
}

// 15 三数之和
vector<vector<int>> threeSum(vector<int> &nums)
{
    //-2 1 1 1 1
    // 哈希法的遍历顺序是 i > c > j ,c是遍历j走过的数组值 如果有2个连续的就是C = j ，3个连续的j就重复了
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] > 0)
            break;
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        unordered_set<int> set;
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (j > i + 2 && nums[j] == nums[j - 1] && nums[j - 1] == nums[j - 2]) // b和c相同的情况（去除最后的那个相同情况
                continue;

            int c = 0 - (nums[i] + nums[j]);
            if (set.find(c) != set.end())
            {
                result.push_back({nums[i], nums[j], c});
                set.erase(c); // 去除中间的那个
            }
            else
            {
                set.insert(nums[j]);
            }
        }
    }
    return result;
}

// 2 -1 -1 -1 -1
vector<vector<int>> threeSum1(vector<int> &nums)
{
    vector<vector<int>> result;

    // 先对数组进行排序
    sort(nums.begin(), nums.end());
    // i c j
    for (int i = 0; i < nums.size(); ++i)
    {
        // 跳过重复的元素
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }
        unordered_set<int> seen;
        for (int j = i + 1; j < nums.size(); ++j)
        {
            int complement = -nums[i] - nums[j];
            if (seen.count(complement))
            {
                result.push_back({nums[i], nums[j], complement});
                // 跳过重复的元素
                while (j + 1 < nums.size() && nums[j] == nums[j + 1])
                {
                    ++j;
                }
            }
            seen.insert(nums[j]); // 相当于c去重
        }
    }

    return result;
}

vector<vector<int>> threeSum2(vector<int> &nums)
{
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] > 0)
            break;
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        int left = i + 1, right = nums.size() - 1;
        while (left < right)
        {
            if (nums[i] + nums[left] + nums[right] == 0)
            {
                result.push_back({nums[i], nums[left], nums[right]});
                left++, right--;
                while (left < right && nums[left] == nums[left - 1])
                    left++;
                while (left < right && nums[right] == nums[right + 1])
                    right--;
            }
            else if (nums[i] + nums[left] + nums[right] < 0)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
    }
    return result;
}

// 18四数之和
vector<vector<int>> fourSum(vector<int> &nums, int target)
{
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int k = 0; k < nums.size(); k++)
    {
        if (nums[k] > target && nums[k] >= 0) // 剪枝(还要考虑nums为负数 且target也为负数)
            break;
        if (k > 0 && nums[k] == nums[k - 1]) // 去重
            continue;
        for (int i = k + 1; i < nums.size(); i++)
        {
            if (nums[k] + nums[i] > target && nums[k] + nums[i] >= 0) // 剪枝
                break;
            if (i > k + 1 && nums[i] == nums[i - 1]) // 去重
                continue;
            int left = i + 1, right = nums.size() - 1;
            while (left < right)
            {
                if ((long)nums[k] + nums[i] + nums[left] + nums[right] == target)
                {
                    result.push_back({nums[k], nums[i], nums[left], nums[right]});
                    //去重
                    left++, right--;
                    while(left < right && nums[left] == nums[left - 1]) left++;
                    while(left < right && nums[right] == nums[right + 1]) right--;
                }else if((long)nums[k] + nums[i] + nums[left] + nums[right] < target){
                    left++;
                }else{
                    right--;
                }
            }
        }
    }
    return result;
}
