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
}
int max(int a,int b){
    if(a>b)
        return a;
    else
        return b;
}
int maxsum(int n,int *t,int *l){
    bool check1=false;
    bool check2=true;
    int temp1=0;
    int cc=1;
    int dd=1;
    int max0=-1000000;
    while(!check1){
        if(t[cc]>0){
            check1=true;
        }
        cc++;
    }
    while(check2){
        if(t[dd]<0){
            check2=false;
        }
        dd++;
    }
    if(!check1){
        for(int i=1;i<=n;i++){
            if(t[i]>max0){
                max0=t[i];
            }
        }
        return max0;
    }
    else if(check2){
        for(int i=1;i<=n;i++){
            if(t[i]>max0){
                max0=t[i];
            }
        }
        return max0;
    }
    else{
        for(int i=1;i<=n;i++){
            l[i]=t[i];
        }
        for(int i=1;i<=n;i++){
            if(t[i]>0){
                for(int j=i;j<=n;j++){
                    if(t[j]>0){
                        for(int k=i;k<=j;k++){
                            temp1+=t[k];
                        }
                        l[j]=max(l[j],temp1);
                        temp1=0;
                    }
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
}