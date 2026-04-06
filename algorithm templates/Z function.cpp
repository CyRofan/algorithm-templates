vector<int> Z(string &s)
{
    int n = s.size();
    s = "$" + s;

    vector<int> z(n + 1);
    z[1] = n;
    int L = 1, R = 0;
    for (int i = 2; i <= n; i ++ )
    {
        if (i > R) z[i] = 0;
        else
        {
            int k = i - L + 1;
            z[i] = min(z[k], R - i + 1);
        }

        while (i + z[i] <= n && s[i + z[i]] == s[1 + z[i]])
            z[i] ++ ;

        if (i + z[i] - 1 > R)
            L = i, R = i + z[i] - 1;
    }

    return z;
}