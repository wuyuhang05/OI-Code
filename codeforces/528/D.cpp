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

const int MAXN = 6e5 + 5;
const int ha = 998244353;
const int g = 3;
const int invg = 332748118;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

struct Poly{
    std::vector<int> x;
    inline int deg(){return SZ(x)-1;}
    inline void ext(const int &n){x.resize(n+1);}
    inline int& operator [] (const int &n){return x[n];}
};

int r[MAXN],N;

inline void init(int n){
    int len = 0;N = 1;while(N <= n) N <<= 1,len++;
    FOR(i,0,N-1) r[i] = (r[i>>1]>>1)|((i&1)<<(len-1));
}

inline void NTT(Poly &A,int opt){
    A.ext(N);FOR(i,0,N-1) if(i < r[i]) std::swap(A[i],A[r[i]]);
    for(int mid = 1;mid < N;mid <<= 1){
        int W = qpow(opt==1?g:invg,(ha-1)/(mid<<1));
        for(int i = 0;i < N;i += (mid<<1)){
            for(int w=1,j = 0;j < mid;++j,w = 1ll*w*W%ha){
                int x = A[i+j],y = 1ll*A[i+mid+j]*w%ha;
                A[i+j] = x+y-ha;A[i+j] += A[i+j]>>31&ha;
                A[i+mid+j] = x-y;A[i+mid+j] += A[i+mid+j]>>31&ha;
            }
        }
    }
    if(opt == -1){
        int inv = qpow(N);
        FOR(i,0,N-1) A[i] = 1ll*A[i]*inv%ha;
    }
}

inline Poly operator * (Poly A,Poly B){
    int len = A.deg()+B.deg();init(len);
    NTT(A,1);NTT(B,1);FOR(i,0,N-1) A[i] = 1ll*A[i]*B[i]%ha;NTT(A,-1);
    return A;
}

int n,m,k;
int ans[MAXN],S[MAXN],T[MAXN];
char str[MAXN];
int sm[MAXN][4],occ[MAXN];

inline int ctoi(char x){
    if(x == 'A') return 0;
    if(x == 'G') return 1;
    if(x == 'C') return 2;
    return 3;
}

inline void gao(int o){
    Poly A,B;A.ext(n-1);B.ext(m-1);
    FOR(i,0,n-1) A[i] = !((occ[i]>>o)&1);
    FOR(i,0,m-1) B[i] = (T[i]==o);
    std::reverse(all(B.x));
    A = A*B;
    FOR(i,0,n-m) ans[i] |= A[i+m-1];
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s",str);FOR(i,0,n-1) S[i] = ctoi(str[i]);
    scanf("%s",str);FOR(i,0,m-1) T[i] = ctoi(str[i]);
    FOR(i,0,n-1){
        if(i) FOR(j,0,3) sm[i][j] = sm[i-1][j];
        ++sm[i][S[i]];
    }
    FOR(i,0,n-1){
        int l = std::max(0,i-k),r = std::min(n-1,i+k);
        FOR(j,0,3) if(sm[r][j]^(l==0?0:sm[l-1][j])) occ[i] |= (1<<j);
    }
    FOR(i,0,3) gao(i);int res = 0;
    FOR(i,0,n-m) res += (ans[i]==0);
    printf("%d\n",res);
    return 0;
}
