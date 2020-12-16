#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define SZ(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define LD long double

const int MAXN = 1000+5;
const LD EPS = 1e-8;

inline int sgn(LD x){
    if(std::abs(x) <= EPS) return 0;
    if(x > 0) return 1;
    return -1;
}

struct Node{
    LD x,y;
    Node(LD x=0,LD y=0) : x(x),y(y) {}

    inline Node operator - (const Node &t) const {
        return Node(x-t.x,y-t.y);
    }

    inline LD operator * (const Node &t) const {
        return x*t.y-y*t.x;
    }

    inline void read(){
        double a,b;scanf("%lf%lf",&a,&b);x = a;y = b;
    }
}a[MAXN],b[MAXN];
int n,m;

inline LD intersect(Node a,Node b){// 与 x 轴交点
    if(a.x > b.x) std::swap(a,b);
    if(!sgn(a.x-b.x)){
        if(a.y > b.y) std::swap(a,b);
        if(sgn(a.y) <= 0 && sgn(b.y) >= 0) return b.x;
        return -1e18;
    }
//    double k = (a.y-b.y)/(a.x-b.x),bb = a.y-k*a.x;
    LD xx = a.x-(a.x-b.x)*a.y/(a.y-b.y);
    return xx;
}

inline Node rotate(Node a,LD theta){// 逆时针
    return Node(a.x*cos(theta)-a.y*sin(theta),a.x*sin(theta)+a.y*cos(theta));
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) b[i].read();
//    bool flag = (n == 12 && m == 93 && b[2].x == 5);
    FOR(cc,1,m){
        Node s,v;s.read();v.read();
//        if(flag && cc == 83){
//            printf("%lf %lf %lf %lf\n",(double)s.x,(double)s.y,(double)v.x,(double)v.y);
//        }
        if(s.x > v.x) std::swap(s,v);
        v = v-s;double len = std::sqrt(v.x*v.x+v.y*v.y);
        Node e = Node(v.y,-v.x);
        FOR(i,1,n){
            Node t = b[i]-s;
            a[i].y = std::abs(t*v)/len;
            if(!sgn(t.x*t.x+t.y*t.y-a[i].y*a[i].y)) a[i].x = 0;
            else a[i].x = std::sqrt(t.x*t.x+t.y*t.y-a[i].y*a[i].y);
            if(v*t < 0) a[i].y = -a[i].y;
            if(t*e < 0) a[i].x = -a[i].x;
        }
        //FOR(i,1,n) printf("(%Lf,%Lf)\n",a[i].x,a[i].y);
        std::vector<LD> nd;
        std::vector<std::pair<LD,LD> > S;
        FOR(i,1,n){
            if(sgn(a[i].y) < 0 && sgn(a[i%n+1].y) < 0) continue;
            if(sgn(a[i].y) > 0 && sgn(a[i%n+1].y) > 0) continue;
            if(!sgn(a[i].y) && !sgn(a[i%n+1].y)){
                S.pb(MP(std::min(a[i].x,a[i%n+1].x),std::max(a[i].x,a[i%n+1].x)));
                continue;
            }
            if(!sgn(a[i].y-a[i%n+1].y)) continue;
            LD x = intersect(a[i],a[i%n+1]);
            if(x == -1e18) continue;
            if((!sgn(x-a[i].x) && !sgn(a[i].y)) || (!sgn(x-a[i%n+1].x) && !sgn(a[i%n+1].y))){
                bool flag = 0;
                if(!sgn(x-a[i%n+1].x) && !sgn(a[i%n+1].y)) flag = 1,std::swap(a[i],a[i%n+1]);
//                DEBUG(a[i].y);DEBUG(a[i%n+1].y);DEBUG(x);
                if(sgn(a[i].y-a[i%n+1].y) > 0) nd.pb(x);
                if(flag) std::swap(a[i],a[i%n+1]);
            }
            else nd.pb(x);
        }
  //      FOR(i,1,n) printf("%f %f\n",a[i].x,a[i].y);
        std::sort(all(nd));assert(nd.size()%2 == 0);
        for(int i = 0;i < nd.size();i += 2) S.pb(MP(nd[i],nd[i+1]));
        std::sort(all(S));
        LD ans = 0,now = -1e18;
        for(auto x:S){
            if(now < x.fi) now = x.fi;
            if(now < x.se) ans += x.se-now,now = x.se;
        }
        printf("%.10f\n",(double)ans);
    }
    return 0;
}

