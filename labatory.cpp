#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int n, m, ret;
int map[8][8];

const int dy[] = {-1, +1, 0, 0};
const int dx[] = {0, 0, -1, +1};

void simul_bfs(){
    int temp[8][8];
    queue<int> q;
    int visited[8][8] = { 0,};
    for(int y = 0; y < n; ++y){
        for(int x =0; x < m; ++x){
            temp[y][x] = map[y][x];
            if(temp[y][x] == 2){
                q.push(10*y + x);
                visited[y][x] = 1;
            }
        }
    }
    while(!q.empty())
    {
        int cur = q.front(); q.pop();

        int cy = cur / 10;
        int cx = cur % 10;

        temp[cy][cx] = 2;

        for(int dir = 0; dir < 4; ++dir){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || ny >= n || nx < 0 || nx >= m) continue;

            if(visited[ny][nx] == 0 && temp[ny][nx] == 0 ){
                visited[ny][nx] = 1;
                q.push(10*ny + nx);
            }
        }
    }
    int candi = 0;
    for(int y =0; y < n; ++y){
        for(int x = 0; x <m; ++x){
            if(temp[y][x] == 0) ++candi;
        }
    }
    ret = max(ret, candi);
}

void pick_dfs(int cnt, int sy, int sx){

    if(cnt == 3){
        simul_bfs();
        return;
    }
    for(int y = sy; y < n; ++y){
        for(int x = sx; x < m; ++x){
            if(map[y][x] == 0){
                map[y][x] = 1;
                pick_dfs(cnt + 1, y, x);
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

    cout << ret << "\n";
    return 0;
}