#include<iostream>
using namespace std;

struct Package{
    char name[21];
    int month;
    int day;
};
int main(){
    int n;
    int num=0;
    cin>>n;
    Package birthday[100];
    for(int i=0;i<n;i++){
        cin>>birthday[i].name>>birthday[i].month>>birthday[i].day;
    }
    for(int i=1;i<=12;i++){
        for(int j=1;j<=31;j++){
            for(int k=0;k<n;k++){
                if(birthday[k].month==i&&birthday[k].day==j){
                    num++;
                }
                if(num==2){
                    cout<<i<<' '<<j;
                    for(int l=0;l<n;l++){
                        if(birthday[l].month==i&&birthday[l].day==j){
                            cout<<' '<<birthday[l].name;
                            }
                        if(l==n-1){
                            cout<<endl;
                            num=0;
                            }
                        }
                        break;
                }
                if(k==n-1){
                    num=0;
                }
            }
        }
    }
    return 0;
}