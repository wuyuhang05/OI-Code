#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include<ctime>
using namespace std;
typedef long long ll;
typedef pair<int,int>P;
const int INF=0x3f3f3f3f,maxn=80005;
int n,size[maxn],fa[maxn];
vector<int>g[maxn]; 
void dfs(int u,int f)
{
    size[u]=1;
    fa[u]=f;
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        if(v==f)continue;
        dfs(v,u);
        size[u]+=size[v];
    }
}
ll C(int n)
{
    return (ll)n*(n-1)/2;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v),g[v].push_back(u);
    }
    dfs(1,0);
    ll ans=C(n)*C(n);

    for(int u=1;u<=n;u++)
    {
        ll num1=C(n),num2=C(size[u]);
        for(int i=0;i<g[u].size();i++)
        {
            int v=g[u][i];
            if(v!=fa[u])num1-=C(size[v]),num2-=C(size[v]);
            else num1-=C(n-size[u]);
        }
        ans-=(2ll*num1*num2-num2*num2);
    } 
    printf("%I64d\n",ans);
    return 0;
}
