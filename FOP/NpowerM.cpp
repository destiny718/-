#include <iostream>
#include <cmath>
using namespace std;

char *backthr(int x,int y);
char *frontthr(int x,int y);

struct nm{
    int x;
    int y;
};

int main(){
    int n;
    cin>>n;
    nm *p=new nm [n];
    for(int i=0;i<n;i++){
        cin>>p[i].x>>p[i].y;
    }
    for(int j=0;j<n;j++){
        cout<<frontthr(p[j].x,p[j].y)<<" "<<backthr(p[j].x,p[j].y)<<endl;
    }
    delete []p;
    return 0;
}

char *backthr(int x,int y){
    static char ans[4]={};
    int res=1;
    while(y>0){
        if(y%2==1){
        res=((res%1000)*(x%1000))%1000;
        }
        y=y/2;
        x=((x%1000)*(x%1000))%1000;
    }
    ans[0]=res/100+'0';
    ans[1]=(res%100-res%10)/10+'0';
    ans[2]=res%10+'0';
    return ans;
}

char *frontthr(int x,int y){
    static char ans[4]={};
    double m=x;
    double n=y;
    double res=n*log10(m);
    if(res>=3){    
        res-=floor(res);
        res=pow(10.0,res);
        int resw=floor(res*100);
        ans[0]=resw/100+'0';
        ans[1]=(resw %100-resw %10)/10+'0';
        ans[2]=resw %10+'0';
    }
    else{
        res=pow(10.0,res);
        int resw=res+0.1;
        ans[0]=resw/100+'0';
        ans[1]=(resw %100-resw %10)/10+'0';
        ans[2]=resw %10+'0';
    }
    return ans;
}