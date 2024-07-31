#include <vector>
#include <string>
using namespace std;

// 455 分发饼干
int findContentChildren(vector<int> &g, vector<int> &s)
{
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int result = 0;
    int startJ = 0;
    for (int i = 0; i < g.size(); i++)
    {
        for (int j = startJ; j < s.size(); j++)
        {
            if (s[j] >= g[i])
            {
                result++;
                startJ = j + 1;
                break;
            }
        }
    }
    return result;
}