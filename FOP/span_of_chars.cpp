#include<iostream>
using namespace std;

void span(char *p,int x,int y,int z,int len);

int main(){
    int p1,p2,p3;
    cin>>p1>>p2>>p3;
    char pack[1001]={};
    cin>>pack;
    int len=0;
    while(pack[len]){
        len++;
    }
    span(pack,p1,p2,p3,len);
    cout<<pack<<endl;
    return 0;
}

void span(char *p,int x,int y,int z,int len){
    int i=0;
    int num;
    while(p[i]){
        if(p[i]=='-'&&p[i-1]<p[i+1]&&p[i+1]-p[i-1]<25){
            num=p[i+1]-p[i-1];
            if(num==1){
                for(int j=i;;j++){
                    if(!p[j+1]){
                        break;
                    }
                    p[j]=p[j+1];
                }
                len--;
            }
            else if(num==2&&y==1){
                if(x==3)
                    p[i]='*';
                else if(p[i-1]<='9'&&x!=3)
                    p[i]=p[i-1]+1;
                else if(p[i-1]>='a'&&x==1){
                        p[i]=p[i-1]+1;
                }
                else if(p[i-1]>='a'&&x==2){
                        p[i]=p[i-1]-31;
                }
            }
            else{
                for(int j=len;j>i+1;j--){
                    p[j+y*(num-1)-2]=p[j-1];
                }
                if(x==3){
                    for(int j=i;j<=i+y*(num-1)-1;j++){
                        p[j]='*';
                    }
                }
                else if(p[i-1]<='9'&&x!=3){
                    if(z==1){
                        p[i]=p[i-1]+1;
                        for(int j=i+y;j<i+y-1;j++){
                            p[j+1]=p[j];
                        }
                        for(int j=i;j<=i+y*(num-1)-1;j=j+y){
                            p[j]=p[j-1]+1;
                            for(int k=j;k<j+y-1;k++){
                                p[k+1]=p[k];
                            }
                        }
                    }
                    if(z==2){
                        p[i]=p[i+y*(num-1)]-1;
                        for(int j=i;j<i+y-1;j++){
                            p[j+1]=p[j];
                        }
                        for(int j=i+y;j<=i+y*(num-1)-1;j=j+y){
                            p[j]=p[j-1]-1;
                            for(int k=j;k<j+y-1;k++){
                                p[k+1]=p[k];
                            }
                        }
                    }
                }
                else if(p[i-1]>='a'&&x!=3&&p[i-1]<='z'){
                    if(x==1){
                        if(z==1){
                            p[i]=p[i-1]+1;
                            for(int j=i;j<i+y-1;j++){
                                p[j+1]=p[j];
                            }
                            for(int j=i+y;j<=i+y*(num-1)-1;j=j+y){
                                p[j]=p[j-1]+1;
                                for(int k=j;k<j+y-1;k++){
                                    p[k+1]=p[k];
                                }
                            }
                        }
                        if(z==2){
                            p[i]=p[i+y*(num-1)]-1;
                            for(int j=i;j<i+y-1;j++){
                                p[j+1]=p[j];
                            }
                            for(int j=i+y;j<=i+y*(num-1)-1;j=j+y){
                                p[j]=p[j-1]-1;
                                for(int k=j;k<j+y-1;k++){
                                    p[k+1]=p[k];
                                }
                            }
                        }
                    }
                    if(x==2){
                        if(z==1){
                            p[i]=p[i-1]-31;
                            for(int j=i;j<i+y-1;j++){
                                p[j+1]=p[j];
                            }
                            for(int j=i+y;j<=i+y*(num-1)-1;j=j+y){
                                p[j]=p[j-1]+1;
                                for(int k=j;k<j+y-1;k++){
                                    p[k+1]=p[k];
                                }
                            }
                        }
                        if(z==2){
                            p[i]=p[i+y*(num-1)]-33;
                            for(int j=i;j<i+y-1;j++){
                                p[j+1]=p[j];
                            }
                            for(int j=i+y;j<=i+y*(num-1)-1;j=j+y){
                                p[j]=p[j-1]-1;
                                for(int k=j;k<j+y-1;k++){
                                    p[k+1]=p[k];
                                }
                            }
                        }
                    }
                }
                len=len+y*(num-1)-1;
            }
        }
        i++;
    }
}