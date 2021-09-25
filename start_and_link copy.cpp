#include<iostream>
#include<algorithm>

using namespace std;

int n;
int map[20][20];
int pick[20];
int team1[10], team2[10];
int ret = 0x7fffffff;

void update(){

    int team1_size = 0; int team2_size = 0;
    for(int i = 0; i < n ; ++i){
        if(pick[i] == 1){
            team1[team1_size++] = i;
        }
        else{
            team2[team2_size++] = i;
        }
    }
    int sum1 = 0; int sum2 = 0;
    for(int y = 0; y < n / 2; ++y){
        for(int x = y + 1 ; x < n / 2; ++x){
            sum1 += (map[team1[y]][team1[x]] + map[team1[x]][team1[y]]);
            sum2 += (map[team2[y]][team2[x]] + map[team2[x]][team2[y]]);
        }
    }
    ret = min(ret, abs(sum1 - sum2));
}

void pick_dfs(int cnt, int num){
    if( cnt == (n / 2) ){
        update();
        return;
    }

    for(int i = num; i < n; ++i){
        pick[i] = 1;
        pick_dfs(cnt + 1, i + 1);
        pick[i] = 0;
    }
}

int main(){
    cin >> n;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < n; ++x){
            cin >> map[y][x];
        }
    }

    pick_dfs(0, 0);
    cout << ret << endl;
    return 0;
}