#include<iostream>
using namespace std;

int main(){
	int K;
	int n;
	double sum=0;
	cin>>K;
	for(n=1;;n++){
		sum=sum+(1.0/n);
	if(sum>K)
		break;
	}
	cout<<n<<endl;
	return 0;
}
