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
int main(){
    int n,n1;
    long long sum1=0;
    long long sum2=0;
    scanf("%d",&n);
    int *num=new int [n];
    for(int i=0;i<n;++i){
        scanf("%d",&num[i]);
    }
    quicksort(num,0,n-1);
    n1=n/2;
    for(int i=0;i<n1;++i){
        sum1+=num[i];
    }
    for(int i=n1;i<n;++i){
        sum2+=num[i];
    }
    cout<<sum2-sum1<<endl;
    delete []num;
    return 0;
}