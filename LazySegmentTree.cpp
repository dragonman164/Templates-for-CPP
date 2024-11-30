template<class T,T(*queryCombine) (T,T),T(*queryIdentity)(),T(*modifyCombine) (T,T),T(*modifyIdentity)()>
class LazySegmentTree{
    private : 
    int n;
    T *t,*lazy;
    
    void push(T v) {
        t[v*2] = modifyCombine(t[v*2],lazy[v]);
        lazy[v*2] = modifyCombine(lazy[v*2],lazy[v]);
        t[v*2+1] = modifyCombine(t[v*2 + 1],lazy[v]);
        lazy[v*2+1] = modifyCombine(lazy[v*2 + 1],lazy[v]);
        lazy[v] = modifyIdentity();
    }
 
    void build(vector<T> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = queryCombine(t[v*2],t[v*2+1]);
        }
    }
    
 T run_query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return queryIdentity();
    if (l <= tl && tr <= r)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return queryCombine(run_query(v*2, tl, tm, l, min(r, tm)), 
               run_query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
 
    void run_update(int v, int tl, int tr, int l, int r, T addend) {
        if (l > r) 
            return;
        if (l == tl && tr == r) {
            t[v] = modifyCombine(t[v],addend);
            lazy[v] = modifyCombine(lazy[v],addend);
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            run_update(v*2, tl, tm, l, min(r, tm), addend);
            run_update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = queryCombine(t[v*2], t[v*2+1]);
        }
    }
    public: 
 
    LazySegmentTree(vector<T> &a){
        this->n = a.size();
        this->t = new T[4*(n + 1)];
        this->lazy = new T[4*(n + 1)];
        for(int i = 0; i < 4*(n + 1); i++){
            t[i] = queryIdentity();
            lazy[i] = modifyIdentity();
        }
        build(a, 1, 0, n-1);
    }
    T query(int l, int r){
        return run_query(1, 0, n-1, l, r);
    }
 
    void update(int l,int r, T new_val){
        run_update(1, 0, n-1, l,r,new_val );
    }
    
    
};
