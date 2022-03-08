#include<iostream>
using namespace std;

int main(){
    int n,Blevel,Mlevel;
    cin>>n>>Blevel>>Mlevel;
    int *num=new int [n+1];
    bool t[51][1001]={false};
    for(int i=1;i<=n;i++){
        cin>>num[i];
    }
    t[0][Blevel]=true;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=Mlevel;j++){
            if(t[i-1][j]&&j+num[i]<=Mlevel){
                t[i][j+num[i]]=true;
            }
            if(t[i-1][j]&&j-num[i]>=0){
                t[i][j-num[i]]=true;
            }
        }
    }
    for(int i=Mlevel;i>=0;i--){
        if(t[n][i]){
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
    delete []num;
}