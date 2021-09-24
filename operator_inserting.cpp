#include<iostream>
#include<queue>
#include<climits>

using namespace std;

int n;
int max_n = INT_MIN;
int min_n = INT_MAX;
int A[11];
int op[4];

void op_dfs(int num, int idx){
    
    if(idx == n){
        if(max_n < num){
            max_n = num;
        }
        if(min_n > num){
            min_n = num;
        }
        return;
    }

    for(int i = 0; i < 4; ++i){
        if(op[i] != 0){
            int temp;
        switch (i)
        {
        case 0:
            temp = num + A[idx];
            break;
        case 1:
            temp = num - A[idx];
            break;            
        case 2:
            temp = num * A[idx];
            break;
        case 3:
            temp = num / A[idx];
            break;                    
        default:
            break;
        }
            --op[i];
            op_dfs(temp, idx + 1);
            ++op[i];
        }
    }
    return;
}

int main(){
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> A[i];
    }
    for(int i = 0; i < 4; ++i){
        cin >> op[i];
    }

    op_dfs(A[0], 1);
    cout << max_n << "\n" << min_n << "\n" ;
}