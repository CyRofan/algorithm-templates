int hh, tt;
int tr[N][26], idx;
int go[N][26];  // go[u][i] u读入i到达的状态
int fail[N];  // u的最长真后缀等于从根节点到fail[u]的串
int q[N];

void insert(string s)
{
    int u = 0;
    for (auto c : s)
    {
        int i = c - 'a';
        if (!tr[u][i]) tr[u][i] = ++ idx;
        u = tr[u][i];
    }
}

void build()
{
    hh = 0, tt = -1;
    q[ ++ tt] = 0;
    while (hh <= tt)
    {
        int u = q[hh ++ ];
        for (int i = 0; i < 26; i ++ )
            if (tr[u][i])
            {
                int v = tr[u][i];
                go[u][i] = v;
                if (u == 0)
                    fail[v] = 0;
                else
                    fail[v] = go[fail[u]][i];
                
                q[ ++ tt] = v;
            }
            else
                go[u][i] = go[fail[u]][i];
    }
}