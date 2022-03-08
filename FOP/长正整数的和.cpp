#include<iostream>
using namespace std;

int main(){
	int i,n,a,j;
	int num1[100]={0};
	int num2[100]={0};
	char num11[100]={0};
	char num22[100]={0};
	int sum[100]={0};
	cin>>num11;
	cin>>num22;
	for(i=0;i<=99;i++){
		if(num11[i]-'0'<0)
		continue;
		num1[99-i]=num11[i]-'0';
	} 
	for(i=0;i<=99;i++){
		if(num22[i]-'0'<0)
		continue;
		num2[99-i]=num22[i]-'0';
	}
	for(i=99;i>=0;i--){
		a=num1[i]+num2[i]+sum[i];
		if(a>=10){
			a=a%10;
			sum[i]=a;
			if(i=0)
			break;
			else
			sum[i-1]=sum[i-1]+1;
		}
		else
		sum[i]=a;
	}
	for(i=0;i<=99;i++){
		if(sum[i]!=0){
			for(j=99;j>=i;j--){
				cout<<sum[j];
			}
			break;
		}
	}
		
	return 0;
}
