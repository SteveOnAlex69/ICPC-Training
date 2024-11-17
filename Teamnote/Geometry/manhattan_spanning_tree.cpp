

struct Point{
    ll x, y;
    Point(){}
    Point(ll x, ll y): x(x), y(y){}

    Point& operator -= (Point a){
        x -= a.x;
        y -= a.y;
        return *this;
    }
    Point operator - (Point x) const {
        Point ans = *this;
        return ans -= x;
    }
};


struct Path{
    int u, v; ll w;
    Path(){}
    Path(int _u, int _v, ll _w){u = _u, v  =_v, w = _w;}
};

const ll INF = 1e18;
namespace ManhattanSpanningTreeSolver {
    #define sz(v) ((int)v.size())

    vector<Path> solve(vector<Point> ps) {
        vector<int> id(sz(ps));
        iota(ALL(id), 0);
        vector<Path> edges;
        for(int k = 0; k < 4; ++k) {
            sort(ALL(id), [&](int i, int j) {
                return (ps[i]-ps[j]).x < (ps[j]-ps[i]).y;});
            map<ll, int> sweep;
            for (int i : id) {
                for (auto it = sweep.lower_bound(-ps[i].y);
                            it != sweep.end(); sweep.erase(it++)) {
                    int j = it->second;
                    Point d = ps[i] - ps[j];
                    if (d.y > d.x) break;
                    edges.push_back(Path(i, j, d.y + d.x));
                }
                sweep[-ps[i].y] = i;
            }
            for (Point& p : ps) if (k & 1) p.x = -p.x; else swap(p.x, p.y);
        }
        return edges;
    }
};

