/* God is Great !
    Author : SANIDHIYA */
#include<bits/stdc++.h> 
using namespace std;
const int MAX = 1e5 + 5;
vector<int> adj[MAX],adjt[MAX];
stack<int> topo;
vector<bool> vis1(MAX,false),vis2(MAX, false);
void dfs(int root){
    for(auto elem : adj[root]){
        if(!vis1[elem]){
            vis1[elem] = true;
            dfs(elem);
        }
    }    
    topo.push(root);
}
vector<int> scc(int curr){
    queue<int> temp;
    temp.push(curr);
    vector<int> ans;
    ans.push_back(curr);
    while(!temp.empty()){
        int curr = temp.front();
        temp.pop();
        for(auto elem : adjt[curr]){
            if(!vis2[elem]){
                vis2[elem] = true;
                ans.push_back(elem);
                temp.push(elem);
            }
        }
    }
    return ans;
}
void solve()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++ ){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adjt[v].push_back(u);
    }
    for(int i = 1; i <= n ; i++ ){
        if(!vis1[i]){
            vis1[i] = true;
            dfs(i);
        }
    }
    vector<vector<int>> sccs;
    while(!topo.empty()){
        int i = topo.top();
        topo.pop();
        if(!vis2[i]){
            vis2[i] = true;
            sccs.push_back(scc(i));
        }
    }
    if(sccs.size() == 1) cout<<"YES\n";
    else{
        cout<<"NO\n";
        cout<<sccs[1][0]<<" "<<sccs[0][0]<<"\n";
    }
 
 
 
}
int main()
{
ios_base::sync_with_stdio(false);
cout.tie(NULL);
cin.tie(NULL);
solve();
return 0;
}
