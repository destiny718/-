#include<iostream>
using namespace std;

int main(){
	int L,R,i,a,b,c,d,sum;
	cin>>L>>R;
	sum=0;
	for(i=L;i<=R;i++){
	a=i/1000;
	b=(i-a*1000)/100;
	c=(i-a*1000-b*100)/10;
	d=i-a*1000-b*100-c*10;
	if(a==2)
		sum++;
	if(b==2)
		sum++;
	if(c==2)
		sum++;
	if(d==2)
		sum++;
	}cout<<sum<<endl;
	return 0;
		
	
	
}
