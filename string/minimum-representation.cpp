void getmin()
{
    n = strlen(s + 1);
    for (int l = 1; l <= n; l ++ )
        s[l + n] = s[l];

    int i = 1, j = 2;
    while (j <= n)
    {
        int k = 0;
        while (k < n && s[i + k] == s[j + k]) k ++ ;
        if (s[i + k] > s[j + k]) i += k + 1;
        else j += k + 1;
        if (i == j) j ++ ;
        if (i > j) swap(i, j);
    }

    for (int l = i; l <= i + n - 1; l ++ )
        cout << s[l];
}