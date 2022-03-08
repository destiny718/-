#include<iostream>
using namespace std;

int division(int a,int b);
int max(int m[]){
    int max=0;
    for(int i=0;i<2010;i++){
        if(m[i]==0){
            break;
        }
        for(int j=1;j<2010;j++){
            if(m[i+j]==0){
                break;
            }
            if(max<division(m[i],m[i+j])){
                max=division(m[i],m[i+j]);
            }
        }
    }
    return max;
}
int division(int a,int b){
    if(a>b){
        int t=0;
        t=a;
        a=b;
        b=t;
    }
    if(a==0){
        return b;
    }
    else{
        return division(b%a,a);
    }
}
struct tsample{
    int n;
    int num[2010]={0};
};
int main(){
    int n;
    cin>>n;
    tsample *p=new tsample[n];
    for(int i=0;i<n;i++){
        cin>>p[i].n;
        for(int j=0;j<p[i].n;j++){
            cin>>p[i].num[j];
        }
    }
    for(int i=0;i<n;i++){
        cout<<max(p[i].num)<<endl;
    }
    delete []p;
    return 0;
}