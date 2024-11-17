vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
vector<int> searcher(string &text, string &pattern){
    string concat = pattern + "$" + text;
    int l = concat.size();
    vector<int> z = z_function(concat);
    vector<int> pos;
    for(int i = 0; i < l; i++){
        if(z[i] == pattern.size()){
            pos.push_back(i - pattern.size() - 1);
        }
    }
    return pos;
}
