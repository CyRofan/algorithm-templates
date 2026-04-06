void dfs(int u)
{
    dfn[u] = low[u] = ++ idx;
    stk.push(u);
    ins[u] = true;

    for (auto v : e[u])
        if (!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if (ins[v]) low[u] = min(low[u], dfn[v]);

    if (dfn[u] == low[u])
    {
        ++ cnt;
        while (true)
        {
            int v = stk.top();
            stk.pop();
            ins[v] = false;
            bel[v] = cnt;
            if (v == u) break;
        }
    }
}