#include<iostream>
using namespace std;

int main(){
    int x,y,max=0,min=100000000;
    int maxx[2];
    int minn[2];
    cin>>x>>y;
    bool *prime=new bool [y+1];
    prime[1]=false;
//素数筛法
    for (int i = 2; i <= y; i++){
        prime[i] = true;
    }
    for (int i = 2; i * i <= y; i++){
        if (prime[i]){
            for (int j = i * i; j <= y; j += i){
                prime[j] = false;
            }
        }
    }
//
    for(int i=x;i<=y;i++){
        if(prime[i]){
            for(int j=i+1;j<=y;j++){
                if(prime[j]){
                    if(j-i>max){
                        max=j-i;
                        maxx[0]=i;
                        maxx[1]=j;
                    }
                    if(j-i<min){
                        min=j-i;
                        minn[0]=i;
                        minn[1]=j;
                    }
                    break;
                }
            }
        }
    }
    if(max==0){
        cout<<"-1"<<endl;
    }
    else{
        cout<<minn[0]<<" "<<minn[1]<<endl;
        cout<<maxx[0]<<" "<<maxx[1]<<endl;
    }
    delete []prime;
    return 0;
}