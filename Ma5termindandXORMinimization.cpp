//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/ma5termind-and-xor-minimization/


#include<bits/stdc++.h>

using namespace std;
long long int mod=1e9+7;
struct node{
    int count=0;
    struct node* vt[2];
    node()
    {
        for(int i=0;i<2;i++)
            vt[i] = NULL;
    }
};

int ans=0,t=0;

class trie{
    public : void insert(node* A,int n,int ct){
        A->count= (A->count+ct)%mod;
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
            if(i==0){
                A->count= ct%mod;
                //cout<<A->count<<" "<<n<<endl;
            }
        }
    }
    
    void search(node* A,int n){
        for(int i=30;i>=0;i--){
            int temp =0;
            if(n&(1<<i)){
                if(A->vt[1]!=NULL){
                    temp=1;
                }else 
                    temp=0;
            }else {
                if(A->vt[0]!=NULL){
                    temp=0;
                }else 
                    temp=1;
            }
            t = t + (temp<<i);
            A = A->vt[temp];
            //cout<<t<<" "<<temp<<endl;
            if(i==0){
                ans=A->count;
            }
        }
    }
    
    
    
};

int main() {
     ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    trie tt;
    vector<int> vt(n,0);
    for(int i=0;i<n;i++){
        cin>>vt[i];
    }
    node *A = new node();
    vector<int> dp(1e5+10,0);
    dp[vt[0]]=1;
    for(int i=1;i<n;i++){
        for(int j=100001;j>=vt[i];j--){
            dp[j] = (dp[j]+dp[j-vt[i]])%mod;
        }
        dp[vt[i]]=(dp[vt[i]]+1)%mod;
    }
    for(int i=0;i<100001;i++){
        
        if(dp[i]){
            //cout<<i<<endl;
            tt.insert(A,i,dp[i]);
        }
    }
    int q=0;
    cin>>q;
    for(int i=0;i<q;i++){
        int a;
        cin>>a;
        ans=0,t=0;
        tt.search(A,a);
        cout<<t<<" "<<ans<<endl;
    }
}
