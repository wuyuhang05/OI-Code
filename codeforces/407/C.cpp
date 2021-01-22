#include <bits/stdc++.h>

#define fi first
#define se second
#define DB double
#define U unsigned
#define P std::pair
#define LL long long
#define LD long double
#define pb emplace_back
#define MP std::make_pair
#define SZ(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3e5 + 5;
const int ha = 1e9 + 7;

int n,m,a[MAXN];
int fac[MAXN],inv[MAXN];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline int C(int n,int m){
    return n < 0 || m < 0 || n < m ? 0 : 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

inline void add(int &x,int y){
    x += y-ha;x += x>>31&ha;
}

std::vector<P<int,int> > G[101];
int ans[MAXN],tag[MAXN];

int main(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,m){
        int l,r,k;scanf("%d%d%d",&l,&r,&k);
        G[k].pb(l,r);
    }
    ROF(k,100,0){
        for(auto x:G[k]) add(ans[x.fi],1);
        FOR(i,1,n) tag[i] = 0;
        FOR(kk,k,100){
            for(auto x:G[kk]){
                add(tag[x.se+1],ha-C(x.se-x.fi+kk-k,kk-k));
            }
        }
        FOR(i,1,n) add(tag[i],tag[i-1]);
        FOR(i,1,n) add(ans[i],ans[i-1]);
        FOR(i,1,n) add(ans[i],tag[i]);
    }
    FOR(i,1,n) add(ans[i],a[i]);
    FOR(i,1,n) printf("%d%c",ans[i]," \n"[i==n]);
    return 0;
}
