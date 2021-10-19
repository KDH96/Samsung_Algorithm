#include<iostream>
using namespace std;

int N, ret;
int T[16];
int P[16];

void dfs(int day, int sum, int last_day){
    if( day == N + 1){
        ret = max(ret, sum);    
        return ;
    }
    if( day > N + 1){
        sum -= P[last_day];
        ret = max(ret, sum);
        return;
    }

    for(int i = day; i <= N; ++i){
        dfs(i + T[i], sum + P[i], i);
    }
}

int main(){
    cin >> N;
    for(int i = 1; i <= N; ++i){
        cin >> T[i] >> P[i];
    }
    
    ret = 0;
    dfs(1, 0, 0);

    cout << ret << endl;
    return 0;
}