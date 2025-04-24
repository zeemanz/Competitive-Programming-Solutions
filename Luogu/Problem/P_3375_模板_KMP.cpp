#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

std::vector<int> prefixFunction(const std::string &s) {
    std::vector<int> pi(s.size());
    for (int i = 1, j = 0; i < s.size(); i++) {
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        pi[i] = j += s[i] == s[j];
    }
    return pi;
}

std::vector<int> match(const std::string &s, const std::string &t) {
    auto pi = prefixFunction(t);
    std::vector<int> ans;
    for (int i = 0, j = 0; i < s.size(); i++) {
        while (j > 0 && s[i] != t[j]) {
            j = pi[j - 1];
        }
        j += s[i] == t[j];
        if (j == t.size()) {
            ans.push_back(i - j + 1);
            j = pi[j - 1];
        }
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, t;
    std::cin >> s >> t;

    auto a = match(s, t);
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] + 1 << "\n";
    }

    auto b = prefixFunction(t);
    for (int i = 0; i < b.size(); i++) {
        std::cout << b[i] << " \n"[i == b.size() - 1];
    }

    return 0;
}
