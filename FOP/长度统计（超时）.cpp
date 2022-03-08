#include<iostream>
using namespace std;

int main(){
	int n,a,i,j,k,l,max,min,length=0;
	cin>>n;
	a=2*n;
	int num[2002]={0};
	for(i=1;i<=a;i++){
		cin>>num[i];
	}
	min=num[1];
	max=num[2];
	for(j=1;j<=a;j=j+2){
		if(min>num[j]){
			min=num[j];
		}
		if(max<num[j+1]){
			max=num[j+1];
		}
	}
	for(k=min;k<=max;k++){
		for(l=1;l<a;l=l+2){
			if(k>=num[l]&&k<num[l+1]){
				length++;
				break;
			}
		}
	}
	cout<<length<<endl;
	return 0;
}
