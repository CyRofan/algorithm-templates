// 求解c[k] = \sum_{i | j == k} (a[i] * b[j])
void Or(LL a[], int n, int type)  // type = 1为正变换, -1为复变换, n为数组长度
{
    for (int x = 2; x <= n; x <<= 1)  // x为枚举的区间长度
    {
        int k = x >> 1;
        for (int i = 0; i < n; i += x)
            for (int j = 0; j < k; j ++ )
                a[i + j + k] += a[i + j] * type;
    }
}

void solve()
{
    Or(a, n, 1);
    Or(b, n, 1);
    for (int i = 0; i < n; i ++ )  // FWT(C) = FWT(A) * FWT(B)
        c[i] = a[i] * b[i];
    Or(c, n, -1);
}