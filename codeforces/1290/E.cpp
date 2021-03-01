#include <bits/stdc++.h>

#define fi first
#define se second
#define DB double
#define U unsigned
#define P std::pair
#define LL long long
#define LD long double
#define pb emplace_back
#define MP std::make_pair
#define SZ(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;

struct DS{
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)
    LL sm[MAXN<<2];
    int cnt[MAXN<<2],tag[MAXN<<2];
    int mx[MAXN<<2],cmx[MAXN<<2],mxc[MAXN<<2];

    inline void pushup(int x){
        sm[x] = sm[lc]+sm[rc];cnt[x] = cnt[lc]+cnt[rc];
        if(mx[lc] < mx[rc]){
            mx[x] = mx[rc];mxc[x] = mxc[rc];
            cmx[x] = std::max(mx[lc],cmx[rc]);
        }
        else if(mx[lc] == mx[rc]){
            mx[x] = mx[lc];mxc[x] = mxc[lc]+mxc[rc];
            cmx[x] = std::max(cmx[lc],cmx[rc]);
        }
        else{
            mx[x] = mx[lc];mxc[x] = mxc[lc];
            cmx[x] = std::max(cmx[lc],mx[rc]);
        }
    }

    inline void build(int x,int l,int r){
        tag[x] = 0;
        if(l == r){
            sm[x] = cnt[x] = 0;
            mx[x] = cmx[x] = -1e9;mxc[x] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc,l,mid);build(rc,mid+1,r);
        pushup(x);
    }

    inline void update(int x,int l,int r,int p,int d){
        if(l == r){
            sm[x] = mx[x] = d;cnt[x] = 1;mxc[x] = 1;
            return;
        }
        int mid = (l + r) >> 1;pushdown(x);
        if(p <= mid) update(lc,l,mid,p,d);
        else update(rc,mid+1,r,p,d);
        pushup(x);
    }

    inline void cover1(int x,int d){// 区间+=d
        if(!cnt[x]) return;
        sm[x] += 1ll*cnt[x]*d;mx[x] += d;if(cmx[x] != -1e9) cmx[x] += d;
        tag[x] += d;
    }

    inline void cover2(int x,int d){// 区间max(d,*)
        if(mx[x] <= d || !cnt[x]) return;
        assert(cmx[x] < d);
        sm[x] += 1ll*(d-mx[x])*mxc[x];
        mx[x] = d;
    }

    inline void pushdown(int x){
        if(tag[x]){
            cover1(lc,tag[x]);
            cover1(rc,tag[x]);
            tag[x] = 0;
        }
        cover2(lc,mx[x]);
        cover2(rc,mx[x]);
    }

    inline void modify1(int x,int l,int r,int L,int R,int d){
        if(L > R || !cnt[x]) return;
        if(l == L && r == R) return cover1(x,d);
        int mid = (l + r) >> 1;pushdown(x);
        if(R <= mid) modify1(lc,l,mid,L,R,d);
        else if(L > mid) modify1(rc,mid+1,r,L,R,d);
        else modify1(lc,l,mid,L,mid,d),modify1(rc,mid+1,r,mid+1,R,d);
        pushup(x);
    }

    inline void modify2(int x,int l,int r,int L,int R,int d){
        if(L > R || !cnt[x] || mx[x] <= d) return;
        if(l == L && r == R && cmx[x] < d) return cover2(x,d);
        int mid = (l + r) >> 1;pushdown(x);
        if(R <= mid) modify2(lc,l,mid,L,R,d);
        else if(L > mid) modify2(rc,mid+1,r,L,R,d);
        else modify2(lc,l,mid,L,mid,d),modify2(rc,mid+1,r,mid+1,R,d);
        pushup(x);
    }

    inline int query(int x,int l,int r,int L,int R){
        if(l == L && r == R) return cnt[x];
        int mid = (l + r) >> 1;pushdown(x);
        if(R <= mid) return query(lc,l,mid,L,R);
        if(L > mid) return query(rc,mid+1,r,L,R);
        return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
    }
}dl,dr;

int n,a[MAXN],ps[MAXN];

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),ps[a[i]] = i;
    dl.build(1,1,n);dr.build(1,1,n);
    FOR(i,1,n){
        int p = ps[i],rk = dr.query(1,1,n,1,p)+1;
        dr.update(1,1,n,p,i);
        dl.update(1,1,n,p,-1);
        dr.modify1(1,1,n,p+1,n,1);
        dl.modify1(1,1,n,p+1,n,-1);
        dr.modify2(1,1,n,1,p-1,rk-1);
        dl.modify2(1,1,n,p+1,n,-(rk+1));
        printf("%lld\n",dr.sm[1]+dl.sm[1]+i);
//        if(i == 2) return 0;
    }
    return 0;
}
