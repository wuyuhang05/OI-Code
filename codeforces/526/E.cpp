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

const int MAXN = 1e6 + 5;
int n,q,a[MAXN];
int f[MAXN],sf[MAXN],g[MAXN],sg[MAXN];

int main(){
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%d",a+i);
    while(q--){
        LL b;scanf("%lld",&b);
        FOR(i,0,n+3) sf[i] = sg[i] = f[i] = g[i] = 0;
        // f[i]: i->1
        // g[i]: i->n
        int j = 1;LL sm = 0;
        FOR(i,1,n){
            sm += a[i];
            while(sm > b) sm -= a[j++];
            if(j == 1) f[i] = 1,sf[i] = sm;
            else sf[i] = sf[j-1],f[i] = f[j-1]+1;
        }
        j = n;sm = 0;
        ROF(i,n,1){
            sm += a[i];
            while(sm > b) sm -= a[j--];
            if(j == n) g[i] = 1,sg[i] = sm;
            else sg[i] = sg[j+1],g[i] = g[j+1]+1;
        }
        int ans = std::min(f[n],g[1]);
        FOR(i,1,n-1){
            ans = std::min(ans,f[i]+g[i+1]-(sf[i]+sg[i+1]<=b));
        }
        printf("%d\n",ans);
    }
    return 0;
}
