#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

struct BitSet : std::vector<u64> {
    using vector::vector;
    BitSet(const std::string &s) {
        init(s);
    }
    void init(const std::string &s) {
        assign((s.size() + 63) / 64, 0ULL);
        for (int i = 0; i < s.size(); i++) {
            (*this)[i / 64] |= u64(s[s.size() - 1 - i] - '0') << (i % 64);
        }
    }
    bool operator()(int i) const {
        return (*this)[i / 64] >> (i % 64) & 1ULL;
    }
    BitSet &operator^=(const BitSet &rhs) {
        for (int i = 0; i < size(); i++) {
            (*this)[i] ^= rhs[i];
        }
        return *this;
    }
    friend BitSet operator^(BitSet lhs, const BitSet &rhs) {
        return lhs ^= rhs;
    }
};

bool operator==(const std::vector<BitSet> &lhs, const std::vector<BitSet> &rhs) {
    auto contains = [&](const std::vector<BitSet> &s, BitSet x) {
        for (int i = 0; i < s.size(); i++) {
            if (x(i)) {
                if (s[i].empty()) {
                    return false;
                }
                x ^= s[i];
            }
        }
        return true;
    };
    for (auto x : rhs) {
        if (!x.empty() && !contains(lhs, x)) {
            return false;
        }
    }
    return true;
}

void solve() {
    int n;
    std::cin >> n;
    const int m = n >> __builtin_ctz(n);

    std::string s, t;
    std::cin >> s >> t;

    auto work = [&](const std::string &s) {
        std::vector<BitSet> b(m);
        auto insert = [&](const std::string &s) {
            BitSet x(s);
            for (int i = 0; i < m; i++) {
                if (x(i)) {
                    if (b[i].empty()) {
                        b[i] = std::move(x);
                        return;
                    }
                    x ^= b[i];
                }
            }
        };
        for (int i = 0; i < n; i += m) {
            insert(s.substr(i, m));
        }
        return b;
    };

    if (work(s) == work(t)) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
