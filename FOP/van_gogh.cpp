#include<iostream>
using namespace std;
int think[50001][21]={0};
int main(){
    int n,m,temp=1,num=1,times=0;
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        num=num<<1;
    }
    num-=1;
    /*int **think=new int *[n+1];
    for(int i=0;i<=n;++i){
        think[i]=new int [m+1];
    }*/
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>think[i][j];
        }
    }
    /*for(int i=1;i<=n;++i){
        think[i][0]=0;
    }*/
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j,temp=temp<<1){
            think[i][0]+=think[i][j]*temp;
        }
        temp=1;
    }
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
            if(think[i][0]+think[j][0]==num){
                times++;
            }
        }
    }
    cout<<times<<endl;
    return 0;
}