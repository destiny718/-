#include<iostream>
using namespace std;

bool checkprime(int n){
	int i;
	for(i=2;i*i<=n;i++){
		if(n%i==0){
			return false;
		}
	}
	return true;
}
bool checkpalindromic(int n){
	int i;
	if(n<10){
		return true;
	}
	if(n==11){
		return true;
	}
	if(n>100&&n<999){
		int a,b,c;
		a=n%10;
		if(a%2==0)
			return false;
		b=((n%100)-a)/10;
		c=(n-10*b-a)/100;
		if(a==c)
			return true;
		else
			return false;
	}
	if(n>10000&&n<99999){
		int a,b,c,d,e;
		a=n%10;
		if(a%2==0){
			return false;
		}
		b=((n%100)-a)/10;
		c=(n%1000-10*b-a)/100;
		d=(n%10000-100*c-10*b-a)/1000;
		e=(n-1000*d-100*c-10*b-a)/10000;
		if(a==e&&b==d){
			return true;
		}
		else
			return false;
	}
	if(n>1000000&&n<9999999){
		int a,b,c,d,e,f,g;
		a=n%10;
		if(a%2==0)
			return false;
		b=(n%100-a)/10;
		c=(n%1000-10*b-a)/100;
		d=(n%10000-100*c-10*b-a)/1000;
		e=(n%100000-1000*d-100*c-10*b-a)/10000;
		f=(n%1000000-10000*e-1000*d-100*c-10*b-a)/100000;
		g=(n-100000*f-10000*e-1000*d-100*c-10*b-a)/1000000;
		if(a==g&&b==f&&c==e){
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
int main(){
	int a,b,i;
	cin>>a>>b;
	if(a&2==0){
	for(i=a;i<=b;i+=2){
		if(checkpalindromic(i)&&checkprime(i)){
			cout<<i<<'\n';
		}
	}
	}
	else{
		for(i=a;i<=b;i++){
		if(checkpalindromic(i)&&checkprime(i)){
			cout<<i<<'\n';
		}
	}
	}
	return 0;
}
