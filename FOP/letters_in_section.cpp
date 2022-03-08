#include<iostream>
using namespace std;

int num[27];
void check(char *S,int xx,int yy){
    char let[27];
    let[1]='a';
    for(int i=2;i<=26;++i){
        let[i]=let[i-1]+1;
    }
    for(int i=xx;i<=yy;++i){
        for(int j=1;j<=26;++j){
            if(S[i]==let[j]){
                num[j]++;
            }
        }
    }
    for(int i=1;i<=26;++i){
        if(num[i]!=0){
            cout<<let[i]<<":"<<num[i]<<" ";
        }
    }
    for(int i=1;i<=26;++i){
        num[i]=0;
    }
}
int main(){
    char S[1001]={0};
    int Q;
    cin>>S;
    cin>>Q;
    int xx[101]={0};
    int yy[101]={0};
    for(int i=0;i<Q;++i){
        cin>>xx[i]>>yy[i];
    }
    for(int i=0;i<Q;++i){
        check(S,xx[i],yy[i]);
        cout<<endl;
    }
    return 0;
}