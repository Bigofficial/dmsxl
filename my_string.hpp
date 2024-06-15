#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 344反转字符串
void reverseString(vector<char> &s)
{
    // 0 1 2; 3
    // 0 1 2 3; 4
    // 0 1 2 3 4; 5
    // 0 1 2 3 4 5 ; 6

    int round = s.size() / 2;
    for (int i = 0; i < round; i++)
    {
        swap(s[i], s[s.size() - i - 1]);
    }
}

void my_reverse(string &s, int begin, int end)
{
    while (begin < end)
    {
        swap(s[begin++], s[end--]);
    }
}

// 541反转字符串
string reverseStr(string s, int k)
{
    int size = s.size();
    int left = size % (2 * k);
    int round = size / (2 * k); // 8 1 4
    // 0 1 2 3 4 5 6 7
    //
    // 对每个2k进行操作
    int start = 0;
    while (round--)
    {
        my_reverse(s, start, start + k - 1);
        start += 2 * k;
    }
    if (left < k)
        my_reverse(s, start, s.size() - 1);
    else
        my_reverse(s, start, start + k - 1);
    return s;
}

// 54替换数字
// 双指针
string replaceNumber(string &s)
{
    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            count++;
    }
    int oldIndex = s.size() - 1;
    s.resize(s.size() + count * 5);
    int newIndex = s.size() - 1;
    while (oldIndex >= 0)
    {
        if (s[oldIndex] >= '0' && s[oldIndex] <= '9')
        {
            s[newIndex--] = 'r';
            s[newIndex--] = 'e';
            s[newIndex--] = 'b';
            s[newIndex--] = 'm';
            s[newIndex--] = 'u';
            s[newIndex--] = 'n';
        }
        else
        {
            s[newIndex--] = s[oldIndex];
        }
        oldIndex--;
    }
    return s;
}

void removeExtraSpaces(string &s)
{
    for (int i = s.size() - 1; i > 0; i--)
    {
        if (s[i] == s[i - 1] && s[i] == ' ')
            s.erase(s.begin() + i);
    }

    if (s.size() > 0 && s[s.size() - 1] == ' ')
    {
        s.erase(s.begin() + s.size() - 1);
    }

    if (s.size() > 0 && s[0] == ' ')
        s.erase(s.begin());
}

// 151翻转字符串里面的单词
string reverseWords(string s)
{
    removeExtraSpaces(s);
    my_reverse(s, 0, s.size() - 1);
    int start = 0;
    for (int i = 0; i <= s.size(); i++)
    {
        if (i == s.size() || s[i] == ' ')
        {
            my_reverse(s, start, i - 1);
            start = i + 1;
        }
    }
    return s;
}

// 右旋字符串
// abcdefg
// fgabcde

// gfedcba
// fgabcd

void rightRotate(string s, int num)
{
    my_reverse(s, 0, s.size() - 1);
    my_reverse(s, 0, num - 1);
    my_reverse(s, num, s.size() - 1);
}

void getNext(int *next, const string &s)
{

    // 010120
    int j = 0;   // j表示前缀末尾
    next[0] = 0; // 表示长度 也表示跳转下标
    for (int i = 1; i < s.size(); i++)
    {
        // 说明i往前和j往前可能有部分的匹配
        // 这里j=next[j-1]也就是跳转至前面都匹配的状况
        while (j > 0 && s[i] != s[j])
        {                    // j要保证大于0，因为下面有取j-1作为数组下标的操作
            j = next[j - 1]; // 注意这里，是要找前一位的对应的回退位置了
        }
        if (s[i] == s[j])
        {
            j++;
        }
        next[i] = j;
    }
}
// 找出字符串中的第一个匹配项的下标
int strStr(string haystack, string needle)
{
    if (needle.size() == 0)
    {
        return 0;
    }
    vector<int> next(needle.size());
    getNext(&next[0], needle);
    int j = 0;
    for (int i = 0; i < haystack.size(); i++)
    {
        while (j > 0 && haystack[i] != needle[j])
        {
            j = next[j - 1];
        }
        if (haystack[i] == needle[j])
        {
            j++;
        }
        if (j == needle.size())
        {
            return (i - needle.size() + 1);
        }
    }
    return -1;
}

bool repeatedSubstringPattern(string s)
{
    string t = s + s;
    t.erase(t.begin());
    t.erase(t.end() - 1);
    if(t.find(s) != t.end()) return true;
    return false;
}
