#include<iostream>
using namespace std;

long long getmax(long long *m,int n);
long long getsum(long long *m,int n);
int getpart(long long *m,int n,long long max0);

int main(){
    int n,m;
    long long min=0,max=0,mid=0,req=0;
    long long num[100001]={0};
    cin>>n>>m;
    for(int i=0;i<n;++i){
        cin>>num[i];
    }
    min=getmax(num,n);
    max=getsum(num,n);
    while(min<max){
        mid=(min+max)/2;
        req=getpart(num,n,mid);
        if(req<=m){
            max=mid;
        }
        else{
            min=mid+1;
        }
    }
    cout<<min<<endl;
    return 0;
}

long long getmax(long long *m,int n){
    long long max=0;
    for(int i=0;i<n;++i){
        if(m[i]>max){
            max=m[i];
        }
    }
    return max;
}

long long getsum(long long *m,int n){
    long long sum=0;
    for(int i=0;i<n;++i){
        sum+=m[i];
    }
    return sum;
}

int getpart(long long *m,int n,long long max0){
    int num=0;
    long long sum=0;
    for(int i=0;i<n;++i){
        sum+=m[i];
        if(sum>max0){
            num++;
            sum=0;
            i--;
        }
    }
    if(sum<=max0){
        num++;
    }
    return num;
}