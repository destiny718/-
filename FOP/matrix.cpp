#include<iostream>
using namespace std;

int matrix[101][101]={0};
int n,m;
void order(char a,int *p){
    int temp;
    if(a=='A'){
        for(int i=p[1];i<=p[3];++i){
            for(int j=p[2];j<=p[4];++j){
                matrix[i][j]=matrix[i][j]+p[5];
            }
        }
    }
    if(a=='E'){
        for(int i=1;i<=m;++i){
            temp=matrix[p[1]][i];
            matrix[p[1]][i]=matrix[p[2]][i];
            matrix[p[2]][i]=temp;
        }
    }
    if(a=='Q'){
        cout<<matrix[p[1]][p[2]]<<endl;
    }
}
int main(){
    int num;
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>matrix[i][j];
        }
    }
    cin>>num;
    char ordn[101]={0};
    int ord[101][6]={0};
    //bool check=true;
    for(int i=1;i<=num;++i){
        /*if(check){
            check=false;
            cin.ignore();
        }*/
        cin>>ordn[i];
        if(ordn[i]=='A'){
            for(int j=1;j<=5;++j){
                cin>>ord[i][j];
            }
            //order(ordn[i],ord[i]);
        }
        else{
            for(int j=1;j<=2;++j){
                cin>>ord[i][j];
            }//order(ordn[i],ord[i]);
        }
    }
    for(int i=1;i<=num;++i){
        order(ordn[i],ord[i]);
    }
    return 0;
}