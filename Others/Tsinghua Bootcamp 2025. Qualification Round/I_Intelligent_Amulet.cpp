#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r) {
    return std::uniform_int_distribution<int>(l, r)(rng);
}

constexpr int V = 2000000;

std::vector<int> primes, minp, pi;

void sieve(int n) {
    primes.clear();
    minp.assign(n + 1, 0);
    pi.assign(n + 2, 0);
    for (int i = 2; i <= n; i++) {
        pi[i + 1] = pi[i];
        if (minp[i] == 0) {
            pi[i + 1]++;
            minp[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (1LL * i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}

constexpr int magic[]{98, 65, 27, 84, 4088, 2696, 3976, 4221, 1337, 2774, 2459};
std::map<std::array<int, 11>, int> map;

int range(int l, int r) {
    return pi[r] - pi[l];
}

void init() {
    for (auto p : primes) {
        if (p > 1000114) {
            break;
        }
        int s = 0;
        std::array<int, 11> cur{};
        for (int i = 0; i < 11; i++) {
            s += magic[i];
            cur[i] = range(p, p + s);
        }
        if (map.contains(cur)) {
            std::cout << "error\n";
            exit(1);
        }
        map[cur] = p + s - 1;
    }
}

void solve() {
    auto ask = [&](int dl, int dr) {
        std::cout << "? " << dl << " " << dr << std::endl;
        int res;
        std::cin >> res;
        return res;
    };

    auto ans = [&](int l, int r) {
        std::cout << "! " << l << " " << r << std::endl;
        int res;
        std::cin >> res;
        assert(res == 1);
    };

    int ori = ask(0, 0), del = 0;
    for (int i = 6; i >= 0; i--) {
        int cur = ask(0, del + (1 << i));
        del = 0;
        if (cur != ori) {
            del -= 1 << i;
        }
    }

    std::array<int, 11> cur{};
    for (int i = 0; i < 11; i++) {
        cur[i] = ask(0, del + magic[i]) - ori;
        del = 0;
    }

    int q = map[cur];

    ori += cur[10];
    del = 0;
    for (int i = 6; i >= 0; i--) {
        int cur = ask(del + (1 << i), 0);
        del = 0;
        if (cur != ori) {
            del -= 1 << i;
        }
    }

    int lo = 0, hi = primes.size();
    while (hi - lo > 1) {
        int m = (lo + hi) / 2;
        if (primes[m] <= q && range(primes[m], q + 1) >= ori) {
            lo = m;
        } else {
            hi = m;
        }
    }
    int p = primes[lo] - del;

    ans(p, q);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    sieve(V);
    init();

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
