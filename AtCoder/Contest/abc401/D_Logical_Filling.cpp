#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, K;
    std::cin >> N >> K;

    std::string S;
    std::cin >> S;

    for (int i = 0; i < N; i++) {
        if (S[i] == 'o') {
            if (i > 0) {
                S[i - 1] = '.';
            }
            if (i + 1 < N) {
                S[i + 1] = '.';
            }
        }
    }

    int x = K - std::ranges::count(S, 'o'), y = 0;
    for (int i = 0, j = 0; i <= N; i++) {
        if (i == N || S[i] != '?') {
            y += (j + 1) / 2;
            j = 0;
        } else {
            j++;
        }
    }

    if (x == 0) {
        for (auto &S : S) {
            if (S == '?') {
                S = '.';
            }
        }
    } else if (x == y) {
        for (int i = 0, j = 0; i <= N; i++) {
            if (i == N || S[i] != '?') {
                if (j % 2 == 1) {
                    for (int k = i - j; k < i; k += 2) {
                        S[k] = 'o';
                        if (k + 1 < N) {
                            S[k + 1] = '.';
                        }
                    }
                }
                j = 0;
            } else {
                j++;
            }
        }
    }
    std::cout << S << "\n";

    return 0;
}
