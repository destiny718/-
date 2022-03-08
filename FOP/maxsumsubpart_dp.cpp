#include<iostream>
using namespace std;

int max(int a,int b){
    if(a>b)
        return a;
    else
        return b;
}
int main(){
    int n,sum=0;
    cin>>n;
    int *num=new int [n+1];
    int *t=new int [n+1];
    for(int i=1;i<=n;i++){
        cin>>num[i];
    }
    for(int i=1;i<=n;i++){
        if(i==1){
            t[i]=num[i];
        }
        else{
            t[i]=max(num[i],t[i-1]+num[i]);
            sum=max(sum,t[i]);
        }
    }
    cout<<sum<<endl;
    delete []num;
    delete []t;
    return 0;
}