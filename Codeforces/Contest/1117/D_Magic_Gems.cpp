#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <class T> constexpr T power(T a, u64 n) {
    T res{1};
    for (; n != 0; n /= 2, a *= a) {
        if (n % 2 == 1) {
            res *= a;
        }
    }
    return res;
}

template <u32 P> constexpr u32 mulMod(u32 a, u32 b) {
    return 1ULL * a * b % P;
}

template <u64 P> constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.0L * a * b / P - 0.5L) * P;
    return res % P;
}

template <class U, U P> struct ModBase {
    U x;
    constexpr ModBase() : x{0} {}
    template <class T> constexpr ModBase(T x) : x{norm(x % mod())} {}
    static constexpr U mod() {
        return P;
    }
    static constexpr U norm(U x) {
        if ((x >> (8 * sizeof(U) - 1) & 1) == 1) {
            x += mod();
        }
        if (x >= mod()) {
            x -= mod();
        }
        return x;
    }
    constexpr U val() const {
        return x;
    }
    constexpr ModBase operator-() const {
        return ModBase(mod() - x);
    }
    constexpr ModBase inv() const {
        return power(*this, mod() - 2);
    }
    constexpr ModBase &operator+=(const ModBase &rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr ModBase &operator-=(const ModBase &rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr ModBase &operator*=(const ModBase &rhs) & {
        x = mulMod<mod()>(x, rhs.x);
        return *this;
    }
    constexpr ModBase &operator/=(const ModBase &rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr ModBase operator+(ModBase lhs, const ModBase &rhs) {
        return lhs += rhs;
    }
    friend constexpr ModBase operator-(ModBase lhs, const ModBase &rhs) {
        return lhs -= rhs;
    }
    friend constexpr ModBase operator*(ModBase lhs, const ModBase &rhs) {
        return lhs *= rhs;
    }
    friend constexpr ModBase operator/(ModBase lhs, const ModBase &rhs) {
        return lhs /= rhs;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const ModBase &rhs) {
        return os << rhs.val();
    }
    friend constexpr bool operator==(const ModBase &lhs, const ModBase &rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(const ModBase &lhs, const ModBase &rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(const ModBase &lhs, const ModBase &rhs) {
        return lhs.val() < rhs.val();
    }
};

template <u32 P> using Mod32 = ModBase<u32, P>;
template <u64 P> using Mod64 = ModBase<u64, P>;

constexpr u32 P = 1000000007;
using Z = Mod32<P>;

template <int V> constexpr Z inv = Z(V).inv();

template <class T, int N> struct Matrix : std::array<std::array<T, N>, N> {
    using std::array<std::array<T, N>, N>::array;
    Matrix(T x) : Matrix() {
        eye(x);
    }
    void eye(T x) {
        for (int i = 0; i < N; i++) {
            (*this)[i][i] = x;
        }
    }
    Matrix &operator+=(const Matrix &rhs) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                (*this)[i][j] += rhs[i][j];
            }
        }
        return *this;
    }
    Matrix &operator*=(const Matrix &rhs) {
        Matrix res;
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                for (int j = 0; j < N; j++) {
                    res[i][k] += (*this)[i][j] * rhs[j][k];
                }
            }
        }
        return *this = res;
    }
    friend Matrix operator+(Matrix lhs, const Matrix &rhs) {
        return lhs += rhs;
    }
    friend Matrix operator*(Matrix lhs, const Matrix &rhs) {
        return lhs *= rhs;
    }
    friend std::ostream &operator<<(std::ostream &os, const Matrix &rhs) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                os << rhs[i][j] << " \n"[j == N - 1];
            }
        }
        return os;
    }
};

using Mat = Matrix<Z, 100>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 N;
    int M;
    std::cin >> N >> M;

    Mat F, G;
    F[0][M - 1] = 1;
    for (int i = 1; i < M; i++) {
        G[i][i - 1] = 1;
    }
    G[0][M - 1] = 1;
    G[M - 1][M - 1] = 1;

    F *= power(G, N);
    std::cout << F[0][M - 1] << "\n";

    return 0;
}
