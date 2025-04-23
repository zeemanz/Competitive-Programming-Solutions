#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class T, class Cmp = std::less<T>> struct ErasableHeap {
    std::priority_queue<T, std::vector<T>, Cmp> heap, trash;
    ErasableHeap() {}
    ErasableHeap(const std::vector<T> &data) : heap{data.begin(), data.end()} {}
    void push(const T &x) {
        heap.push(x);
    }
    void pop() {
        doErase();
        heap.pop();
    }
    const T &top() {
        doErase();
        return heap.top();
    }
    void erase(const T &x) {
        trash.push(x);
    }
    void doErase() {
        while (!heap.empty() && !trash.empty() && heap.top() == trash.top()) {
            heap.pop();
            trash.pop();
        }
    }
    bool empty() const {
        return heap.size() == trash.size();
    }
};

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<u32> a(n);
    for (auto &a : a) {
        std::cin >> a;
    }

    std::vector prev(k, std::vector(n, -1));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if (a[j] >> i & 1) {
                prev[i][j] = j;
            } else if (j > 0) {
                prev[i][j] = prev[i][j - 1];
            }
        }
    }

    std::vector<std::vector<u32>> add(n + 1), del(n + 1);
    auto work = [&](int l, int r) {
        if (l < 0 || l > r) {
            return;
        }
        u32 v = 0;
        for (int i = 0; i < k; i++) {
            u32 d;
            if (prev[i][r] < l) {
                d = (r - l) % 2;
            } else if (prev[i][r] == l) {
                d = (r - l + 1) % 2;
            } else {
                d = (r - prev[i][r]) % 2;
            }
            v |= d << i;
        }
        add[l].push_back(v);
        del[r + 1].push_back(v);
    };

    for (int r = 0; r < n; r++) {
        for (int i = 0; i < k; i++) {
            for (int d = -2; d <= 2; d++) {
                work(prev[i][r] + d, r);
            }
        }
        work(0, r);
        work(1, r);
    }

    ErasableHeap<u32> que;
    std::vector<u32> ans(n);
    for (int i = 0; i < n; i++) {
        for (auto v : del[i]) {
            que.erase(v);
        }
        for (auto v : add[i]) {
            que.push(v);
        }
        ans[i] = que.top();
    }

    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << " \n"[i == n - 1];
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
