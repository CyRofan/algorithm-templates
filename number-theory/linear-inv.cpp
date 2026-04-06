constexpr int N = 100010, mod = 1E9 + 7;

LL inv[N];
LL fact[N], infact[N];

int qmi(int a, int k)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = 1LL * res * a % mod;
        a = 1LL * a * a % mod;
        k >>= 1;
    }

    return res;
}

void get_inv(int n)
{
    inv[1] = 1;
    for (int i = 2; i <= n; i ++ )
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;

    fact[0] = 1;
    for (int i = 1; i <= n; i ++ )
        fact[i] = fact[i - 1] * i % mod;
    infact[n] = qmi(fact[n], mod - 2);
    for (int i = n - 1; i >= 0; i -- )
        infact[i] = infact[i + 1] * (i + 1) % mod;
}