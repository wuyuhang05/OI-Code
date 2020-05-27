/*
 * Author: RainAir
 * Time: 2020-05-27 08:27:02
 */
#include<bits/stdc++.h>

#define fi first
#define se second
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
#define int LL
const int MAXN = 1e6 + 5;
int n,a[MAXN],x,sm;
int s[MAXN],pre[MAXN];

signed main(){
    scanf("%lld",&n);int m = (n+1)/2;
    FOR(i,1,m) scanf("%lld",a+i),sm += a[i];scanf("%lld",&x);
    s[1] = sm;FOR(i,2,n-m+1) s[i] = s[i-1]+x-a[i-1];
    pre[1] = s[1];FOR(i,2,n-m+1) pre[i] = std::min(pre[i-1],s[i]);
    FOR(k,m,n){
        if(pre[n-k+1]+x*(k-m) > 0){
            printf("%lld\n",k);
            return 0;
        }
    }
    puts("-1");
    return 0;
}
/*
如果有<n/2的答案一定有>n/2 的答案
考虑对于一个 k > n/2 我们设 s[i] 表示所有的 report
s[i] = s[i-1]+(a[i+k-1]-a[i-1])
=> s[i] = s[i-1]+x-a[i-1]
要求所有 s[i] > 0
发现基本上和 k 无关了（除了 s[1]）
枚举 k 每次 k++ 的时候相当于区间加上一个 x 然后最后一个元素不要
O(nlogn)/O(n)
*/
