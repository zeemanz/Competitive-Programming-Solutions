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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> v(n * n);
    for (auto &v : v) {
        std::cin >> v;
    }

    std::map<int, int> c;
    for (auto v : v) {
        c[v]++;
    }

    std::vector<int> a;
    ErasableHeap<int, std::greater<>> s(v);
    while (!s.empty() && a.size() < n) {
        auto x = s.top();
        s.pop();
        c[x]--;
        for (auto a : a) {
            auto l = std::lcm(a, x);
            if (!c.contains(l) || c[l] < 2) {
                std::cout << "-1\n";
                return 0;
            }
            c[l] -= 2;
            s.erase(l);
            s.erase(l);
        }
        a.push_back(x);
    }

    if (a.size() != n || !s.empty()) {
        std::cout << "-1\n";
    } else {
        for (auto a : a) {
            std::cout << a << " ";
        }
    }

    return 0;
}
