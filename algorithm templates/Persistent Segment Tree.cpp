int idx;
int root[N];
struct Node
{
    int l, r, val;  // 左右儿子编号, 元素数量
} tr[N << 5];

// 在[l, r]权值范围建树 
void build(int version, int l, int r)
{
    if (l == r) 
    {
        tr[version].val = 0;
        return;
    }

    int mid = l + r >> 1;
    tr[version].l = ++ idx, tr[version].r = ++ idx;
    build(tr[version].l, l, mid);
    build(tr[version].r, mid + 1, r);

    tr[version].val = tr[tr[version].l].val + tr[tr[version].r].val;
}

//权值范围, 上一个版本的节点编号, 当前节点的编号, 修改的位置, 修改的数量
void update(int l, int r, int last, int now, int pos, int val) 
{
    if (l == r) 
    {
        tr[now].val = tr[last].val + val;
        return;
    }

    int mid = l + r >> 1;
    tr[now].l = tr[last].l, tr[now].r = tr[last].r;
    if (pos <= mid) 
    {
        tr[now].l = ++ idx;
        update(l, mid, tr[last].l, tr[now].l, pos, val);
    }
    else 
    {
        tr[now].r = ++ idx;
        update(mid + 1, r, tr[last].r, tr[now].r, pos, val);
    }

    tr[now].val = tr[tr[now].l].val + tr[tr[now].r].val;
}

//区间第k小查询(权值范围, 版本节点编号, 第k小)
int query(int l, int r, int last, int now, int k) 
{
    if (l == r) return l;
    int mid = l + r >> 1, d = tr[tr[now].l].val - tr[tr[last].l].val;
    if (d < k)
        return query(mid + 1, r, tr[last].r, tr[now].r, k - d);
    return query(l, mid, tr[last].l, tr[now].l, k);
}

//查询区间大于等于x的数的个数(v:离散化后的数组, 权值范围, 版本节点编号)
int query(int l, int r, int last, int now, int x)
{
    if (x > v[r]) return 0;
    if (l == r) return tr[now].val - tr[last].val;
    int mid = l + r >> 1;
    if (v[mid] < x) return query(mid + 1, r, tr[last].r, tr[now].r, x);
    return tr[tr[now].r].val - tr[tr[last].r].val + query(l, mid, tr[last].l, tr[now].l, x);
}