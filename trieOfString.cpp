#include<bits/stdc++.h>

using namespace std;

struct node{
    int count=1;
    struct node* vt[26];
    node()
    {
        for(int i=0;i<26;i++)
            vt[i] = NULL;
    }
};

int ans=1;

class trie{
    public : void insert(node* A,string s){
        for(auto i: s){
            if(A->vt[i-'a']){
                A = A->vt[i-'a'];
                A->count++;
            }else {
                ans++;
                A->vt[i-'a'] = new node();
                A = A->vt[i-'a'];
            }
        }
    }
};

int main() {
    int n;
    cin>>n;
    trie t;
    node *A = new node();
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        t.insert(A,s);
    }
    cout<<ans<<endl;
}
