#include<iostream>

using namespace std;

int n, m, sy, sx, d;
int map[50][50];
int visited[50][50];

const int dy[] = {-1, 0, +1, 0};
const int dx[] = {0, +1, 0, -1};

int simulation(){  
    int ans = 0;
    int cy = sy; int cx = sx; int cd = d;
    visited[cy][cx] = 1;
    
    while(true)
    {
        ++ans;
        bool flag = false;
        for(int i = 0; i < 4; ++i){
            int nd = (cd + 3) % 4;
            int ny = cy + dy[nd];
            int nx = cx + dx[nd];
            if(map[ny][nx] == 1 || visited[ny][nx] == 1){
                cd = nd;
                continue;
            }
            cd = nd, cy = ny, cx = nx;
            visited[cy][cx] = 1;
            flag = true;
            break;
        }
        if(flag) continue;
        int nd = (cd + 2) % 4;
        int ny = cy + dy[nd];
        int nx = cx + dx[nd];
        if(map[ny][nx] == 1) break;
        if(visited[ny][nx] == 1) --ans;
        cy = ny, cx = nx;
        visited[cy][cx] == 1;
    }
    return ans;
}

int main(){
    cin >>  n >> m >> sy >> sx >> d;
    for(int y = 0; y < n; ++y){
        for(int x =0; x < m; ++x){
            cin >> map[y][x];
        }
    }

    int ans = simulation();

    cout << ans << "\n";
    return 0;
}