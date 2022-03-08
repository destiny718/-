#include<iostream>
using namespace std;

int num[6]={0};
void cook(int *m);
int main(){
    int dishes[5]={0};
    for(int i=1;i<5;++i){
        cin>>dishes[i];
    }
    cook(dishes);
    return 0;
}

void cook(int *m){
    if(m[1]>=2&&m[2]>=1&&m[4]>=2){
        m[1]-=2;
        m[2]-=1;
        m[4]-=2;
        ++num[1];
        cook(m);
    }
    else if(m[1]>=1&&m[2]>=1&&m[3]>=1&&m[4]>=1){
        m[1]-=1;
        m[2]-=1;
        m[3]-=1;
        m[4]-=1;
        ++num[2];
        cook(m);
    }
    else if(m[3]>=2&&m[4]>=1){
        m[3]-=2;
        m[4]-=1;
        ++num[3];
        cook(m);
    }
    else if(m[2]>=3){
        m[2]-=3;
        ++num[4];
        cook(m);
    }
    else if(m[1]>=1&&m[4]>=1){
        m[1]-=1;
        m[4]-=1;
        ++num[5];
        cook(m);
    }
    else{
        for(int i=1;i<=5;++i){
            cout<<num[i]<<endl;
        }
        return;
    }
}