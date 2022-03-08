#include<iostream>
using namespace std;

int main(){
	double X,Y,n;
	double PI=3.14159;
	int Z;
	int year=50;
	cin>>X;
	cin>>Y;
	n=PI*(X*X+Y*Y)*0.5;
	Z=(int)(n/year)+1;
	cout<<Z<<endl;
	return 0;
}
