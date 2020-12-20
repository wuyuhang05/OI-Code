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

const int ha = 1e9 + 7;
const int inv2 = 500000004;
LL n,m;
LL ans = 0;

int main(){
    scanf("%lld%lld",&n,&m);
    ans = (ha-n%ha*(m%ha)%ha)%ha;m = std::min(m,n);
    for(LL l = 1,r;l <= m;l = r+1){
        r = std::min(m,n/(n/l));
        LL c = r%ha*((r+1)%ha)%ha*inv2%ha;
        (c += ha-(l-1)%ha*(l%ha)%ha*inv2%ha) %= ha;
        (ans += (n/l)%ha*(c%ha)%ha)%=ha;
    }
    ans = (ha-ans)%ha;
    printf("%lld\n",ans);
    return 0;
}
