#include<iostream>
using namespace std;

int nj(int *p,int n){
    if(n==1){
        return *p;
    }	
	if(n==2){		
		return *(p+3)*(*p)-*(p+1)*(*(p+2));		
	}
	else{
		int i=0,num=0,sum = 0;
		int al=(n-1)*(n-1);
        int *ne=new int[al];
		for(int q=0;q<n;q++){ 	 
			i=0;num=0; 
			for(int k=0;k<n*n;k++){  	 
				if(k==n*i+q&&k<n*n) {
                    i++; 
                    continue;
                }	 
				else if(k<n){
                    continue;
                }		
				else if(k<n*n){
					ne[num] = *(p+k);   	
					num++;
					continue;
				}
			}
		if(q%2==0){
            sum += *(p+q)*nj(ne,n-1);
        } 	
		else{
            sum -= *(p+q)*nj(ne,n-1);
        } 
		} 
		return sum;
	}
}
int main()
{
	int n;
	cin>>n;
	int all=n*n;
    int *a=new int[all];
	for(int i=0;i<n*n;i++){
        cin>>a[i];
    }
	cout<<nj(a,n);
    delete []a;
	return 0;
}