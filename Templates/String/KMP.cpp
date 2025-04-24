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
