constexpr int N = 1000010;

int p[N];
int primes[N], cnt;

void sieve(int n)
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
}