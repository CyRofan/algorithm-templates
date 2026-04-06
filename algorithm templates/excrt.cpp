LL exgcd(LL a, LL b, LL &x, LL &y) 
{
    if (b == 0) 
    {
        x = 1, y = 0;
        return a;
    }
    LL g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

bool merge(LL &m1, LL &a1, LL m2, LL a2) 
{
    LL u, v;
    LL g = exgcd(m1, m2, u, v);
    LL m = m1 / g * m2;
    if ((a2 - a1) % g != 0)
        return false;

    LL d = (a2 - a1) / g;
    LL x = (__int128(u) * m1 * d + a1) % m;
    if (x < 0)
        x += m;

    m1 = m, a1 = x;
    return true;
}
