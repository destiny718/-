#include<iostream>
using namespace std;

int main(){
	int n,Q,i,j,k,l,min=1001,qq;
	cin>>n>>Q;
	int a[2000]={0};
	int b[4000]={0};
	for(i=0;i<n;i++){
		cin>>a[i];
	}
	qq=2*Q;
	for(j=0;j<qq;j++){
		cin>>b[j];
	}
	for(k=1;k<qq;k=k+2){
		for(l=b[k-1];l<=b[k];l++){
			if(min>=a[l]){
				min=a[l];
			}
			if(l==b[k]){
			cout<<min<<endl;
			min=1001;
			break;
			}
		}
	}
	return 0;
}
