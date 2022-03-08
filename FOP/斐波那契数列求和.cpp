#include<iostream>
using namespace std;

int fib[10000000];
int main(){
	int n;
	int sum;
	cin>>n;
	fib[1]=fib[2]=1;
	fib[1]=fib[1]%1000000007;
	fib[2]=fib[2]%1000000007;
	if(n==1)
		cout<<fib[1]<<endl;
		else if(n==2){
			sum=fib[1]+fib[2];
			cout<<sum<<endl;
		}
	else{
	sum=2;
	for(int i=3;i<=n;i++){
		fib[i]=fib[i-1]+fib[i-2];
		fib[i]=fib[i]%1000000007;
		if(sum<=fib[i]){
			sum=sum+fib[i];
			sum=sum%1000000007;
			}
		else{
		sum=sum-fib[i];
			sum=sum%1000000007;
			}
	}
	cout<<sum<<endl;
}
	return 0;
}
	

