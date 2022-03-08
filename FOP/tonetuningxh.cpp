#include<iostream>
using namespace std;

int main(){
    int n, bL, mL;
    cin >> n>> bL>> mL;
    int *c = new int[n];
    for (int i = 0; i < n; ++i){
        cin >> c[i];
    }
    int L[1001] = {0};
    L[0] = bL;
    int nL = 1;
    for (int i = 0; i < n; ++i){
        int l0[1001] = {0};
        int l1[1001] = {0};
        for (int j = 0; j < nL; ++j){
            l0[j] = L[j] - c[i];
            l1[j] = L[j] + c[i];
        }
        int nL0 = 0;
        for (int n0 = 0, n1 = 0; n0 < nL || n1 < nL;){
            if (n1 == nL){
                if (l0[n0] >= 0) L[nL0++] = l0[n0];
                ++n0;
            }else if (l1[n1] > l0[n0]){
                if (l1[n1] <= mL) L[nL0++] = l1[n1];
                ++n1; 
            }else if (l0[n0] == l1[n1]){
                L[nL0++] = l0[n0];
                ++n0;
                ++n1;
            }else{
                if (l0[n0] >= 0) L[nL0++] = l0[n0];
                ++n0;
            }
        }
        nL = nL0;
        if (nL == 0){
            L[0] = -1;
            break;
        }
    }
    cout <<L[0];
    return 0;
}