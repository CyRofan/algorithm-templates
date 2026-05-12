const int B = 60;
struct linear_basis
{
    LL num[B + 1];
    //int t[B];
    bool insert(LL x)
    {
        for (int i = B - 1; i >= 0; i -- )
            if (x >> i & 1)
            {
                if (num[i] == 0)
                {
                    num[i] = x;
                    return true;
                }
                x ^= num[i];
            }
        return false;
    }

    // 带时间的线性基
    /*void insert(int x, int t_)
    {
        for (int i = B - 1; i >= 0; i -- )
            if (x >> i & 1)
            {
                if (num[i] == 0)
                {
                    num[i] = x;
                    t[i] = t_;
                    return;
                }
                else
                {
                    if (t_ > t[i])
                    {
                        swap(t[i], t_);
                        swap(num[i], x);
                    }
                    x ^= num[i];
                }
            }
    }*/

    LL querymin(LL x)
    {
        for (int i = B - 1; i >= 0; i -- )
            x = min(x, x ^ num[i]);
        return x;
    }

    LL querymax(LL x)
    {
        for (int i = B - 1; i >= 0; i -- )
            x = max(x, x ^ num[i]);
        return x;
    }
} T;