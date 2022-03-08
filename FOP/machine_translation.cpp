#include<iostream>
using namespace std;

int main(){
    int m=0;
    int n=0;
    int times=0;
    int answer;
    cin>>m>>n;
    int num[25]={-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-24,-25};
    for(int i=0;i<n;i++){
        cin>>num[i];
    }
    for(int i=0;i<n;i++){
        for(int j=1;j<=m;j++){
            if(num[i]==num[i+j]){
                for(int k=i+j;k<=24;k++){
                    num[k]=num[k+1];
                }
                times++;
                i=0;
                j=0;
            }
        }
    }
    answer=n-times;
    cout<<answer<<endl;
    return 0;
}