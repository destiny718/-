#include<iostream>
using namespace std;

int main(){
    int n,temp;
    int sum=0;
    cin>>n;
    int *stock=new int [n+2];
    stock[0]=1000000000;
    stock[n+1]=1000000000;
    for(int i=1;i<=n;++i){
        cin>>stock[i];
    }
    for(int i=1;i<=n;++i){
        if(stock[i]<stock[i-1]&&stock[i]<stock[i+1]){
            temp=stock[i];
        }
        if((stock[i]>stock[i-1]&&stock[i]>stock[i+1]) || (i==n && stock[i]>stock[i-1])){
            sum+=(stock[i]-temp);
        }
    }
    cout<<sum<<endl;
    delete []stock;
    return 0;
}