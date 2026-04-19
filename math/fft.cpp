using CD = complex<double>;

class FFTPolyMul
{
private:
    static constexpr double PI = acos(-1.0);
    int tot = 1;
    vector<int> rev = {0};

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

    void fft(vector<CD> &a, int inv) const
    {
        for (int i = 0; i < tot; i ++ )
            if (i < rev[i])
                swap(a[i], a[rev[i]]);

        for (int len = 1; len < tot; len <<= 1)
        {
            CD w1(cos(PI / len), inv * sin(PI / len));
            for (int i = 0; i < tot; i += (len << 1))
            {
                CD wk(1, 0);
                for (int j = 0; j < len; j ++ , wk = wk * w1)
                {
                    CD x = a[i + j], y = wk * a[i + j + len];
                    a[i + j] = x + y;
                    a[i + j + len] = x - y;
                }
            }
        }
    }

public:
    vector<LL> mul(const vector<int> &A, const vector<int> &B)
    {
        int n = A.size(), m = B.size();
        init(n + m - 1);

        vector<CD> a(tot), b(tot);
        for (int i = 0; i < n; i ++ ) a[i] = CD(A[i], 0);        
        for (int i = 0; i < m; i ++ ) b[i] = CD(B[i], 0);

        fft(a, 1);
        fft(b, 1);
        for (int i = 0; i < tot; i ++ )
            a[i] = a[i] * b[i];
        fft(a, -1);

        vector<LL> ans(n + m - 1);
        for (int i = 0; i < ans.size(); i ++ )
            ans[i] = llround(a[i].real() / tot);
        return ans;
    }
};