#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Inf 0x3f3f3f3f3f3f3f3f
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define REP(i, s, t) for (int i = (s); i <= (t); i ++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template <typename T> void chkmax(T &x, T y) { x = x > y ? x : y; }
template <typename T> void chkmin(T &x, T y) { x = x < y ? x : y; }
template <typename T> void read(T &x) {
    x = 0; bool w = 0; char ch = 0;
    for (; !isdigit(ch); ch = getchar()) w |= ch == '-';
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x *= w ? -1 : 1;
}
template <typename T> void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
template <typename T> void write(T x, char ch) {
    write(x); putchar(ch);
}
const int N = 3e5 + 5;
int n, m;
ll a[N], dif[N];
namespace segMentTree {
    #define lc (nod << 1)
    #define rc (nod << 1 | 1)
    struct node {
        ll mx, L, R;
    } tr[N << 2];
    ll chk(ll x) {
        return x == 0 ? 0 : (x > 0 ? 1 : -1);
    }
    void pushUp(int nod, int l, int r) {
        tr[nod].mx = max(tr[lc].mx, tr[rc].mx);
        tr[nod].L = tr[lc].L; 
        tr[nod].R = tr[rc].R;
        int mid = (l + r) >> 1;
        if (dif[mid] && dif[mid + 1] && chk(dif[mid]) >= chk(dif[mid + 1])) {
            chkmax(tr[nod].mx, tr[lc].R + tr[rc].L);
            if (tr[lc].L == mid - l + 1) tr[nod].L = tr[lc].L + tr[rc].L;
            if (tr[rc].R == r - mid) tr[nod].R = tr[lc].R + tr[rc].R; 
        }
    }
    void build(int nod, int l, int r) {
        if (l == r) {
            tr[nod].mx = tr[nod].L = tr[nod].R = (dif[l] != 0);
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushUp(nod, l, r);
    }
    void modify(int nod, int l, int r, int pos) {
        if (l == r) {
            tr[nod].mx = tr[nod].L = tr[nod].R = (dif[pos] != 0);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) modify(lc, l, mid, pos);
        else modify(rc, mid + 1, r, pos);
        pushUp(nod, l, r);
    }
}
int main() {
    read(n); 
    for (int i = 1; i <= n; i ++) read(a[i]);
    for (int i = 1; i < n; i ++) dif[i] = a[i + 1] - a[i];
    read(m);
    if (n == 1) {
        while (m --) printf("1\n");
        return 0;
    }
    segMentTree::build(1, 1, n - 1);
    while (m --) {
        int l, r; ll x; read(l); read(r); read(x);
        if (l != 1) dif[l - 1] += x, segMentTree::modify(1, 1, n - 1, l - 1);
        if (r != n) dif[r] -= x, segMentTree::modify(1, 1, n - 1, r);
        write(segMentTree::tr[1].mx + 1, '\n');
    }
    return 0;
}