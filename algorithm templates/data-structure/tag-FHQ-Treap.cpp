#include <bits/stdc++.h>

using namespace std;

constexpr int N = 100010, INF = 1e9;

mt19937 rnd(114514);
int root, T1, T2, T3, idx;
struct FHQ
{
    int ls, rs, key, sz, val, tag;
} fhq[N];

int create(int v)
{
    fhq[ ++ idx] = {0, 0, (int)rnd(), 1, v, 0};
    return idx;
}

void pushup(int u)
{
    fhq[u].sz = fhq[fhq[u].ls].sz + fhq[fhq[u].rs].sz + 1;
}

void settag(int u, int tag)
{
    swap(fhq[u].ls, fhq[u].rs);
    fhq[u].tag ^= 1;
}

void pushdown(int u)
{
    if (fhq[u].tag)
    {
        settag(fhq[u].ls, fhq[u].tag);
        settag(fhq[u].rs, fhq[u].tag);
        fhq[u].tag = 0;
    }
}

void split(int u, int v, int &x, int &y)
{
    if (!u)
    {
        x = 0, y = 0;
        return;
    }

    if (fhq[u].val > v)
    {
        y = u;
        split(fhq[u].ls, v, x, fhq[u].ls);
    }
    else
    {
        x = u;
        split(fhq[u].rs, v, fhq[u].rs, y);
    }

    pushup(u);
}

void split_rank(int u, int k, int &x, int &y)
{
    if (!u)
    {
        x = 0, y = 0;
        return;
    }

    pushdown(u);
    int tmp = fhq[fhq[u].ls].sz + 1;
    if (k == tmp)
    {
        x = u;
        y = fhq[u].rs;
        fhq[u].rs = 0;
    }
    else if (k < tmp)
    {
        y = u;
        split_rank(fhq[u].ls, k, x, fhq[u].ls);
    }
    else
    {
        x = u;
        split_rank(fhq[u].rs, k - tmp, fhq[u].rs, y);
    }

    pushup(u);
}

int merge(int x, int y)
{
    if (!x || !y) return x + y;
    if (fhq[x].key > fhq[y].key)
    {
        pushdown(x);
        fhq[x].rs = merge(fhq[x].rs, y);
        pushup(x);
        return x;
    }
    else
    {
        pushdown(y);
        fhq[y].ls = merge(x, fhq[y].ls);
        pushup(y);
        return y;
    }
}

void insert(int v)
{
    split(root, v, T1, T2);
    root = merge(merge(T1, create(v)), T2);
}

void erase(int x)
{
    split(root, x, T1, T2);
    split(T1, x - 1, T1, T3);
    T3 = merge(fhq[T3].ls, fhq[T3].rs);
    root = merge(merge(T1, T3), T2);
}

int find_rank(int x)
{
    split(root, x - 1, T1, T2);
    int res = fhq[T1].sz + 1;
    root = merge(T1, T2);
    return res;
}

int kth(int k)
{
    int u = root;
    while (u)
    {
        int tmp = fhq[fhq[u].ls].sz + 1;
        if (tmp == k) break;
        else if (k < tmp) u = fhq[u].ls;
        else 
        {
            k -= tmp;
            u = fhq[u].rs;
        }
    }

    return fhq[u].val;
}

int find_pre(int u, int v)
{
    if (u == 0) return -INF;
    if (fhq[u].val < v)
    {
        int res = find_pre(fhq[u].rs, v);
        return res == -INF ? fhq[u].val : res;
    }
    else return find_pre(fhq[u].ls, v);
}

int find_next(int u, int v)
{
    if (u == 0) return INF;
    if (fhq[u].val > v)
    {
        int res = find_next(fhq[u].ls, v);
        return res == INF ? fhq[u].val : res;
    }
    else return find_next(fhq[u].rs, v);
}

void dfs(int u)
{
    pushdown(u);
    if (fhq[u].ls) dfs(fhq[u].ls);
    cout << u << ' ';
    if (fhq[u].rs) dfs(fhq[u].rs);
}

void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i ++ )
        root = merge(root, create(i));

    while (m -- )
    {
        int l, r;
        cin >> l >> r;
        split_rank(root, l - 1, T1, T2);
        split_rank(T2, r - l + 1, T2, T3);
        settag(T2, 1);
        root = merge(merge(T1, T2), T3);
    }

    dfs(root);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T = 1;
    
    while (T -- ) solve();

    return 0;
}