#include<iostream>
using namespace std;

int noodlesx[1001][1001];
int noodlesy[1001][1001];
int noo[1001][1001]={0};


int max(int a,int b){
    if(a>b)
        return a;
    else
        return b;
}

int gan(int x,int y){
    for(int i=1;i<=x;++i){
        for(int j=1;j<=y;++j){
            noo[i][j]=max(noo[i-1][j]+noodlesy[i-1][j],noo[i][j-1]+noodlesx[i][j-1]);
        }
    }
    return noo[x][y];
}
int main(){
    noo[1][1]=0;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>noodlesx[i][j];
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>noodlesy[i][j];
        }
    }
    for(int i=0;i<=n;++i){
        noodlesx[i][0]=0;
        noodlesy[0][i]=0;
        noodlesy[i][0]=0;
        noodlesx[0][i]=0;
    }
    cout<<gan(n,m)<<endl;
    return 0;
}