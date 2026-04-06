void dfs(int u, int fa)
{
    dfn[u] = low[u] = ++ idx;
    stk.push(u);
    int ch = 0;
    for (auto v : e[u])
        if (!dfn[v])
        {
            ch ++ ;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])
            {
                cut[u] = true;
                vector<int> c;
                c.push_back(u);
                while (true)
                {
                    int w = stk.top();
                    stk.pop();
                    c.push_back(w);
                    if (w == v) break;
                }
                bcc.push_back(c);
            }
        }
        else if (v != fa) low[u] = min(low[u], dfn[v]);

    // 孤立点
    if (fa == -1 && ch == 0) bcc.push_back(vector<int>(1, u));
    // 如果是根结点并且儿子数量小于等于1, 则不是割点
    if (fa == -1 && ch <= 1) cut[u] = false;
}