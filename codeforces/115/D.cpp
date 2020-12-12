#pragma GCC optimize("Ofast")
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
const int ha = 1e6 + 3;
char str[MAXN];
int a[MAXN];
int n;
int f[MAXN][MAXN],g[MAXN][MAXN];

int main(){
    scanf("%s",str+1);int len = strlen(str+1);
    //int len = 2000;
    //FOR(i,1,1000) str[i<<1] = '-',str[i<<1|1] = '1';
    FOR(i,1,len){
        if(isdigit(str[i])){
            a[++n] = 0;
            while(isdigit(str[i])) ++i;
            --i;
        }
        else{
            if(str[i] == '+' || str[i] == '-') a[++n] = 1;
            else a[++n] = 2;
        }
    }
    FOR(i,1,n) f[i][i] = g[i][i] = !a[i];
    ROF(l,n-1,1) if(a[l] != 2){
        int *p1 = f[l]-1;
        FOR(r,l+1,n) if(!a[r]){
            LL t = 0;
            if(a[l] == 1) t = f[l+1][r];
            int *p2 = g[r]+1;
            FOR(k,l+1,r-1) if(a[k]) t += 1ll*p1[k]*p2[k];
            f[l][r] = g[r][l] = t%ha;
        }
    }
    printf("%d\n",f[1][n]);
    return 0;
}
