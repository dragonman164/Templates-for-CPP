class SegmentTree{
   int n;
    vector<long long int> t;
    public: 
    SegmentTree(long long int n){
        this->n = n;
        t = vector<long long int>(4*(n + 1));
    }
    // Call this Function with array,1,0,n-1 where n is length
    void build(vector<long long int> &a,int v,int tl,int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
       int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1]; // Modify this line for different type of queries
        }
    }

    // Call as 1, 0, n-1, index, new_val
    void update(long long int v,int tl,int tr,int pos,int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
       int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = t[v*2] + t[v*2+1]; // Modify this line for different type of queries
    }
    }

    // call as 1, 0, n-1, l, r
   // modify this function according to the query being asked
   int query(long long int v,int tl,int tr,int l,int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
   int tm = (tl + tr) / 2;
    return query(v*2, tl, tm, l, min(r, tm)) + 
           query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

};