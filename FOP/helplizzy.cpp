#include<iostream>
#include<cstring>
using namespace std;

void lizzy(int a,char *m,int n,int start);

int main(){
    char num[20]={0};
    cin>>num;   
    int n=strlen(num);
    if(num[0]=='0'){
        cout<<"NONE"<<endl;
        return 0;
    }
    for(int i=0;i<n-1;++i){
        if(num[i]>'2'&&num[i+1]=='0'){
            cout<<"NONE"<<endl;
            return 0;
        }
    }
    lizzy(1,num,n,0);
    lizzy(2,num,n,0);
    return 0;
}

void lizzy(int a,char *m,int n,int start){
    if((a==2&&start==n-1)||m[start]=='0'){
        return;
    }
    else if(start==n){
        cout<<m<<" ";
        return;
    }
    else{
        if(a==1){
            m[start]+=48;
            lizzy(1,m,n,start+1);
            lizzy(2,m,n,start+1);
        }
        if(a==2){
            int temp=0;
            temp=(m[start]-'0')*10;
            if(m[start+1]+temp+48>'z'){
                return;
            }
            m[start+1]+=temp+48;
            for(int i=start;i<n;++i){
                m[i]=m[i+1];
            }
            lizzy(1,m,n-1,start+2);
            lizzy(2,m,n-1,start+2);
        }
    }
}