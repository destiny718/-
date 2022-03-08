#include<iostream>
using namespace std;

int main(){
	int n,i,j;
	cin>>n;
	for(i=1;i<n;i++){
		for(j=i+1;j<n;j++){
			if((i+j)*(j-i+1)/2==n)     //计算首项加末项 的和乘项数除以2等于n 
		cout<<i<<" "<<j<<endl;
		}
	}
	return 0;
	
}
