constexpr int N = 1E7 + 10;

int p[N];
int primes[N], cnt;
bool vis[N];

void sieve(int n, LL l, LL r)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!p[i]) p[i] = i, primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ )
        {
            p[i * primes[j]] = primes[j];
            if (p[i] == primes[j]) break;
        }
    }

    for (int i = 0; i < cnt; i ++ )
    {
        int p = primes[i];
        for (LL j = r / p * p; j >= l && j > p; j -= p)
            vis[j - l] = true;
    }
}