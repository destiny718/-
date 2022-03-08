#include<iostream>
using namespace std;

int maxsum(int n,int *t,int *l);
int main(){
    int leng;
    cin>>leng;
    int *sub=new int [leng+1];
    int *l=new int [leng+1];
    for(int i=1;i<=leng;i++){
        cin>>sub[i];
    }
    cout<<maxsum(leng,sub,l);
    delete []sub;
    delete []l;
    return 0;
}
int max(int a,int b){
    if(a>b)
        return a;
    else
        return b;
}
int maxsum(int n,int *t,int *l){
    bool *check1=new bool [n+2];
    int temp1=0;
    int cc=1;
    int max0=-1000000;
    check1[n+1]=false;
    for(int i=1;i<=n;i++){
        l[i]=t[i];
    }
    for(int i=1;i<=n;i++){
        if(t[i]>0){
            check1[i]=true;
        }
        else{
            check1[i]=false;
        }
    }
    for(int i=1;i<=n;i++){
        if(check1[i]){
            for(int j=i;j<=n;j++){
                if(check1[j]&&!check1[j+1]){
                    if(j>=n-2||t[j+1]+t[j+2]<0){
                        for(int k=i;k<=j;k++){
                        temp1+=t[k];
                        }
                    l[j]=max(l[j],temp1);
                    temp1=0;
                    }
                    else{
                        continue;
                    }
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(l[i]>max0){
            max0=l[i];
        }
    }
    delete []check1;
    return max0;
}