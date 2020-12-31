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
const int ha = 1e9 + 7;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

int fac[MAXN],inv[MAXN];

inline int C(int n,int m){
    return n < 0 || m < 0 || n < m ? 0 : 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int main(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    int n,m;scanf("%d%d",&n,&m);
    int ans = qpow(m,n);
    FOR(i,1,n) (ans += 1ll*qpow(m,n-i+1)*qpow(2*m-1,i-1)%ha) %= ha;
    /*
    FOR(i,1,n){
        FOR(j,i,n){
            int c = 1ll*C(j-1,i-1)%ha*qpow(m-1,j-i)%ha*qpow(m,n-j)%ha;
            c = 1ll*c*qpow(m,i)%ha;
            (ans += c) %= ha;
        }
    }*/
    printf("%d\n",ans);
    return 0;
}
