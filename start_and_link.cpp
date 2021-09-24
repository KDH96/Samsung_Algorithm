#include<iostream>
#include<algorithm>

using namespace std;

int n;
int table[20][20];
int pick[20];
int team_1[10], team_2[10];
int ret = 0x7fffffff;

void update(){
    int team1_size = 0, team2_size = 0;
    for(int i = 0; i < n; ++i){
        if(pick[i] == 1){
            team_1[team1_size++] = i;
        }
        else{
            team_2[team2_size++] = i;
        }
    }

    int sum_1 = 0, sum_2 = 0;
    for(int y = 0; y < n / 2; ++y){
        for(int x = y + 1; x < n / 2; ++x){
            sum_1 += (table[team_1[y]][team_1[x]] + table[team_1[x]][team_1[y]]);
            sum_2 += (table[team_2[y]][team_2[x]] + table[team_2[x]][team_2[y]]);
        }
    }
    ret = min(ret,abs(sum_1 - sum_2));
}

void dfs(int cnt, int cur){
    if(cnt == (n/2) ){
        update();
        return;
    }

    for(int i = cur; i < n; ++i){
        pick[i] = 1;
        dfs(cnt + 1, i + 1);
        pick[i] = 0;
    }
}

int main(){
    cin >> n;
    for(int y =0; y < n; ++y){
        for(int x =0; x < n; ++x){
            cin >> table[y][x];
        }
    }
    dfs(0, 0);
    cout << ret << "\n";
    return 0;
}