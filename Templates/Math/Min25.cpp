template <class T> struct Min25 {
    inline static Sieve sieve = Sieve(100000);
    using Func = T (*)(int, int, i64);
    i64 n, sqrtn, cnt;
    std::vector<i64> num;
    std::vector<T> coef;
    std::vector<std::vector<T>> sum, ini, val;
    Min25() : n{0}, sqrtn{0} {}
    Min25(i64 n, const std::initializer_list<T> &coef, const std::initializer_list<Func> &func) {
        init(n, coef, func);
    }
    void init(i64 m, const std::initializer_list<T> &coef, const std::initializer_list<Func> &func) {
        n = m;
        sqrtn = std::sqrt(n);
        cnt = sieve.count(sqrtn);
        num.clear();
        for (i64 i = 1; i <= n; i = n / (n / i) + 1) {
            num.push_back(n / i);
        }
        this->coef = coef;
        sum.assign(func.size(), std::vector<T>(cnt + 1));
        ini.assign(func.size(), std::vector<T>(num.size()));
        for (int i = 0; auto f : func) {
            for (int j = 0; j < cnt; j++) {
                auto b = sieve.prime(j);
                sum[i][j + 1] = sum[i][j] + f(b, 1, b);
            }
            auto c = f(0, 0, 1);
            for (int j = 0; j < num.size(); j++) {
                ini[i][j] = f(0, 0, num[j]) - c;
            }
            i++;
        }
        for (int i = 0; auto f : func) {
            for (int j = 0; j < cnt; j++) {
                auto b = sieve.prime(j);
                for (int k = 0; k < num.size(); k++) {
                    if (1LL * b * b > num[k]) {
                        break;
                    }
                    ini[i][k] -= f(b, 1, b) * (ini[i][rank(num[k] / b)] - sum[i][j]);
                }
            }
            i++;
        }
        val.assign(cnt, {});
        for (int i = 0; i < cnt; i++) {
            auto b = sieve.prime(i);
            val[i].assign(int(std::ceil(std::log(n) / std::log(b))) + 1, 0);
            for (i64 e = 1, p = b, c = 0; p <= n; e++, p *= b, c = 1) {
                for (int j = 0; auto f : func) {
                    val[i][e] += this->coef[j++] * f(b, e, p);
                }
            }
        }
    }
    int rank(i64 m) {
        if (m <= sqrtn) {
            return num.size() - m;
        } else {
            return n / m - 1;
        }
    }
    T dfs(i64 m, int i) {
        if (sieve.prime(i) > m) {
            return 0;
        }
        T res = 0;
        for (int j = 0; j < coef.size(); j++) {
            res += coef[j] * (ini[j][rank(m)] - sum[j][i]);
        }
        for (; i < cnt; i++) {
            auto b = sieve.prime(i);
            if (1LL * b * b > m) {
                break;
            }
            for (i64 e = 1, p = b, c = 0; p <= m; e++, p *= b, c = 1) {
                res += val[i][e] * (dfs(m / p, i + 1) + c);
            }
        }
        return res;
    }
    T operator()(i64 m) {
        return dfs(m, 0);
    }
};
