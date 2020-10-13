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
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
const int MAXM = 16;
const int ha = 1e9 + 7;
const int inv2 = 1;
const int inv6 = 1;

int n;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

struct Edge{
	int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int sz[MAXN],sm[MAXN],sm2[MAXN],dep[MAXN];// 到子树每个点的距离和/平方和
// 到所有点的距离和/平方和
int f[MAXN][MAXM+1];

inline void add(int &x,int y){
	x += y;if(x >= ha) x -= ha;
}

inline void dfs1(int v,int fa=0){
	sz[v] = 1;f[v][0] = fa;dep[v] = dep[fa]+1;
	FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dfs1(e[i].to,v);
		sz[v] += sz[e[i].to];
	}
}

inline void dfs2(int v,int fa=0){
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dfs2(e[i].to,v);
		add(sm[v],(sm[e[i].to]+1ll*e[i].w*sz[e[i].to]%ha)%ha);
		add(sm2[v],sm2[e[i].to]);
		add(sm2[v],1ll*e[i].w*e[i].w%ha*sz[e[i].to]%ha);
		add(sm2[v],2ll*e[i].w%ha*sm[e[i].to]%ha);
	}
}

int pre[MAXN];
int ss[MAXN],ss2[MAXN];

inline void dfs3(int v,int fa=0){
	int s1 = ss[v],s2 = ss2[v];
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		add(s1,sm[e[i].to]);
		add(s1,1ll*sz[e[i].to]*e[i].w%ha);
		add(s2,sm2[e[i].to]);
		add(s2,1ll*e[i].w*e[i].w%ha*sz[e[i].to]%ha);
		add(s2,2ll*e[i].w%ha*sm[e[i].to]%ha);
	}
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		add(s1,ha-sm[e[i].to]);
		add(s1,ha-1ll*sz[e[i].to]*e[i].w%ha);
		add(s2,ha-sm2[e[i].to]);
		add(s2,ha-1ll*e[i].w*e[i].w%ha*sz[e[i].to]%ha);
		add(s2,ha-2ll*e[i].w%ha*sm[e[i].to]%ha);
		// if(e[i].to == 2){
			// DEBUG(s1);
		// }
		ss[e[i].to] = s1;
		add(ss[e[i].to],1ll*e[i].w*(n-sz[e[i].to])%ha);
		ss2[e[i].to] = s2;
		add(ss2[e[i].to],1ll*e[i].w*e[i].w%ha*(n-sz[e[i].to])%ha);
		add(ss2[e[i].to],2ll*e[i].w%ha*s1%ha);
		add(s1,sm[e[i].to]);
		add(s1,1ll*sz[e[i].to]*e[i].w%ha);
		add(s2,sm2[e[i].to]);
		add(s2,1ll*e[i].w*e[i].w%ha*sz[e[i].to]%ha);
		add(s2,2ll*e[i].w%ha*sm[e[i].to]%ha);
	}
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		pre[e[i].to] = (pre[v]+e[i].w)%ha;
		dfs3(e[i].to,v);
	}
}

inline int lca(int x,int y){
	if(dep[x] != dep[y]){
		if(dep[x] < dep[y]) std::swap(x,y);
		int d = dep[x]-dep[y];
		FOR(i,0,MAXM) if((d>>i)&1) x = f[x][i];
	}
	if(x == y) return x;
	ROF(i,MAXM,0){
		if(f[x][i] == f[y][i]) continue;
		x = f[x][i],y = f[y][i];
	}
	return f[x][0];
}

int main(){
	scanf("%d",&n);
	FOR(i,2,n){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	dfs1(1);dfs2(1);dfs3(1);
	// DEBUG(ss[2]);
	// exit(0);
	int q;scanf("%d",&q);
	while(q--){
		int u,v;scanf("%d%d",&v,&u);// u子树
		int l = lca(u,v),ans = 0;
		int d = ((pre[u]+pre[v])%ha+ha-2ll*pre[l]%ha)%ha;
		if(l == u){
			ans = ss2[u];
			add(ans,1ll*(n-sz[u])*d%ha*d%ha);
			add(ans,2ll*d%ha*ss[u]%ha);
			ans = 2ll*ans%ha;ans = ha-ans;
			add(ans,sm2[v]);add(ans,ss2[v]);
		}
		else{
			ans = sm2[u];
			add(ans,1ll*sz[u]*d%ha*d%ha);
			add(ans,2ll*d%ha*sm[u]%ha);
			ans = 2ll*ans%ha;
			DEBUG(ss2[v]);
			add(ans,ha-sm2[v]);
			add(ans,ha-ss2[v]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
到某个子树内的点 \sum x^2 + sz*d^2 + 2d\sum x
都维护出来 如果询问点在子树内 就可以拆一下暴力爬的式子 前缀和维护
*/