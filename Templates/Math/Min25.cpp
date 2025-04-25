template <class T> struct Min25 {
    using Func = T (*)(int, int, i64);
    int pcnt;
    i64 n, sqrt;
    std::vector<i64> nums;
    std::vector<T> coef;
    std::vector<std::vector<T>> sum, ini, val;
    Min25() : n{0}, sqrt{0} {}
    Min25(i64 n, const std::vector<T> &coef, const std::vector<Func> &func, u32 lim = -1) {
        init(n, coef, func, lim);
    }
    void init(i64 m, const std::vector<T> &coef, const std::vector<Func> &func, u32 lim = -1) {
        n = m;
        sqrt = std::sqrt(n);
        pcnt = sieve.count(sqrt);
        nums.clear();
        for (i64 i = 1; i <= n; i = n / (n / i) + 1) {
            nums.emplace_back(n / i);
        }
        nums.emplace_back(0);
        std::reverse(nums.begin(), nums.end());
        sum.assign(func.size(), std::vector<T>(pcnt + 1));
        ini.assign(func.size(), std::vector<T>(nums.size()));
        for (int i = 0; i < func.size(); i++) {
            auto f = func[i];
            for (int j = 0; j < pcnt; j++) {
                auto b = sieve.prime(j);
                sum[i][j + 1] = sum[i][j] + f(b, 1, b);
            }
            auto c = f(0, 0, 1);
            for (int j = 1; j < nums.size(); j++) {
                ini[i][j] = f(0, 0, nums[j]) - c;
            }
        }
        for (int i = 0; i < func.size(); i++) {
            auto f = func[i];
            for (int j = 0; j < pcnt; j++) {
                auto b = sieve.prime(j);
                for (int k = nums.size() - 1; k > 0; k--) {
                    if (1LL * b * b > nums[k]) {
                        break;
                    }
                    ini[i][k] -= f(b, 1, b) * (ini[i][rank(nums[k] / b)] - sum[i][j]);
                }
            }
        }
        val.assign(pcnt, {});
        for (int i = 0; i < pcnt; i++) {
            auto b = sieve.prime(i);
            val[i].reserve(std::floor(std::log(n) / std::log(b)) + 1);
            val[i].emplace_back(0);
            for (i64 e = 1, p = b, c = 0; e <= lim && p <= n; e++, p *= b, c = 1) {
                val[i].emplace_back(0);
                for (int j = 0; j < coef.size(); j++) {
                    val[i][e] += coef[j] * func[j](b, e, p);
                }
            }
        }
        this->coef = coef;
    }
    int rank(i64 m) {
        if (m <= sqrt) {
            return m;
        } else {
            return nums.size() - n / m;
        }
    }
    T operator[](i64 m) {
        T res = 0;
        for (int i = 0; i < coef.size(); i++) {
            res += coef[i] * ini[i][rank(m)];
        }
        return res;
    }
    T dfs(i64 m, int i) {
        if (sieve.prime(i) > m) {
            return 0;
        }
        T res = 0;
        for (int j = 0; j < coef.size(); j++) {
            res += coef[j] * (ini[j][rank(m)] - sum[j][i]);
        }
        for (; i < pcnt; i++) {
            auto b = sieve.prime(i);
            if (1LL * b * b > m) {
                break;
            }
            for (i64 e = 1, p = b, c = 0; e < val[i].size() && p <= m; e++, p *= b, c = 1) {
                res += val[i][e] * (dfs(m / p, i + 1) + c);
            }
        }
        return res;
    }
    T operator()(i64 m) {
        return dfs(m, 0);
    }
};
