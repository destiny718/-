#include<iostream>
using namespace std;

int main(){
	int a=1440;
	int b=60;
	int n,d,h,m;
	cin>>n;
	d=n/a;
	h=(n-a*d)/b;
	m=n-a*d-h*b;
	cout<<d<<" "<<h<<" "<<m;
	return 0;
}
