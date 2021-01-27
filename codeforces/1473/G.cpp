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

const int MAXN = 3e5+5;
const int ha = 998244353;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

int n,a[MAXN],b[MAXN];
int sz[MAXN];
int f[2][MAXN],now;
int fac[MAXN],inv[MAXN];

inline int C(int n,int m){
    return n < 0 || m < 0 || n < m ? 0 : 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

inline void add(int &x,int y){
    x += y-ha;x += x>>31&ha;
}

struct Poly{
    std::vector<int> x;
    inline int deg(){return SZ(x)-1;}
    inline void ext(int n){x.resize(n+1);}
    inline int& operator [] (const int &n){return x[n];}
};

int r[MAXN<<2],N;
int W[MAXN<<2];

inline void init(int n){
    N = 1;int len = 0;while(N <= n) N <<= 1,++len;
    FOR(i,0,N-1) r[i] = (r[i>>1]>>1)|((i&1)<<(len-1));
}

inline void NTT(Poly &A){
    A.ext(N-1);FOR(i,0,N-1) if(i < r[i]) std::swap(A[i],A[r[i]]);
    int *w = W;
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            for(int j = 0;j < mid;++j){
                int x = A[i+j],y = 1ll*w[j]*A[i+mid+j]%ha;
                A[i+j] = (x+y)%ha;A[i+mid+j] = (x+ha-y)%ha;
            }
        }
        w += (mid<<1);
    }
}

inline Poly operator * (Poly A,Poly B){
    int len = A.deg()+B.deg();init(len);
    NTT(A);NTT(B);FOR(i,0,N-1) A[i] = 1ll*A[i]*B[i]%ha;
    NTT(A);std::reverse(A.x.begin()+1,A.x.end());int inv = qpow(N);
    A.ext(len);FOR(i,0,A.deg()) A[i] = 1ll*A[i]*inv%ha;
    return A;
}

int main(){
//    freopen("A.in","r",stdin);
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    int *w = W;for(int n = 2,i = 0;i <= 16;++i,n <<= 1) FOR(j,0,n-1) *w = qpow(3,((ha-1)/n)*j),++w;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",a+i,b+i);
    sz[0] = 1;Poly ans;ans.ext(1);ans[1] = 1;
    FOR(i,1,n){
        sz[i] = sz[i-1]+a[i]-b[i];
        int l = std::max(-b[i],1-sz[i-1]),r = std::min(a[i],sz[i-1]+a[i]-b[i]-1);
        Poly F,G;F.ext(sz[i-1]);G.ext(r-l);
        FOR(j,1,sz[i-1]) F[j] = ans[j];
        FOR(j,0,r-l) G[j] = 1ll*inv[b[i]+j+l]*inv[a[i]-j-l]%ha;
        F = F*G;
        ans.x.clear();ans.ext(sz[i]);
        FOR(j,1,sz[i]) if(0 <= j-l && j-l <= F.deg()) ans[j] = 1ll*F[j-l]*fac[a[i]+b[i]]%ha;
    }
    int res = 0;FOR(i,1,ans.deg()) add(res,ans[i]);
    printf("%d\n",res);
    return 0;
}
