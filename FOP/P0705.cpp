#include<iostream>
using namespace std;

int intersection(int a[],int b[],int c[],int n,int m){
    int temp=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(b[j]>a[n-1]){
                break;
            }
            if(a[i]==b[j]){
                c[temp]=a[i];
                temp++;
            }
        }
        if(a[i]>b[m-1]){
            break;
        }
    }
    return temp;
}

int unionsection(int a[],int b[],int c[],int n,int m){
    int num=0;
    for(int i=0;i<n;i++){
        c[i]=a[i];
    }
    for(int i=0;i<m;i++){
        if(b[i]<a[0]){
            for(int l=m+n-1;l>=1;l--){
                c[l]=c[l-1];
            }
            c[0]=b[i];
            num++;
        }
    for(int j=0;j<n-1;j++){
        if(b[i]>a[j]&&b[i]<a[j+1]){
            for(int l=m+n-1;l>=j+2;l--){
                c[l]=c[l-1];
            }
            c[j+1]=b[i];
            num++;
            }
        }
        if(b[i]>a[n-1]){
            c[n+num]=b[i];
            num++;
        }
    }
    return n+num;
}

int complementarysection(int a[],int b[],int c[],int n,int m){
    int tempt=0;
    for(int i=0;i<n;i++){
        c[i]=a[i];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i]==b[j]){
                for(int l=i;l<m+n-1;l++){
                    c[l-tempt]=c[l+1-tempt];
                }
                tempt++;
            }
        }
    }
    return tempt;
}

int main(){
    int n,m;
    int aa,bb,cc;
    int uni[2000]={0};
    int itr[2000]={0};
    int com[2000]={0};
    cin>>n;
    int *p=new int[n];
    for(int i=0;i<n;i++){
        cin>>p[i];
    }
    cin>>m;
    int *q=new int[m];
    for(int i=0;i<m;i++){
        cin>>q[i];
    }
    aa=unionsection(p,q,uni,n,m);
    bb=intersection(p,q,itr,n,m);
    cc=complementarysection(p,q,com,n,m);
    for(int i=0;i<=n+m;i++){
        if(itr[i]==0){
            cout<<endl;
            break;
        }
        cout<<itr[i]<<' ';
    }
    for(int i=0;i<=n+m;i++){
        if(uni[i]==0){
            cout<<endl;
            break;
        }
        cout<<uni[i]<<' ';
    }
    for(int i=0;i<=n+m;i++){
        if(com[i]==0){
            cout<<endl;
            break;
        }
        cout<<com[i]<<' ';
    }
    delete []p;
    delete []q;
    return 0;
}