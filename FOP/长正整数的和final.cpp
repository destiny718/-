#include<iostream>
using namespace std;

int main(){
	int i,n,a,j,k,aa=0,bb=0,l,m,r;
	char num11[100]={0};
	char num22[100]={0};
	int sum[100]={0};
	cin>>num11;
	cin>>num22;
	for(k=0;;k++){
		if(num11[k]-'0'>=0){
			aa++;
		}
		else
			break;
	}	
	for(k=0;;k++){		
		if(num22[k]-'0'>=0){
			bb++;
		}
		else
			break;
	}
		if(aa<bb){
			for(l=aa;l>=0;l--){
				num11[l+bb-aa]=num11[l];
			}
			for(l=0;l<bb-aa;l++){
				num11[l]='0';
			}
		}
		if(aa>bb){
			for(m=bb;m>=0;m--){
				num22[m+aa-bb]=num22[m];
			}
			for(m=0;m<aa-bb;m++){
				num22[m]='0';
			}
		}
		r=(aa>=bb)?aa:bb;
		for(i=r;i>=0;i--){
		a=num11[i]+num22[i]+sum[i]-'0'-'0';
		if(a>=10&&i!=0){
			a=a-10;
			sum[i]=a;
			sum[i-1]=sum[i-1]+1;
		}
		else
		sum[i]=a;
	}
		for(i=0;i<r;i++){
		cout<<sum[i];
	}
	return 0;
}
