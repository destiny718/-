#include<iostream>
using namespace std;

int main(){
	int N,M,i,j,max=-1000000,a,b,c,d=0,k=1;
	cin>>N>>M;
	int field[101][101]={0};
	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++){
			cin>>field[i][j];
			field[i][j]+=field[i-1][j];
		}
	}
	for(a=1;a<=N;a++){
		for(b=a;b<=N;b++){
			for(c=1;c<=M;c++){
				d+=field[b][c]-field[a-1][c];
				if(d>max)
				max=d;
				if(c==M){
					d=0;
					k++;
					if(c!=k)
					c=k;
					else{
					k=1;
					break;
					}
					
				}
				
			}
		}
	}
	cout<<max<<endl;
	return 0;
}
