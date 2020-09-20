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

const int MAXN = 3e5 + 5;
const int ha = 1e9 + 9;
int pw[MAXN];

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
    #undef SIZE
}

template <typename T>
inline void read(T &x){
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

struct Node{
    int l,r,sm,rev;
    Node(int l=0,int r=0,int sm=0,int rev=0) : l(l),r(r),sm(sm),rev(rev) {}

    friend Node operator + (const Node &a,const Node &b){
        return Node(a.l,b.r,(1ll*a.sm*pw[b.r-b.l+1]%ha+b.sm)%ha,(1ll*b.rev*pw[a.r-a.l+1]%ha+a.rev)%ha);
    }
}sm[MAXN<<2];

#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void build(int x,int l,int r){
    sm[x] = Node(l,r,1,1);
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    sm[x] = sm[lc]+sm[rc];
}

inline void update(int x,int l,int r,int p,int d){
    if(l == r){
        sm[x] = Node(l,r,d,d);
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) update(lc,l,mid,p,d);
    else update(rc,mid+1,r,p,d);
    sm[x] = sm[lc]+sm[rc];
}

inline Node query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sm[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

int a[MAXN],n;

inline void Solve(){// left:0 right:1
    read(n);FOR(i,1,n) read(a[i]);
    build(1,1,n);
    FOR(i,1,n){
        update(1,1,n,a[i],0);
        int len = std::min(a[i]-1,n-a[i]);
        if(len <= 0) continue;
        if(query(1,1,n,a[i]-len,a[i]-1).rev != query(1,1,n,a[i]+1,a[i]+len).sm){
            puts("YES");
            return;
        }
    }
    puts("NO");
}

int main(){
    pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = 2ll*pw[i-1]%ha;
    int T=1;//read(T);
    while(T--) Solve();
    return 0;
}
/*
枚举mid,是否存在mid-i=j-mid,i 在左边 j 在右边
如果在当前点左边就是0 右边就是1 判断是否是回文
每次修改会改一个区间
*/
