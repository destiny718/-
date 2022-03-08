#include<iostream>
using namespace std;
bool checkprime(int);

int main(){
	int i,a,n,b,c,d,e;
	cin>>n;
		for(d=2;d*d<=n;d++){
			e=n%d;
			if(e==0)
			break;
		}
		if(e!=0)
		cout<<'A'<<'\n'<<n;
		else{
		for(i=2;i*i<=n;i++){
		a=n%(i*i);
		if(a==0){
			cout<<'B'<<'\n';
			break;
		}
	}
		if(a!=0){
		cout<<'A'<<'\n';
	}
		for(c=2;c<=n;c++){
		b=n%c;
		if(b==0){
			cout<<c<<'\n';
			n=n/c;
			c=1;
		}
	}	
		if(b!=0){
			cout<<n;
	}
	}

	return 0;

}
