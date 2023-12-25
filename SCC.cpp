/* God is Great !
    Author : SANIDHIYA*/
#include<bits/stdc++.h> 
using namespace std;
const int mod = 1e9 + 7;
void solve()
{
    // dp[i] number of ways to reach i from 1
    int n, m;
    cin >> n >> m;
    vector<int> adj[n + 1],back_edge[n + 1];
    map<int,int> deg;
 
    for(int i = 0; i < m; i++ ){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        back_edge[v].push_back(u);
        deg[v]++;
 
    }
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    vector<bool> vis(n + 1, false);
    queue<int> temp;
        for(int i = 1; i <= n; i++ ){
        if(deg[i] == 0) {
            temp.push(i);
            vis[i] = true;
        }
    }
    while(!temp.empty()){
        int curr = temp.front();
        temp.pop();
        for(auto elem : back_edge[curr]){
            dp[curr] = (dp[curr]%mod + dp[elem]%mod)%mod;
        }
        for(auto elem : adj[curr]){
            if(!vis[elem]){
                deg[elem]--;
                if(deg[elem] == 0) {
                    vis[elem] = true;
                    temp.push(elem);
                }
           
            }
        }
    }
    cout<<dp[n]<<"\n";
 
 
}
int main()
{
ios_base::sync_with_stdio(false);
cout.tie(NULL);
cin.tie(NULL);
solve();
return 0;
}
