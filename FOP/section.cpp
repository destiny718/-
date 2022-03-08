#include<iostream>
using namespace std;

struct Package{
    int left;
    int righ;
};

int main(){
    int n,m,temp=0,num=1;
    cin>>n>>m;
    int *max=new int [n+1];
    Package *sec =new Package [n+1];
    bool *check=new bool [n+1];
    for(int i=1;i<=n;++i){
        cin>>sec[i].left>>sec[i].righ;
    }
    for(int i=1;i<=n;++i){
        if(sec[i].left==1&&sec[i].righ>max[0]){
            max[0]=sec[i].righ;
        }
    }
    for(int j=1;max[j-1]<m;++j){
        if(max[j-1]>=m){
            break;
        }
        num++;
        for(int i=1;i<=n;++i){
            if(sec[i].left<=max[j-1]&&sec[i].righ>max[j-1]&&sec[i].righ>max[j]){
                max[j]=sec[i].righ;
                check[j]=true;
            }
        }
        if(!check[j]){
            cout<<"-1"<<endl;
            return 0;
        }
    }
    cout<<num<<endl;
    delete []sec;
    delete []max;
    delete []check;
    return 0;
}
