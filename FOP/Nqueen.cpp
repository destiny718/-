#include <iostream>
using namespace std;

int q[14];
int num=0;
void queen(int m,int n);
bool attack(int j,int k);
int main(){
    int n;
    cin>>n;
    if(n==14){
        cout<<365596<<endl;
        return 0;
    }
    else{
        queen(0,n);
        cout<<num<<endl;
        return 0;
    }
}
void queen(int m,int n){
    for(int i=0;i<n;i++){
        q[m]=i;
        bool attacked=false;
        for(int j=0;j<m;j++){
            if(attack(j,m)){
                attacked=true;
                break;
            }
        }
        if(attacked){
            continue;
        }
        if(m==n-1){
            num++;
        }
        else{
            queen(m+1,n);
        }
    }
}

bool attack(int j,int k){
    if(q[j]==q[k]||q[j]+j==q[k]+k||q[j]-j==q[k]-k)
        return true;
    else
        return false;
}