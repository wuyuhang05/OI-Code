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

const int MAXN = 300+5;
int n,m,a[MAXN][MAXN],b[MAXN][MAXN];
bool h[MAXN*MAXN],l[MAXN*MAXN];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&a[i][j]);
    FOR(i,1,n){
        int mx = 0;
        FOR(j,1,m) mx = std::max(mx,a[i][j]);
        h[mx] = 1;
    }
    FOR(j,1,m){
        int mx = 0;
        FOR(i,1,n) mx = std::max(mx,a[i][j]);
        l[mx] = 1;
    }
    std::queue<P> q;
    int x=0,y=0;
    ROF(i,n*m,1){
        x += h[i];y += l[i];
        if(h[i] || l[i]){
            b[x][y] = i;
 //           printf("%d %d\n",x,y);
        }
        else{
            b[q.front().fi][q.front().se] = i;
            q.pop();
        }
        if(h[i]) ROF(i,y-1,1) q.push(MP(x,i));
        if(l[i]) ROF(i,x-1,1) q.push(MP(i,y));
    }
    FOR(i,1,n) FOR(j,1,m) printf("%d%c",b[i][j]," \n"[j==m]);
    return 0;
}
