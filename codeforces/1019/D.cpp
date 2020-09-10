#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2000+5;
LL x[MAXN],y[MAXN];
int n;LL S;
LL G[MAXN][MAXN];

int main(){
	scanf("%d%lld",&n,&S);S <<= 1;
	// n = 2000;
	FOR(i,1,n) scanf("%lld%lld",x+i,y+i);
	FOR(a,1,n) FOR(b,a+1,n) G[a][b] = x[a]*y[b]-x[b]*y[a];
	FOR(a,1,n){
		//xayb-xbya+yc(xb-xa)+xc(ya-yb)
		FOR(b,a+1,n){
			register LL t = S-G[a][b];
			register LL _t = -(S+G[a][b]);
			FOR(c,b+1,n){
				LL tt = G[b][c]-G[a][c];
				if(t == tt || _t == tt){
					printf("Yes\n%lld %lld\n%lld %lld\n%lld %lld\n",x[a],y[a],x[b],y[b],x[c],y[c]);
					exit(0);
				}
				// if(_t == G[a][c]-G[b][c]){
					// printf("Yes\n%lld %lld\n%lld %lld\n%lld %lld\n",x[a],y[a],x[b],y[b],x[c],y[c]);
					// exit(0);				/	
				// }
			}
		}
	}
	puts("No");
	return 0;
}