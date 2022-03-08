#include<iostream>
using namespace std;

//快速排序
void quicksort(int s[], int l, int r){
    if (l < r){
        //Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换
        int i = l, j = r, x = s[l];
        while (i < j){
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;  
            if(i < j) 
                s[i++] = s[j];
            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                i++;  
            if(i < j) 
                s[j--] = s[i];
        }
        s[i] = x;
        quicksort(s, l, i - 1); // 递归调用 
        quicksort(s, i + 1, r);
    }
}
int max(int a,int b){
    if(a>b)
        return a;
    else
        return b;
}
int main(){
    int n;
    cin>>n;
    int flowerx[100001]={0};
    int flowery[100001]={0};
    for(int i=0;i<n;++i){
        cin>>flowerx[i]>>flowery[i];
    }
    quicksort(flowerx,0,n-1);
    quicksort(flowery,0,n-1);
    int maxx=flowerx[n-1]-flowerx[0];
    int maxy=flowery[n-1]-flowery[0];
    int max0=max(maxx,maxy);
    cout<<max0<<endl;
    return 0;
}