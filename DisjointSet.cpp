class DisjointSet{
    vector<int> parent,rank;
    int n;
    public : 
    DisjointSet(int n){
        this->n = n;
        this->parent = vector<int>(n + 1);
        this->rank = vector<int>(n+ 1);
        for(int i = 1; i <= n ;i ++)
        parent[i] = i;
    }
    int findparent(int u){
        if(parent[u] == u) return u;
        return parent[u] = findparent(parent[u]);
    }
    void Union(int u, int v){
        int parent_u = findparent(u);
        int parent_v = findparent(v);
        if(rank[parent_u] > rank[parent_v]){
            parent[parent_v] = parent_u;
            rank[parent_u] ++ ;
        }else{
            parent[parent_u] = parent_v;
            rank[parent_v] ++ ;
        }
        
    }
    
 
};
