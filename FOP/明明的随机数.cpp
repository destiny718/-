#include<iostream>
using namespace std;

void swap1(int &x,int &y){
	int t;
	t=x;
	x=y;
	y=t;
}
int main(){
	int N,i,j,k,rep,time=0;
	int num[102]={0};
	cin>>N;
	for(i=1;i<=N;i++){
		cin>>num[i];
	}
	for(i=1;i<=N;i++){
		rep=num[i];
		for(j=i+1;j<=N-time;j++){
			if(rep==num[j]){
				for(k=j;k<=N-time;k++){
					num[k]=num[k+1];
				}
				time++;
				j--;
			}
		}
	}
	int final;
	final=N-time;
	cout<<final<<'\n';
	for(i=1;i<=final;i++){
		for(j=1;j<=final-i;j++){
			if(num[j]>num[j+1]){
				swap1(num[j],num[j+1]);
			}
		}
	}
	for(i=1;i<=final;i++){
		cout<<num[i]<<' ';
	}
	return 0;
}
