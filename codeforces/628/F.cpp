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

const int MAXN = 2e5 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cur[MAXN],dep[MAXN],cnt=1;

inline void add(int u,int v,int w){
//    printf("%d %d %d\n",u,v,w);
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,0,head[v]};head[v] = cnt;
}

int S,T,N;

inline bool bfs(){
    std::queue<int> q;
    FOR(i,1,N) cur[i] = head[i],dep[i] = 0;q.push(S);dep[S] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].w > 0 && !dep[e[i].to]){
                dep[e[i].to] = dep[v]+1;
                q.push(e[i].to);
            }
        }
    }
    return dep[T];
}

inline int dfs(int v,int lim=1e9){
    if(v == T) return lim;
    if(!lim) return 0;
    int flow = 0;
    for(int &i = cur[v];i;i = e[i].nxt){
        if(dep[e[i].to] == dep[v]+1 && e[i].w > 0){
            int t = dfs(e[i].to,std::min(e[i].w,lim));
            if(t){
                e[i].w -= t;e[i^1].w += t;
                lim -= t;flow += t;
                if(!lim) break;
            }
        }
    }
    return flow;
}

inline int Dinic(){
    int flow=0,res=0;
    while(bfs()) while((flow=dfs(S))) res += flow;
    return res;
}

int n,b,q;
int a[MAXN],t[5];

int main(){
    scanf("%d%d%d",&n,&b,&q);
    CLR(a,-1);a[0] = 0;
    FOR(i,1,q){
        int lim,num;scanf("%d%d",&lim,&num);
        if(a[lim] != -1 && a[lim] != num){
            puts("unfair");
            return 0;
        }
        a[lim] = num;
    }
    int las = 0;
    if(a[b] == -1) a[b] = n;
    else{
        if(a[b] != n){
            puts("unfair");
            return 0;
        }
    }
    S = 1,T = 2,N = 2;
    FOR(i,0,4) t[i] = ++N;
    FOR(i,0,4) add(t[i],T,n/5);
    FOR(i,1,b){
        if(a[i] == -1) continue;
        if(a[las] > a[i] || a[i]-a[las] > i-las){
            puts("unfair");
            return 0;
        }
        // [las+1,i] 有 a[i] 个数
        int c[5];CLR(c,0);
        FOR(k,las+1,i) ++c[k%5];
        ++N;add(S,N,a[i]-a[las]);
        FOR(k,0,4) add(N,t[k],c[k]);
        las = i;
    }
    int r = Dinic();
  //  DEBUG(r);
    puts(r==n?"fair":"unfair");
    return 0;
}
