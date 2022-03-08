#include <iostream>
using namespace std;

int divide(int n,int k);

int main(){
    int n,k;
    int answer;
    cin>>n>>k;
    answer=divide(n,k);
    cout<<answer<<endl;
}
int divide(int n,int k){
    if(n==k|k==1){
        return 1;
    }
    else if(n<k){
        return 0;
    }
    else{
        return divide(n-1,k-1)+divide(n-k,k);
    }
}