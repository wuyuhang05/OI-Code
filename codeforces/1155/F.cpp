#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 16;
const int MAXM = MAXN*MAXN;
const int times = 500000;

P edge[MAXM*2];
int n,m;
int fa[MAXN];

struct Edge{
    int to,nxt;
}e[MAXN*MAXN*MAXN];
int cnt,head[MAXN],dfn[MAXN],low[MAXN];

void add(int u,int v){
    e[++cnt]=(Edge){v,head[u]};
	head[u]=cnt;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void Union(int u,int v){
	fa[find(u)]=find(v);
}

int ts;

void init(int x){
	CLR(head,0);CLR(dfn,0);CLR(low,0);
    FOR(i,1,n) fa[i]=i;
    cnt = ts = 0;
    FOR(i,1,x){
        int u = edge[i].fi,v = edge[i].se;
        Union(u,v);
		add(u,v);add(v,u);
    }
}

bool flag;

void dfs(int v,int fa){
	if(!flag)return;
    dfn[v]=low[v]=++ts;//DEBUG(v);
    for(int i=head[v];i;i=e[i].nxt){
        if((i+1)/2==fa) continue;
        if(dfn[e[i].to]) low[v] = std::min(low[v],dfn[e[i].to]);
        else{
			dfs(e[i].to,(i+1)/2);
			low[v] = std::min(low[v],low[e[i].to]);
		}
    }
    if(dfn[v]==low[v] && v!=1){
        flag=false;
    }
}

std::vector<P> ans;

bool check(int k){
	srand(time(NULL));
    int tss=1;
    while(tss<=times){
        std::random_shuffle(edge+1,edge+m+1);
		flag=true;init(k);
        FOR(i,1,n) if(find(i)!=find(1))flag=false;
        if(!flag){	
			++tss;
			continue;
		}
        dfs(1,0);
		if(flag){
            ans.clear();
            FOR(i,1,k) ans.push_back(edge[i]);
            return true;
        }
        tss++;
    }
    return false;
}

bool g[MAXN][MAXN];
int A[MAXN];
bool vis[MAXN];

void dfs(int k){
	if(k > n){
		if(g[A[n]][1]){
			printf("%d\n",n);
			FOR(i,1,n-1)
				printf("%d %d\n",A[i],A[i+1]);
			printf("%d %d\n",A[n],A[1]);
			exit(0);
		}
		return;
	}
	FOR(i,1,n){
		if(g[i][A[k-1]] && !vis[i]){
			A[k]=i;vis[i]=true;
			dfs(k+1);vis[i]=false;A[k]=0;
		}
	}
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        g[u][v]=g[v][u]=true;
        edge[i] = MP(u,v);
    }
    A[1]=1;
	vis[1]=true;
	dfs(2);
    int l=n,r=m,as=-1;
    while(l<=r){
        int mid= (l+r) >> 1;
        if(check(mid)){
			as=mid;
			r=mid-1;
		}
        else l=mid+1;
    }
    if(as==-1){
        as=m;
		for(int i=1;i<=m;i++)ans.push_back(edge[i]);
    }
	printf("%d\n",as);
    for(auto x:ans){
    	printf("%d %d\n",x.fi,x.se);
	}
    return 0;
}

