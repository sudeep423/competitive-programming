// question: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/substring-xor-bc997d8a/

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
        A->count= A->count+ct ;
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
            A->count= A->count+ct;
        }
    }
    
    vector<long long int> searchMore(node* A,int n,int p){
        long long int t=0,f=0;
        for(int i=30;i>=0;i--){
            if((n&(1<<i)) == (p&(1<<i))){
                if(p&(1<<i)){
                    A=A->vt[0];
                }else {
                    if(A->vt[1]){
                        t = t + A->vt[1]->count;
                        //cout<<"aaa"<<endl;
                    }
                    A=A->vt[0];
                    //cout<<"aaa"<<endl;
                }
            }else {
                if(!(p&(1<<i))){
                    A=A->vt[1];
                }else {
                    if(A->vt[0]){
                        t = t + A->vt[0]->count;
                        //cout<<"aaa"<<endl;
                    }
                    A=A->vt[1];
                    //cout<<"aaa"<<endl;
                }
            }
            //cout<<t<<" "<<f<<"temp"<<endl;
            if(i==0 && A){
                f=A->count;
            }
            if(!A)
                return { t ,f };
        }
        return { t,f};
    }   
};



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long int n,k;
    cin>>n>>k;
    vector<int> a(n+1,0);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int l=0,r=1<<21;
    
    vector<long long int > v;
    node* A = new node();
    int g=0;
    trie t;
    t.insert(A,0,1);
    for(int i=0;i<n;i++){
        g = g^a[i];
        t.insert(A,g,1);
            //cout<<g<<endl;
    }
    
    while(l<=r){
        long long int p=0 ,q=0,g=0;
        int mid=(l+r)/2;
        v = t.searchMore(A,mid,0);
        p = v[0]+p;
        q = v[0] + v[1]+q;
        for(int i=0;i<n;i++){
            g = g^a[i];
            v = t.searchMore(A,mid,g);
            p = v[0]+p;
            q = v[0] + v[1]+q;
            //cout<<g<<endl;
        }
        p=p/2;
        q=q/2;
       //cout<<p<<" | "<<q<<" "<<mid<<endl;
        
        if(p<k && q>=k){
            cout<<mid<<endl;
            return 0;
        }else {
            if(q>=k){
                l=mid+1;
            }else 
                r=mid-1;
        }
        //cout<<l<<" "<<r<<endl;
    }
    
    return 0;
}



