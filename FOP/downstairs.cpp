#include<iostream>
using namespace std;

int down(int n){
    switch(n){
        case 1:return 1;
        case 2:return 2;
        case 3:return 4;
        default:return (down(n-1)+down(n-2)+down(n-3));
    }
}
int main(){
    int n;
    cin>>n;
    if(n<=3||n>20){
        cout<<0<<endl;
    }
    else{
        cout<<down(n)<<endl;
    }
    return 0;
}