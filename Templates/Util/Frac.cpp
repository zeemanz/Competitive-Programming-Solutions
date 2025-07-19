struct Frac {
    i64 num, den;
    constexpr Frac(i64 x = 0) : Frac(x, 1) {}
    constexpr Frac(i64 num, i64 den) : num{num}, den{den} {
        norm();
    }
    constexpr void norm() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }
    constexpr Frac operator-() const {
        return Frac(-num, den);
    }
    constexpr Frac &operator+=(const Frac &rhs) {
        num = num * rhs.den + rhs.num * den;
        den *= rhs.den;
        norm();
        return *this;
    }
    constexpr Frac &operator-=(const Frac &rhs) {
        return *this += -rhs;
    }
    constexpr Frac &operator*=(const Frac &rhs) {
        num *= rhs.num;
        den *= rhs.den;
        norm();
        return *this;
    }
    constexpr Frac &operator/=(const Frac &rhs) {
        num *= rhs.den;
        den *= rhs.num;
        norm();
        return *this;
    }
    friend constexpr Frac operator+(const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Frac operator-(const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Frac operator*(const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Frac operator/(const Frac &lhs, const Frac &rhs) {
        Frac res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr bool operator<(const Frac &lhs, const Frac &rhs) {
        return static_cast<__int128>(lhs.num) * rhs.den < static_cast<__int128>(rhs.num) * lhs.den;
    }
    friend constexpr bool operator>(const Frac &lhs, const Frac &rhs) {
        return static_cast<__int128>(lhs.num) * rhs.den > static_cast<__int128>(rhs.num) * lhs.den;
    }
    friend std::ostream &operator<<(std::ostream &os, const Frac &rhs) {
        return os << rhs.num << "/" << rhs.den;
    }
};
