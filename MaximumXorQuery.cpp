// question : https://www.codechef.com/problems/MCO16404
// solution help : https://www.codechef.com/viewsolution/25918174

#include<bits/stdc++.h>

using namespace std;

struct node{
    int count=0;
    struct node* vt[2];
    node()
    {
        for(int i=0;i<2;i++)
            vt[i] = NULL;
    }
};


class trie{
    public : void insert(node* A,int n,int ct){
        //A->count= (A->count+ct)%mod;
        int temp=0;
        for(int i=30;i>=0;i--){
            if(n&(1<<i)){
                if(A->vt[1]!=NULL){
                    A=A->vt[1];
                }else {
                    A->vt[1] = new node();
                    A=A->vt[1];
                }
                temp=1;
            }else {
                if(A->vt[0]!=NULL){
                    A=A->vt[0];
                }else {
                    A->vt[0] = new node();
                    A=A->vt[0];
                }
                temp=0;
            }
            //cout<<temp<<" ";
            // if(i==0){
            //     A->count= ct%mod;
            //     //cout<<A->count<<" "<<n<<endl;
            // }
        }
    }
    
    long long int search(node* A,int n){
        int t=0;
        for(int i=30;i>=0;i--){
            int temp =0;
            if(n&(1<<i)){
                if(A->vt[0]!=NULL){
                    temp=0;
                }else 
                    temp=1;
            }else {
                if(A->vt[1]!=NULL){
                    temp=1;
                }else 
                    temp=0;
            }
            t = t + (temp<<i);
            A = A->vt[temp];
            //cout<<t<<" "<<temp<<endl;
            // if(i==0){
            //     ans=A->count;
            // }
        }
        return t^n;
    }   
};


class segmentTree {
    private : vector<node* > v;
    
    public:
    segmentTree(int n){
        vector<node* > t(4*300009,NULL);
        v=t;
    }
    void combine(node* &root,node* root1,node* root2)
{ 
    if(root1==NULL && root2==NULL)return;
    root=new node();
    if(root1==NULL){root=root2;return;}
    if(root2==NULL){root=root1;return;}
    combine(root->vt[0],root1->vt[0],root2->vt[0]);
    combine(root->vt[1],root1->vt[1],root2->vt[1]);
}
    
    vector<long long int> merge(vector<long long int> a,vector<long long int> b){
        vector<long long int> p = {0,0};
        p[0] = max(a[0],b[0]);
        p[1] = min(a[1],b[1]);
        return p;
    }
    
    node* create(int l,int r,vector<int> &a){
        trie t;
        node* A = new node();
        for(int i=l;i<=r;i++){
            t.insert(A,a[i],1);
        }
        return A;
    }
    
    void build(int noe,int l,int r,int st,int ed,vector<int> &a){
        if(l>r){
            return;
        }
        if(l==r){
            v[noe] = create(l,r,a);
            return ;
        }
        int mid = (l+r)/2;
        build(2*noe,l,mid,st,ed,a);
        build(2*noe+1,mid+1,r,st,ed,a);
        node* A = new node();
        combine(A,v[2*noe],v[2*noe+1]);
        v[noe] = A;
    }
    
    long long int query(int node,int l,int r,int st,int ed,int f){
        trie t;
        if(l>=st && r<=ed){
            return t.search(v[node],f);
        }
        if(l>ed || st>r){
            return 0;
        }
        int mid = (l+r)/2;
        long long int a,b;
        a = query(2*node,l,mid,st,ed,f);
        b = query(2*node+1,mid+1,r,st,ed,f);
        return max(a,b);
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    vector<int> a(n+1,0);
    for(int i=0;i<n;i++){
        cin>>a[i+1];
    }
    segmentTree sg(n);
    sg.build(1,1,n,1,n,a);
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        int l,r,x;
        cin>>l>>r>>x;
        cout<<sg.query(1,1,n,l,r,x)<<endl;
    }
}



