#include<iostream>
using namespace std;

int minus1[4]={0};
void sort_max(int n[]);
void sort_min(int n[]);
int *number(int n[],int m[]);
int times(int m[]);

void sort_max(int n[]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3-i;j++){
            if(n[j]<n[j+1]){
                int t=0;
                t=n[j];
                n[j]=n[j+1];
                n[j+1]=t;
            }
        }
    }
}
void sort_min(int n[]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3-i;j++){
            if(n[j]>n[j+1]){
                int t=0;
                t=n[j];
                n[j]=n[j+1];
                n[j+1]=t;
            }
        }
    }
}
int *number(int n[],int m[]){
    for(int i=3;i>=0;i--){
        minus1[i]=n[i];
    }
    for(int i=3;i>=0;i--){
        if(minus1[i]<m[i]){
            minus1[i]=10+minus1[i]-m[i];
            minus1[i-1]--;
        }
        else{
            minus1[i]=minus1[i]-m[i];
        }
    }
    return minus1;
}
int times(int m[]){
    static int ftime=0;
    static int minus1[4]={0};
    static int num_max[4]={0};
    static int num_min[4]={0};
    static int *number1;
    for(int i=0;i<=3;i++){
        num_max[i]=m[i];
        num_min[i]=m[i];
    }
    sort_max(num_max);
    sort_min(num_min);
    number1=number(num_max,num_min);
    ftime++;
    if(number1[0]==6&&number1[1]==1&&number1[2]==7&&number1[3]==4){
        return ftime;
    }
    else{
        return times(number1);
    }
}
int main(){
    int num[4];
    int numm;
    cin>>numm;
    num[0]=numm/1000;
    num[1]=numm/100-num[0]*10;
    num[2]=numm/10-num[0]*100-num[1]*10;
    num[3]=numm-num[0]*1000-num[1]*100-num[2]*10;
    if(num[0]==6&&num[1]==1&&num[2]==7&&num[3]==4){
        cout<<0<<endl;
    }
    else{
        cout<<times(num)<<endl;
    }
    return 0;
}