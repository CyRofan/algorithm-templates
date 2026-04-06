template<typename T>
struct FlowGraph
{
    int s, t, vtot;
    int h[N], idx;
    int dis[N], cur[N];
    struct Edge
    {
        int v, nxt;
        T f;
    } e[M * 2];

    void add(int u, int v, T f1, T f2 = 0)
    {
        e[idx] = {v, h[u], f1}; h[u] = idx ++ ;
        e[idx] = {u, h[v], f2}; h[v] = idx ++ ;
    }

    bool bfs()
    {
        for (int i = 1; i <= vtot; i ++ ) 
        {
            dis[i] = 0;
            cur[i] = h[i];
        }
        queue<int> q;
        q.push(s); dis[s] = 1;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (int i = h[u]; ~i; i = e[i].nxt)
                if (e[i].f && !dis[e[i].v])
                {
                    int v = e[i].v;
                    dis[v] = dis[u] + 1;
                    if (v == t) return true;
                    q.push(v);
                }
        }
        return false;
    }

    T dfs(int u, T m)
    {
        if (u == t) return m;
        T flow = 0;
        for (int i = cur[u]; ~i; cur[u] = i = e[i].nxt)
            if (e[i].f && dis[e[i].v] == dis[u] + 1)
            {
                T f = dfs(e[i].v, min(m, e[i].f));
                e[i].f -= f;
                e[i ^ 1].f += f;
                m -= f;
                flow += f;
                if (!m) break;
            }
        if (!flow) dis[u] = -1;
        return flow;
    }

    T dinic()
    {
        T flow = 0;
        while (bfs()) flow += dfs(s, numeric_limits<T>::max());
        return flow;
    }
    
    void init(int s_, int t_, int vtot_)
    {
        s = s_;
        t = t_;
        vtot = vtot_;
        idx = 0;
        for (int i = 1; i <= vtot; i ++ ) h[i] = -1;
    }
};