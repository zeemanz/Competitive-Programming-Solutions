struct SuffixArray {
    int n;
    std::vector<int> suff, rnk, hgt;
    SuffixArray() {}
    SuffixArray(const std::string &s) {
        init(s);
    }
    void init(const std::string &s) {
        init(std::vector<int>(s.begin(), s.end()));
    }
    SuffixArray(const std::vector<int> &a) {
        auto v = a;
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        std::vector<int> b(a.size());
        for (int i = 0; i < a.size(); i++) {
            b[i] = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin();
        }
        init(b);
    }
    void init(const std::vector<int> &a) {
        n = a.size();
        suff.assign(n, -1);
        rnk.assign(2 * n, -1);
        for (int i = 0; i < n; i++) {
            rnk[i] = a[i];
        }
        int V = *std::max_element(a.begin(), a.end()) + 1;
        std::vector<int> sum, srnk(n);
        std::iota(srnk.begin(), srnk.end(), 0);
        auto sort = [&]() {
            sum.assign(V, 0);
            for (int i = 0; i < n; i++) {
                sum[rnk[i]]++;
            }
            for (int i = 0; i + 1 < V; i++) {
                sum[i + 1] += sum[i];
            }
            for (int i = n - 1; i >= 0; i--) {
                suff[--sum[rnk[srnk[i]]]] = srnk[i];
            }
        };
        sort();
        std::vector<int> tmp;
        for (int k = 1; k <= n; k *= 2) {
            int cur = 0;
            for (int i = n - k; i < n; i++) {
                srnk[cur++] = i;
            }
            for (int i = 0; i < n; i++) {
                if (suff[i] >= k) {
                    srnk[cur++] = suff[i] - k;
                }
            }
            sort();
            V = 1;
            tmp = rnk;
            rnk[suff[0]] = 0;
            for (int i = 1; i < n; i++) {
                if (tmp[suff[i]] != tmp[suff[i - 1]] || tmp[suff[i] + k] != tmp[suff[i - 1] + k]) {
                    V++;
                }
                rnk[suff[i]] = V - 1;
            }
            if (V == n) {
                break;
            }
        }
        hgt.assign(n, 0);
        for (int i = 0, l = 0; i < n; i++) {
            if (rnk[i] == 0) {
                continue;
            }
            if (l > 0) {
                l--;
            }
            int j = suff[rnk[i] - 1];
            while (i + l < n && j + l < n && a[i + l] == a[j + l]) {
                l++;
            }
            hgt[rnk[i] - 1] = l;
        }
    }
    int suffix(int i) {
        return suff[i];
    }
    int rank(int i) {
        return rnk[i];
    }
    int height(int i) {
        return hgt[i];
    }
    int size() {
        return n;
    }
} sa;
