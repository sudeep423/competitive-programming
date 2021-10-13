//question https://codeforces.com/contest/1555/problem/E

#include<bits/stdc++.h>
using namespace std;

class segementTree {
    
    
    public :
    vector<int> tree,lazy;    
    segementTree(int n){
        vector<int> l(4*n,0);
        vector<int> r(4*n,0);
        tree = l;
        lazy = r;
    }
    
    void update(int node,int l,int r,int start,int end,int val){
        if(l>r){
            tree[node] = 1;
            return;
        }
        
        if(lazy[node]){
            if(l<r){
                lazy[2*node] = lazy[2*node] + lazy[node];
                lazy[2*node+1] = lazy[2*node+1] + lazy[node];
            }
            tree[node] = tree[node] + lazy[node];
            lazy[node]=0;
        }
        if(start>r || l>end)
            return;        
        if(start<=l && r<=end){
            if(l<r){
            lazy[2*node] = lazy[2*node] + val ;
            lazy[2*node+1] = lazy[2*node+1] + val;
            }
            tree[node] = tree[node] + val;
            return;
        }
        
        //cout<<node<<endl;
        int mid = (l+r)/2;
        update(node*2,l,mid,start,end,val);
        update(node*2+1,mid+1,r,start,end,val);
        tree[node ]= min(tree[2*node],tree[2*node+1]);
    }
    
    int query(int node,int l,int r,int start,int end){
        if(l>r || start>r || l>end)
            return 1;
        if(lazy[node]){
            if(l<r){
                lazy[2*node] = lazy[2*node] + lazy[node];
                lazy[2*node+1] = lazy[2*node+1] + lazy[node];
            }
            tree[node] = tree[node] + lazy[node];
            lazy[node]=0;
        }
        
        if(start<=l && r<=end){
            return tree[node];
        }
        int mid = (l+r)/2;
        int a = query(node*2,l,mid,start,end);
        int b = query(node*2+1,mid+1,r,start,end);
        return min(a,b);
    }
};

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> vt;
    for(int i=0;i<n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        vt.push_back({c,a,b});
    }
    sort(vt.begin(),vt.end());
    segementTree st(m);
//     for(auto i :vt){
//         cout<<i[0]<<" "<<i[1]<<" "<<i[2]<<endl;
//     }
    
//     cout<<endl;
    int l=0,r=0;
    int ans=1e9;
    int temp=0;
    for(int i=0;i<n;i++){
        st.update(1,1,m-1,vt[i][1],vt[i][2]-1,1);
        //cout<<st.query(1,1,m-1,1,m-1)<<" "<<i<<endl;
        if(vt[i][2]==m)
            temp++;
        // for(auto i: st.tree)
        // cout<<i<<" ";
        while(st.tree[1] && l<=i && temp){
            ans = min(ans,vt[i][0]-vt[l][0]);
            
            st.update(1,1,m-1,vt[l][1],vt[l][2]-1,-1);
            if(vt[l][2]==m)
                temp--;
            //cout<<vt[i][0]-vt[l][0]<<" "<<i<<" "<<l<<endl;
            //cout<<st.query(1,1,m-1,1,m-1)<<endl;
            l++;
        }
    }
    cout<<ans<<endl;
}
