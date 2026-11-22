// competitive-verifier: STANDALONE

#include "../../library/string/suffix_array.hpp"

#include <random>

#define CHECK(x)                                                          \
    do {                                                                  \
        if (!(x)) {                                                       \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                     \
        }                                                                 \
    } while (0)

template <typename Container>
vector<int> naive_sa(const Container& s) {
    int n = (int)s.size();
    vector<int> sa(n);
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [&](int a, int b) {
        while (a < n && b < n) {
            if (s[a] != s[b]) return s[a] < s[b];
            ++a;
            ++b;
        }
        return a == n;
    });
    return sa;
}

template <typename Container>
vector<int> naive_lcp(const Container& s, const vector<int>& sa) {
    int n = (int)s.size();
    vector<int> lcp(max(0, n - 1));
    for (int i = 0; i + 1 < n; ++i) {
        int a = sa[i], b = sa[i + 1];
        while (a + lcp[i] < n && b + lcp[i] < n &&
               s[a + lcp[i]] == s[b + lcp[i]])
            ++lcp[i];
    }
    return lcp;
}

int main() {
    mt19937_64 rng(20261122);
    for (int tc = 0; tc < 500; ++tc) {
        int n = (int)(rng() % 30);
        vector<int> a(n);
        for (int& x : a) x = (int)(rng() % 5) - 2;
        auto sa = suffix_array(a);
        CHECK(sa == naive_sa(a));
        CHECK(lcp_array(a, sa) == naive_lcp(a, sa));
    }
    for (int tc = 0; tc < 300; ++tc) {
        int n = (int)(rng() % 25);
        string s(n, 'a');
        for (char& c : s) c = char('a' + rng() % 3);
        auto sa = suffix_array(s);
        CHECK(sa == naive_sa(s));
        CHECK(lcp_array(s, sa) == naive_lcp(s, sa));
    }
    {
        vector<long long> a{3, -1, 4, -1, 5, -1000000000000000000LL};
        auto sa = suffix_array(a);
        CHECK(sa == naive_sa(a));
        CHECK(lcp_array(a, sa) == naive_lcp(a, sa));
    }
    {
        vector<int> empty;
        CHECK(suffix_array(empty).empty());
        CHECK(lcp_array(empty, {}).empty());
    }
    cout << "OK" << endl;
    return 0;
}
