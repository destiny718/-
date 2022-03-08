#include<iostream>
using namespace std;

int l[1000];
int subseq(int n,int *t);
int main(){
    int leng;
    cin>>leng;
    int sub[1001]={0};
    for(int i=1;i<=leng;i++){
        cin>>sub[i];
    }
    cout<<subseq(leng,sub);
    return 0;
}
int max(int a,int b){
    if(a>b)
        return a;
    else
        return b;
}
int subseq(int n,int *t){
    int max0;
    for(int i=1;i<=n;i++){
        l[i]=1;
    }
    max0=l[1];
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            if(t[i]<t[j]){
                l[j]=max(l[i]+1,l[j]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(l[i]>max0){
            max0=l[i];
        }
    }
    return max0;
}