template<class T,T(*combine) (T,T),T(*identity)()>
class SegmentTree{
    private : 
    int n;
    T *t;
 
    void build(vector<T> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2],t[v*2+1]);
        }
    }
    
    T run_query(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return identity();
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return combine(run_query(v*2, tl, tm, l, min(r, tm))
           ,run_query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
 
 
    void run_update(int v, int tl, int tr, int pos, T new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            run_update(v*2, tl, tm, pos, new_val);
        else
            run_update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2],t[v*2+1]);
    }
    }   
 
    public: 
 
    SegmentTree(vector<T> &a){
        this->n = a.size();
        this->t = new T[4*(n + 1)];
        build(a, 1, 0, n-1);
    }
    T query(int l, int r){
        return run_query(1, 0, n-1, l, r);
    }
 
    void update(int pos, T new_val){
        run_update(1, 0, n-1, pos, new_val);
    }
    
    
};
