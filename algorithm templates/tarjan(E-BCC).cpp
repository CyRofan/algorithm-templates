void dfs(int u, int id)
{
    dfn[u] = low[u] = ++ idx;
    stk.push(u);
    ins[u] = true;
    for (auto [v, id2] : e[u])
        if (!dfn[v])
        {
            dfs(v, id2);
            low[u] = min(low[u], low[v]);
        }
        else if (id2 != id) low[u] = min(low[u], dfn[v]);
        
    if (dfn[u] == low[u])
    {
        if (id != -1) bridge.push_back(id);
        ++ cnt;
        vector<int> c;
        while (true)
        {
            int v = stk.top();
            stk.pop();
            c.push_back(v);
            ins[v] = false;
            bel[v] = cnt;
            if (v == u) break;
        }
        bcc.push_back(c);
    }
}