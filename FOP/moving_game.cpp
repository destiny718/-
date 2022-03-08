#include<iostream>
using namespace std;

int main(){
    int n,temp,max,i=1;
    int num=0;
    cin>>n;
    int *move =new int [n+1];
    for(int i=1;i<=n;i++){
        cin>>move[i];
    }
    if(n==1){
        cout<<"0"<<endl;
        return 0;
    }
    while(i+move[i]<n){
        max=0;
        for(int j=i+1;j<=i+move[i];++j){
            if(move[j]+j>max){
                max=move[j]+j;
                temp=j;
            }
        }
        ++num;
        i=temp;
    }
    cout<<++num<<endl;
    delete []move;
    return 0;
}