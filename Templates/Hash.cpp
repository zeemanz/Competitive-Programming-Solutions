struct Hash {
    static constexpr u64 B = 251, P = 13681028875439;
    using H = Mod64<P>;
    inline static int m = 0;
    inline static std::vector<H> pow{1};
    int n;
    std::vector<H> hash, rhash;
    Hash(const std::string &s = {}) {
        init(s);
    }
    void init(const std::string &s) {
        n = s.size();
        if (m < n) {
            pow.resize(2 * n + 1);
            for (int i = m; i < 2 * n; i++) {
                pow[i + 1] = pow[i] * B;
            }
            m = 2 * n;
        }
        hash.assign(n + 1, 0);
        rhash.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            hash[i + 1] = hash[i] * B + s[i];
        }
        for (int i = n - 1; i >= 0; i--) {
            rhash[i] = rhash[i + 1] * B + s[i];
        }
    }
    H get(int l, int r) {
        return hash[r] - hash[l] * pow[r - l];
    }
    H rget(int l, int r) {
        return rhash[l] - rhash[r] * pow[r - l];
    }
    int lcp(int i, int j) {
        int lo = 0, hi = n - std::max(i, j);
        while (lo < hi) {
            int x = (lo + hi + 1) / 2;
            if (get(i, i + x) == get(j, j + x)) {
                lo = x;
            } else {
                hi = x - 1;
            }
        }
        return lo;
    }
    int lcs(int i, int j) {
        int lo = 0, hi = std::min(i, j);
        while (lo < hi) {
            int x = (lo + hi + 1) / 2;
            if (get(i - x, i) == get(j - x, j)) {
                lo = x;
            } else {
                hi = x - 1;
            }
        }
        return lo;
    }
};
