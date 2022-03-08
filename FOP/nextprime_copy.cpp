#include<iostream>
using namespace std;

int main(){    
    int prime1[100000]={0};
    bool prime2[100000];
    bool pri0[1000001];
    int maxx[2];
    int minn[2];
    prime2[1]=false;
    long long L,U,max=0,min=100000000;
    cin>>L>>U;
    for(int i=2;i<100000;++i){
        prime2[i]=true;
    }
    for(int i=0;i<1000001;++i){
        pri0[i]=true;
    }
//素数筛法
    for (int i = 2; i * i <= U; i++){
        if (prime2[i]){
            for (long long j = i * i; j*j<= U; j += i){
                prime2[j] = false;
            }
        }
    }
//
    int tem=0;
    for(int i=2;i*i<=U;++i){
        if(prime2[i]){
            prime1[tem]=i;
            tem++;
        }
    }
    int temp=0;
    for(int i=L;i<=U;++i,++temp){
        for(int j=0;prime1[j]!=0;++j){
            if(i%prime1[j]==0&&i!=prime1[j]||i==1){
                pri0[temp]=false;
                break;
            }
        }
    }
    for(int i=0;i<=U-L;i++){
        if(pri0[i]){
            for(int j=i+1;j<=U-L;j++){
                if(pri0[j]){
                    if(j-i>max){
                        max=j-i;
                        maxx[0]=i+L;
                        maxx[1]=j+L;
                    }
                    if(j-i<min){
                        min=j-i;
                        minn[0]=i+L;
                        minn[1]=j+L;
                    }
                    break;
                }
            }
        }
    }
    //cout<<prime1[0]<<" "<<prime1[1]<<endl;
    if(max==0){
        cout<<"-1"<<endl;
    }
    else{
        cout<<minn[0]<<" "<<minn[1]<<endl;
        cout<<maxx[0]<<" "<<maxx[1]<<endl;
    }
    return 0;
}