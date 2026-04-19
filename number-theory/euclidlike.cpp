using i64 = long long;
using i128 = __int128;

ostream &operator<<(ostream &os, const i128 &v) 
{
    if (v <= 1000000000000000000)
        return os << i64(v);
    return os << i64(v / 1000000000000000000) << setw(18) << setfill('0') << i64(v % 1000000000000000000);
}

//floor((a * i + b) / m) (i = 0, 1, ..., n - 1)
i128 floor_sum(i128 n, i128 m, i128 a, i128 b) 
{
    i128 ans = 0;
    if (a < 0) 
    {
        i128 a2 = (a % m + m) % m;
        ans -= n * (n - 1) / 2 * ((a2 - a) / m);
        a = a2;
    }
    if (b < 0) 
    {
        i128 b2 = (b % m + m) % m;
        ans -= n * ((b2 - b) / m);
        b = b2;
    }
    while (1) 
    {
        if (a >= m) 
        {
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if (b >= m) 
        {
            ans += n * (b / m);
            b %= m;
        }
        i128 y_max = a * n + b;
        if (y_max < m)
            break;
        
        n = y_max / m;
        b = y_max % m;
        swap(m, a);
    }
    return ans;
}