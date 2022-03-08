#include<iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    int cha[9]={0};
    cha[0]=n/10000;
    cha[1]=(n-cha[0]*10000)/5000;
    cha[2]=(n-cha[0]*10000-cha[1]*5000)/1000;
    cha[3]=(n-cha[0]*10000-cha[1]*5000-cha[2]*1000)/500;
    cha[4]=(n-cha[0]*10000-cha[1]*5000-cha[2]*1000-cha[3]*500)/200;
    cha[5]=(n-cha[0]*10000-cha[1]*5000-cha[2]*1000-cha[3]*500-cha[4]*200)/100;
    cha[6]=(n-cha[0]*10000-cha[1]*5000-cha[2]*1000-cha[3]*500-cha[4]*200-cha[5]*100)/50;
    cha[7]=(n-cha[0]*10000-cha[1]*5000-cha[2]*1000-cha[3]*500-cha[4]*200-cha[5]*100-cha[6]*50)/20;
    cha[8]=(n-cha[0]*10000-cha[1]*5000-cha[2]*1000-cha[3]*500-cha[4]*200-cha[5]*100-cha[6]*50-cha[7]*20)/10;
    for(int i=0;i<=8;i++){
        cout<<cha[i]<<" ";
    }
    return 0;
}