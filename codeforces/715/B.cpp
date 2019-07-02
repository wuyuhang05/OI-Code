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
#define P std::pair<LL,LL>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
    #define SIZE 1000000
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(LL &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

#define int LL
const int MAXN = 1000+5;
const int MAXM = 10000+5;

struct Edge{
    int to,w,nxt,id;
}e[MAXM<<2];
int head[MAXN],cnt;
int eu[MAXM<<2],ev[MAXM<<2];LL ew[MAXM<<2];
bool emp[MAXM<<2];
LL dis1[MAXN],dis2[MAXN];
int n,m,l,s,t;

inline void add(int id,int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u],id};head[u] = cnt;
}

inline void dij(int type,LL dis[],int s){
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    FOR(i,1,n) dis[i] = 1e18;
    q.push(MP(dis[s] = 0,s));
    while(!q.empty()){
        P vv = q.top();q.pop();
        if(vv.fi != dis[vv.se]) continue;
//        if(used[v]) continue;
  //      used[v] = true;
        int v = vv.se;
        for(int i = head[v];i;i = e[i].nxt){
            int w = e[i].w,id = e[i].id;
            if(emp[id] && type){
                w = ew[id] = std::max(ew[id],l-dis[v]-dis1[e[i].to]);
            }
            if(dis[e[i].to] > dis[v] + w){
                dis[e[i].to] = dis[v] + w;
                q.push(MP(dis[e[i].to],e[i].to));
            }
        }
    }
}

signed main(){
    read(n);read(m);read(l);read(s);read(t);++s;++t;
    FOR(i,1,m){
        int u,v,w;read(u);read(v);read(w);++u,++v;
        eu[i] = u;ev[i] = v;ew[i] = w;emp[i] = !w;if(!w) w = ew[i] = 1;
        add(i,u,v,w);add(i,v,u,w);
    }
    dij(0,dis1,t);dij(1,dis2,s);
    if(dis2[t] != l){
        puts("NO");
        return 0;
    }
    puts("YES");
    FOR(i,1,m) printf("%lld %lld %lld\n",eu[i]-1,ev[i]-1,ew[i]);
    return 0;
}
