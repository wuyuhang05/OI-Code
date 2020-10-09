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

const int MAXN = 500+5;
int f[MAXN][MAXN],n;
char str[MAXN];
// 删除操作 一定互相包含 不交的连通块顺序无关
// 删除首先枚举 mid,那么如果str[l]==str[mid]先删除[l+1,mid-1]然后l和mid就并起来了

int main(){
	scanf("%d",&n);
	scanf("%s",str+1);
	CLR(f,0x3f);
	FOR(i,1,n) f[i][i] = 1,f[i][i-1] = 0;
	FOR(len,2,n){
		FOR(l,1,n-len+1){
			int r = l+len-1;
			f[l][r] = std::min(f[l+1][r],f[l][r-1])+1;
			FOR(k,l+1,r){
				if(str[k] == str[l]){
					f[l][r] = std::min(f[l][r],f[l+1][k-1]+f[k][r]);
				}
			}
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
}