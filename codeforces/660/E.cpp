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

int n,m;
int f[MAXN];

int main(){
    scanf("%d%d",&n,&m);
    f[0] = 1;f[1] = 3*m-1;
    FOR(i,2,n){
        f[i] = 1ll*(3*m-1)*f[i-1]%ha;
        (f[i] += ha-1ll*m*(2*m-1)%ha*f[i-2]%ha) %= ha;
    }
    int ans = f[n];
    (ans += ha-qpow(m,n)) %= ha;
    ans = 1ll*ans*m%ha*qpow(2*m-1)%ha;
    (ans += qpow(m,n)) %= ha;
    printf("%d\n",ans);
    return 0;
}
