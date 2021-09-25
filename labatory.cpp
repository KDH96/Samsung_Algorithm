#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int n, m, ret;
int map[8][8];

const int dy[] = {-1, +1, 0, 0};
const int dx[] = {0, 0, -1, +1};

void simul(){

    int temp[8][8];
    queue<int> q;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < m; ++x){
            temp[y][x] = map[y][x];
            if(temp[y][x] == 2){
                q.push(y * 10 + x);
            }
        }
    }
    while(!q.empty()){
        int cur = q.front(); q.pop();
        
        int cy = cur / 10;
        int cx = cur % 10;
        temp[cy][cx] = 2;
        
        for(int dir = 0; dir < 4; ++dir){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || ny >= n || nx < 0 || nx >= m || temp[ny][nx] != 0){
                continue;
            } 
            temp[ny][nx] = 2;
            q.push(10 * ny + nx);
        }
    }
    int safe = 0;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < m; ++x){
            if( temp[y][x] == 0) ++safe;  
        }
    }
    ret = max(ret, safe);
}

void pick_dfs(int wall, int sy, int sx){
    if( wall == 3){
        simul();
        return;
    }
    for(int y = sy; y < n; ++y){
        for(int x = sx; x < m; ++x){
            if(map[y][x] == 0){
                map[y][x] = 1;
                pick_dfs(wall + 1, y, x);
                map[y][x] = 0;
            }
        }
        sx = 0;
    }
}

int main(){
    cin >> n >> m;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < m; ++x){
            cin >> map[y][x]; 
        }
    }
    pick_dfs(0, 0, 0);
    cout << ret << endl;
    return 0;
}