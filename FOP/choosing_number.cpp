#include<iostream>
using namespace std;

long long choosing(int n,int *t);
long long max(long long a,long long b);
int main(){
    int n;
    cin>>n;
    int *num=new int [n+1];
    for(int i=1;i<=n;i++){
        cin>>num[i];
    }
    cout<<choosing(n,num);
    delete []num;
    return 0;
}
long long max(long long a,long long b){
    if(a>b)
        return a;
    else
        return b;
}
long long choosing(int n,int *t){
    long long *a=new long long [n+1];
    long long *b=new long long [n+1];
    long long max0=0;
    long long max1=0;
    long long maxf=0;
    a[1]=t[1];   //选一
    b[1]=t[1];
    a[2]=t[1];
    b[2]=t[1];
    for(int i=3;i<=n;i++){
        a[i]=max(b[i-1],b[i-2])+t[i];
        b[i]=max(a[i-1],a[i-2]);
    }
    max0=max(a[n-1],b[n-1]);
    a[1]=0;  //不选1
    b[1]=0;
    a[2]=t[2];
    b[2]=0;
    for(int i=3;i<=n;i++){
        a[i]=max(b[i-1],b[i-2])+t[i];
        b[i]=max(a[i-1],a[i-2]);
    }
    max1=max(a[n],b[n]);
    maxf=max(max0,max1);
    delete []a;
    delete []b;
    return maxf;
}