#include<bits/stdc++.h>

using namespace std;


class segmentTree {
    private : vector<vector<long long int>> v;
    
    public:
    segmentTree(int n){
        vector<vector<long long int>> t(4*n,vector<long long int>(2,0));
        v=t;
    }
    
    vector<long long int> merge(vector<long long int> a,vector<long long int> b){
        vector<long long int> p = {0,0};
        p[0] = max(a[0],b[0]);
        p[1] = min(a[1],b[1]);
        return p;
    }
    
    
    void build(int node,int l,int r,int st,int ed,vector<long long int> &a){
        if(l>r){
            return;
        }
        if(l==r){
            v[node][0] = a[l];
            v[node][1] = a[l];
            return ;
        }
        int mid = (l+r)/2;
        build(2*node,l,mid,st,ed,a);
        build(2*node+1,mid+1,r,st,ed,a);
        v[node] = merge(v[2*node],v[2*node+1]);
    }
    
    vector<long long int> query(int node,int l,int r,int st,int ed){
        if(l>=st && r<=ed){
            return v[node];
        }
        long long int f = 1e18;
        if(l>ed || st>r){
            return {-f,f};
        }
        int mid = (l+r)/2;
        vector<long long int> a,b;
        a = query(2*node,l,mid,st,ed);
        b = query(2*node+1,mid+1,r,st,ed);
        return merge(a,b);
    }
};

void solve(){
    int n;
    cin>>n;
    int q;
    cin>>q;
    vector<int> a(n,0),b(n,0);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    vector<long long int> vt(n+1,0);
    for(int i=0;i<n;i++){
        vt[i+1] = vt[i]+b[i]-a[i];
        //cout<<vt[i+1]<<" ";
    }
    //cout<<endl;
    segmentTree tree(n+1);
    tree.build(1,1,n,1,n,vt);
    
    for(int i=0;i<q;i++){
        int l,r;
        cin>>l>>r;
        if(vt[r]-vt[l-1]){
            cout<<"-1"<<endl;
        }else {
            auto j = tree.query(1,1,n,l,r);
            //cout<<j[0]<<" "<<j[1]<<endl;
            if(j[1]-vt[l-1]<0)
                cout<<-1<<endl;
            else 
                cout<<j[0]-vt[l-1]<<endl;
        }
    }
}


int main(){
    int t=1;
//    cin>>t;
    while(t--){
        solve();
    }
}
