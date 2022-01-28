class LCA{
    int n, l;
    vector<vector<int>> adj;
        int timer;
    vector<int> tin, tout,depth;
    vector<vector<int>> up;

    public : 
    LCA(int n){
        this->n = n;
        this->adj = vector<vector<int>>(n + 1);
        this->depth = vector<int>(n + 1);
    } 

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Call Prerprocess Method before queries
    void preprocess(int root) {
        depth[root] = 0;
        tin.resize(n + 1);
        tout.resize(n + 1);
        timer = 0;
        this->l = ceil(log2(n));
        up.assign(n + 1, vector<int>(l + 1));
        dfs(root, root);
    }

    void dfs(int v, int p)
    {
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= l; ++i)
            up[v][i] = up[up[v][i-1]][i-1];

        for (int u : adj[v]) {
            if (u != p)
            {
                depth[u] = depth[v] + 1;
                dfs(u, v);
            }
        }

        tout[v] = ++timer;
    }

    bool is_ancestor(int u, int v)
    {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int kthancestor(int node, int k)
    {
        if(depth[node] < k) return -1;
        for(int i = l ; i >= 0; i--){    
            if(k&(1<<i))
                node = up[node][i];
            if(node == -1) return node;
        }
        return node;
    }
    

    int lca(int u, int v)
    {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    }

    int distance(int u, int v){
        int parent = this->lca(u, v);
        return depth[v] + depth[u] - 2*depth[parent];
    }
};