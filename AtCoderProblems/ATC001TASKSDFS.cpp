//デバッグ
#ifdef LOCAL_DBG
#define _GLIBCXX_DEBUG
#endif
// #pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
template <typename K, typename V>
using umap = unordered_map<K, V>;
template <typename T>
using pque = priority_queue<T>;
template <typename T>
using revpque = priority_queue<T, vector<T>, greater<T>>;
using ll = long long;
using ld = long double;
using str = string;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vi = vector<int>;
using vs = vector<str>;
using mapll = map<ll, ll>;
using umapll = umap<ll, ll>;
#define endl "\n";
#define _rep(i, n) _repi(i, 0, n)
#define _repi(i, l, r) for (ll i = ll(l); i < ll(r); i++)
#define _get_rep(_1, _2, _3, NAME, ...) NAME
#define rep(...) _get_rep(__VA_ARGS__, _repi, _rep)(__VA_ARGS__)
#define _rrep(i, n) for (ll i = ll(n) - 1; 0 <= i; i--)
#define _rrepi(i, l, r) for (ll i = ll(r) - 1; l <= i; i--)
#define _get_rrep(_1, _2, _3, NAME, ...) NAME
#define rrep(...) _get_rrep(__VA_ARGS__, _rrepi, _rrep)(__VA_ARGS__)
#define each(...) for (auto __VA_ARGS__)
#define all(x) x.begin(), x.end()
#define mkpair make_pair
#define is_in(x, l, r) ((l) <= (x) && (x) < (r))
#define in(t, ...) \
    t __VA_ARGS__; \
    isin(cin, __VA_ARGS__)
#define inv(t, v, n) \
    vector<t> v(n);  \
    isin(cin, v)
#define inv2(t, v, h, w)                  \
    vector<vector<t>> v(h, vector<t>(w)); \
    isin(cin, v)
#define invv(t, va, vb, n)  \
    vector<t> va(n), vb(n); \
    rep(i, n) { isin(cin, va[i], vb[i]); }
#define invvv(t, va, vb, vc, n)    \
    vector<t> va(n), vb(n), vc(n); \
    rep(i, n) { isin(cin, va[i], vb[i], vc[i]); }
#define inln(s) \
    str s;      \
    getline(cin, s)
#define print(...) osout(cout, __VA_ARGS__)
#ifdef LOCAL_DBG
#define dbg(...) osout(cerr, __VA_ARGS__)
#else
#define dbg(...)
#endif
const ll inf = numeric_limits<ll>::max() / 2;
template <typename T>
bool chmax(T &x, const T &y) {
    if (x < y) {
        x = y;
        return 1;
    }
    return 0;
}
template <typename T>
bool chmin(T &x, const T &y) {
    if (x > y) {
        x = y;
        return 1;
    }
    return 0;
}
template <typename T>
void sort(vector<T> &v) {
    sort(all(v));
}
template <typename T>
void rsort(vector<T> &v) {
    sort(all(v), greater<T>());
}
template <typename T>
void dec(vector<T> &v) {
    rep(i, v.size()) v[i]--;
}
template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
    rep(i, v.size()) { cin >> v[i]; }
    return is;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, pair<T1, T2> p) {
    if (&os == &cout) {
        os << p.first << ' ' << p.second;
    }
    if (&os == &cerr) {
        os << '(' << p.first << ", " << p.second << ')';
    }
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, vector<T> v) {
    if (&os == &cout) {
        rep(i, v.size() - 1) { os << v[i] << ' '; }
        os << v[v.size() - 1];
    }
    if (&os == &cerr) {
        os << '[';
        rep(i, v.size() - 1) { os << v[i] << ", "; }
        os << v[v.size() - 1] << ']';
    }
    return os;
}
void isin(__attribute__((unused)) istream &_) {}
template <class S, class... T>
void isin(istream &is, S &s, T &...t) {
    is >> s;
    isin(is, t...);
}
void osout(ostream &os) { os << '\n'; }
template <class S, class... T>
void osout(ostream &os, S s, T... t) {
    os << s;
    if (sizeof...(t)) os << ' ';
    osout(os, t...);
}
namespace config {
int precision;
void update();
}  // namespace config
void solve();
int main() {
    config::update();
    cin.tie(0);
    ios::sync_with_stdio(false);
    if (config::precision) {
        cout << fixed << setprecision(15);
        cerr << fixed << setprecision(15);
    }
    solve();
#ifdef LOCAL_DBG
    dbg("time:", 1000 * clock() / CLOCKS_PER_SEC, "[ms]");
#endif
}
void config::update() { precision = 0; }

// 四方向への移動ベクトル
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

// 入力
int H, W;
vs field;

// 探索
bool seen[510][510];  // seen[h][w] := マス (h, w) が検知済みかどうか
void dfs(int h, int w) {
    seen[h][w] = true;

    // 四方向を探索
    for (int dir = 0; dir < 4; ++dir) {
        int nh = h + dx[dir];
        int nw = w + dy[dir];

        // 場外アウトしたり、移動先が壁の場合はスルー
        if (nh < 0 || nh >= H || nw < 0 || nw >= W) continue;
        if (field[nh][nw] == '#') continue;

        // 移動先が探索済みの場合
        if (seen[nh][nw]) continue;

        // 再帰的に探索
        dfs(nh, nw);
    }
}

void solve() {
    // 入力受け取り
    cin >> H >> W;
    field.resize(H);
    for (int h = 0; h < H; ++h) cin >> field[h];

    // s と g のマスを特定する
    int sh, sw, gh, gw;
    for (int h = 0; h < H; ++h) {
        for (int w = 0; w < W; ++w) {
            if (field[h][w] == 's') sh = h, sw = w;
            if (field[h][w] == 'g') gh = h, gw = w;
        }
    }

    // 探索開始
    memset(seen, 0, sizeof(seen));  // seen 配列全体を false に初期化
    dfs(sh, sw);

    // 結果
    if (seen[gh][gw]) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}