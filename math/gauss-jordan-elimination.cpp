// 实数方程组, a为增广矩阵
int gauss(vector<vector<double>> a, vector<double> &ans)
{
    int n = (int)a.size();
    int m = (int)a[0].size() - 1;

    vector<int> where(m, -1);  // 第i列的主元的行号, -1表示自由变量
    for (int col = 0, row = 0; col < m && row < n; col ++ )
    {
        int sel = row;
        for (int i = row; i < n; i ++ )
            if (fabs(a[i][col]) > fabs(a[sel][col]))
                sel = i;

        if (fabs(a[sel][col]) < eps)
            continue;
        for (int i = col; i <= m; i ++ )
            swap(a[sel][i], a[row][i]);
        where[col] = row;

        for (int i = 0; i < n; i ++ )
            if (i != row)
            {
                double c = a[i][col] / a[row][col];
                for (int j = col; j <= m; j ++ )
                    a[i][j] -= a[row][j] * c;
            }

        row ++ ;
    }

    for (int i = 0; i < m; i ++ )
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];

    for (int i = 0; i < n; i ++ )
    {
        double sum = 0;
        for (int j = 0; j < m; j ++ )
            sum += ans[j] * a[i][j];

        if (fabs(sum - a[i][m]) > eps)
            return 0;  // 无解
    }

    for (int i = 0; i < m; i ++ )
        if (where[i] == -1)
            return 2;  // 无穷多解

    return 1;
}

// 异或方程组, n为系数矩阵的行数, m为系数矩阵的列数, a为增广矩阵
int gauss(int n, int m, vector<bitset<N>> a, bitset<N> &ans)
{
    vector<int> where(m, -1);  // 第i列的主元的行号, -1表示自由变量
    for (int col = 0, row = 0; col < m && row < n; col ++ )
    {
        for (int i = row; i < n; i ++ )
            if (a[i][col])
            {
                swap(a[i], a[row]);
                break;
            }

        if (!a[row][col]) continue;
        where[col] = row;

        for (int i = 0; i < n; i ++ )
            if (i != row && a[i][col])
                a[i] ^= a[row];

        row ++ ;
    }

    for (int i = 0; i < m; i ++ )
        if (where[i] != -1)
            ans[i] = a[where[i]][m];

    for (int i = 0; i < n; i ++ )
    {
        int sum = (a[i] & ans).count();
        sum %= 2;
        if (sum != a[i][m])
            return 0;  // 无解
    }

    for (int i = 0; i < m; i ++ )
        if (where[i] == -1)
            return 2;  // 多解

    return 1;
}