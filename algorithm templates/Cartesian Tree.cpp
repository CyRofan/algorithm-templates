/*
一般是给定排列 a1, a2,..., an
树中节点编号表示位置
建树的过程为先找到当前区间[l, r]最小值的位置x作为当前子树的根节点,
然后递归[l, x - 1]和[x + 1, r]
单调栈可以做到O(n)建树, 维护单调递增的右链
性质: 区间[l, r]的最小值为树中l与r的lca的权值
*/

int a[N];
int l[N], r[N];  // 左右儿子 0表示儿子不存在
vector<int> stk;  // root: stk[0]
 
void build()
{
    for (int i = 1; i <= n; i ++ )
    {
        int last = 0;  // 最后一个出栈的位置
        while (!stk.empty() && a[stk.back()] > a[i])
        {
            last = stk.back();
            stk.pop_back();
        }

        if (!stk.empty())
            r[stk.back()] = i;
        l[i] = last;
        stk.push_back(i);
    }
}