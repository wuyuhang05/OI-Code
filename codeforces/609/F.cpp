#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define SZ(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;

int n,m;

struct Node{
    int x;LL t;int id;
}a[MAXN];

LL mx[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void update(int x,int l,int r,int p,LL d){
    if(l == r){
        mx[x] = d;return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) update(lc,l,mid,p,d);
    else update(rc,mid+1,r,p,d);
    mx[x] = std::max(mx[lc],mx[rc]);
}

inline LL query(int x,int l,int r,LL k){//  >= k;
    if(mx[x] < k) return -1;
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(mx[lc] >= k) return query(lc,l,mid,k);
    return query(rc,mid+1,r,k);
}

std::multiset<P> S;
int cnt[MAXN];LL ans[MAXN];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d%lld",&a[i].x,&a[i].t),a[i].id = i;
    std::sort(a+1,a+n+1,[&](const Node &a,const Node &b){
              return a.x < b.x;
              });
    FOR(i,1,n) update(1,1,n,i,a[i].x+a[i].t);
    FOR(i,1,m){
        int p,b;scanf("%d%d",&p,&b);
        int t = query(1,1,n,p);
        if(t == -1 || a[t].x > p){
            S.insert(MP(p,b));
            continue;
        }
        a[t].t += b;++cnt[a[t].id];
        while(!S.empty()){
            auto p = S.lower_bound(MP(a[t].x,-1e9));
            if(p == S.end()) break;
            if(p->fi <= a[t].t+a[t].x){
                a[t].t += p->se;
                ++cnt[a[t].id];
                S.erase(p);
            }
            else break;
        }
        update(1,1,n,t,a[t].x+a[t].t);
    }
    FOR(i,1,n) ans[a[i].id] = a[i].t;
    FOR(i,1,n) printf("%d %lld\n",cnt[i],ans[i]);
    return 0;
}
