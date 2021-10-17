#include<iostream>
using namespace std;

struct CMD
{
    int x, d, k;
};

int n, m, t;
int circle[50][50];
CMD cmd[50];

const int DEL =  -1;

void Input(){
    cin >> n >> m >> t;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < m; ++x){
            cin >> circle[y][x];
        }
    }
    for(int i = 0; i < t; ++i){
        cin >> cmd[i].x >> cmd[i].d >> cmd[i].k;
    }
}

void solve(int x, int d, int k){
    int pick = x - 1;
    if(d == 1){
        k = -k;
    }
    while(pick < n){
        int temp[50] = { 0,};
        for(int j = 0; j < m; ++j){
            temp[(j + k + m) % m] = circle[pick][j];
        }
        for(int j = 0; j < m; ++j){
                circle[pick][j] = temp[j]; 
        }            
        pick += x;
    }

    bool check[50][50] = { false, };
    bool is_update = false;
    const int dy[] = {0, 0, -1, +1};
    const int dx[] = {-1, +1, 0, 0};

    for(int y = 0; y < n; ++y){
        for(int x = 0; x < m; ++x){
            for(int dir = 0; dir < 4; ++dir){
                int ny = y + dy[dir];
                int nx = (x + dx[dir] + m) % m;
                if(ny < 0 || ny >= n) continue;
                if(circle[y][x] != DEL && circle[ny][nx] != DEL && circle[ny][nx] == circle[y][x]){
                    is_update = true;
                    check[y][x] = true;
                    check[ny][nx] = true;
                }
            }
        }
    }
    if(is_update){
        for(int y = 0; y < n; ++y){
            for(int x = 0; x < m; ++x){
                if(check[y][x]){
                    circle[y][x] = DEL;
                }
            }
        }
    } else{
        int sum, count = 0;
        for(int y = 0; y < n; ++y){
            for(int x = 0; x < m; ++x){
                if(circle[y][x] != DEL){
                    sum += circle[y][x];
                    ++count;
                }
            }
        }
        for(int y = 0; y < n; ++y){
            for(int x = 0; x < m; ++x){
                if(circle[y][x] == DEL) continue;
                    if(circle[y][x] * count > sum ){
                        circle[y][x] -= 1;
                    } else if (circle[y][x] * count < sum){
                        circle[y][x] += 1;
                    }                    
            }
        }                
    }
}

int main(){
    Input();

    for(int i = 0; i < t; ++i){
        solve(cmd[i].x, cmd[i].d, cmd[i].k);
    }

    int ret = 0;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < m; ++x){
            if(circle[y][x] != DEL)
                ret += circle[y][x];
        }
    }
    cout << ret << endl;
    return 0;
}