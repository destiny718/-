#include<iostream>
using namespace std;

struct Location{
    int x;
    int y;
    int xlength;
    int ylength;
};
int main(){
    int n=0;
    cin>>n;
    int xx,yy;
    Location m[10000];
    for(int i=0;i<n;i++){
        cin>>m[i].x>>m[i].y>>m[i].xlength>>m[i].ylength;
    }
    cin>>xx>>yy;
    for(int i=n-1;i>=0;i--){
        if(xx>=m[i].x&&yy>=m[i].y&&xx<=m[i].x+m[i].xlength&&yy<=m[i].y+m[i].ylength){
            cout<<i+1<<endl;
            break;
        }
        if(i==0){
            cout<<"-1"<<endl;
        }
    }
    return 0;
}