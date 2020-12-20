#include <bits/stdc++.h>

#define fi first
#define se second
#define DB double
#define U unsigned
#define P std::pair
#define LL long long
#define LD long double
#define pb push_back
#define MP std::make_pair
#define SZ(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 50000+5;
int sm[1000005];
int n,m,a[MAXN];
int t[MAXN];
int l[MAXN],r[MAXN],ans[MAXN];

int main(){
    FOR(i,1,1000000) sm[i] = sm[i-1]^i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,m) scanf("%d%d",l+i,r+i);
    FOR(i,1,n){
        t[i-1] = -1e9;
        FOR(j,i,n) t[j] = std::max(t[j-1],sm[std::max(a[i],a[j])]^sm[std::min(a[i],a[j])-1]);
        FOR(j,1,m){
            if(l[j] <= i && r[j] >= i) ans[j] = std::max(ans[j],t[r[j]]);
        }
    }
    FOR(i,1,m) printf("%d\n",ans[i]);
    return 0;
}
