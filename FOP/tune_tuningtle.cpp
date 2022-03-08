#include<iostream>
using namespace std;

int max(int a,int b);
int tune(int n,int *t,int Blevel,int Mlevel,int i);
int main(){
    int n,Blevel,Mlevel;
    cin>>n>>Blevel>>Mlevel;
    int *t=new int[n];
    for(int i=1;i<n+1;++i){
        cin>>t[i];
    }
    int i=1;
    cout<<tune(n,t,Blevel,Mlevel,i);
    delete []t;
}
int max(int a,int b){
    if(a>b)
        return a;
    else
        return b;
}
int tune(int n,int *t,int Blevel,int Mlevel,int i){
    int max0=0;
    if(Blevel>Mlevel||Blevel<0){
        return -1;
    }
    else if(i<n){
        max0= max(tune(n,t,Blevel+t[i],Mlevel,i+1),tune(n,t,Blevel-t[i],Mlevel,i+1));
        return max0;
    }
    else if(i==n){
        if(Blevel+t[i]<=Mlevel){
            return Blevel+t[i];
        }
        else if(Blevel-t[i]>=0){
            return Blevel-t[i];
        }
        else{
            return -1;
        }
    }
    else{
        return -1;
    }
}