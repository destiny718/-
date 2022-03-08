#include<iostream>
using namespace std;

int main(){
	int n,a,i,j,k,length=0;
	cin>>n;
	a=2*n;
	int num[2002]={0};
	for(i=1;i<=a;i++){
		cin>>num[i];
	}
	for(j=1;j<a;j=j+2){
		for(k=1;k<a;k=k+2){
			if(num[j]>num[k]&&num[j]<num[k+1]){
				num[j]=num[k+1];
			}
		}
	}
	for(j=2;j<a;j=j+2){
		for(k=2;k<=a;k=k+2){
			if(num[j]>num[k-1]&&num[j]<num[k]){
				num[j]=num[k-1];
			}
			if(num[k]<num[k-1]){
				num[k-1]=num[k];
			}
		}
			if(num[j]<num[j-1]){
				num[j-1]=num[j];
			}
	}
	for(j=1;j<a;j+=2){
		length+=num[j+1]-num[j];
	}
	cout<<length<<endl;
	return 0;
}
