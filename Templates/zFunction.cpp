std::vector<int> zFunction(const std::string &s) {
    int n = s.size();
    std::vector<int> z(n);
    for (int i = 1, j = 1; i < n; i++) {
        z[i] = std::max(std::min(z[i - j], j + z[j] - i), 0);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > j + z[j]) {
            j = i;
        }
    }
    return z;
}
