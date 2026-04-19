constexpr int P = 998244353;
constexpr int G = 3;

class NTTPolyMul
{
private:
    int tot = 1;
    vector<int> rev = {0};

    int power(int a, int b) const
    {
        int res = 1;
        while (b)
        {
            if (b & 1) res = 1LL * res * a % P;
            a = 1LL * a * a % P;
            b >>= 1;
        }
        return res;
    }

    void init(int need)
    {
        int bit = 0, new_tot = 1;
        while (new_tot < need)
            new_tot <<= 1, bit ++ ;

        if (new_tot == tot) return;

        tot = new_tot;
        rev.assign(tot, 0);
        if (tot == 1) return;

        for (int i = 0; i < tot; i ++ )
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    }

    void ntt(vector<int> &a, int inv) const
    {
        for (int i = 0; i < tot; i ++ )
            if (i < rev[i])
                swap(a[i], a[rev[i]]);

        for (int len = 1; len < tot; len <<= 1)
        {
            int w1 = power(G, (P - 1) / (len << 1));
            if (inv == -1) w1 = power(w1, P - 2);
            for (int i = 0; i < tot; i += (len << 1))
            {
                int w = 1;
                for (int j = 0; j < len; j ++ , w = 1LL * w * w1 % P)
                {
                    int x = a[i + j], y = 1LL * w * a[i + j + len] % P;
                    a[i + j] = (x + y) % P;
                    a[i + j + len] = (x - y + P) % P;
                }
            }
        }
    }

public:
    vector<int> mul(const vector<int> &A, const vector<int> &B)
    {
        int n = A.size(), m = B.size();
        init(n + m - 1);

        vector<int> a(tot), b(tot);
        for (int i = 0; i < n; i ++ ) a[i] = (A[i] % P + P) % P;
        for (int i = 0; i < m; i ++ ) b[i] = (B[i] % P + P) % P;

        ntt(a, 1);
        ntt(b, 1);
        for (int i = 0; i < tot; i ++ )
            a[i] = 1LL * a[i] * b[i] % P;
        ntt(a, -1);

        int inv_tot = power(tot, P - 2);
        vector<int> ans(n + m - 1);
        for (int i = 0; i < ans.size(); i ++ )
            ans[i] = 1LL * a[i] * inv_tot % P;
        return ans;
    }
};