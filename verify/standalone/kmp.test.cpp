// competitive-verifier: STANDALONE

#include "../../library/string/kmp.hpp"

#include <random>

#define CHECK(x)                                                          \
    do {                                                                  \
        if (!(x)) {                                                       \
            cerr << "FAILED: " #x << " (line " << __LINE__ << ")" << endl; \
            return 1;                                                     \
        }                                                                 \
    } while (0)

int main() {
    CHECK(kmp_search("abc", "").empty());
    mt19937_64 rng(20261122);
    for (int tc = 0; tc < 500; ++tc) {
        int n = (int)(rng() % 20);
        int m = 1 + (int)(rng() % 6);
        string text(n, 'a'), pat(m, 'a');
        for (char& c : text) c = char('a' + rng() % 3);
        for (char& c : pat) c = char('a' + rng() % 3);

        vector<int> want;
        for (int i = 0; i + m <= n; ++i) {
            bool ok = true;
            for (int j = 0; j < m; ++j)
                if (text[i + j] != pat[j]) ok = false;
            if (ok) want.push_back(i);
        }
        CHECK(kmp_search(text, pat) == want);

        auto pi = prefix_function(pat);
        for (int i = 0; i < m; ++i) {
            int w = 0;
            for (int len = i; len >= 1; --len) {
                bool ok = true;
                for (int j = 0; j < len; ++j)
                    if (pat[j] != pat[i - len + 1 + j]) ok = false;
                if (ok) {
                    w = len;
                    break;
                }
            }
            CHECK(pi[i] == w);
        }
    }
    cout << "OK" << endl;
    return 0;
}
