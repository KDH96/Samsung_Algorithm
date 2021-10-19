#include<iostream>
#include<algorithm>
using namespace std;

struct POS
{
    int y, x, d;
};

int ret;
const int dy[] = {-1, -1, 0, +1, +1, +1, 0, -1};
const int dx[] = {0, -1, -1, -1, 0, +1, +1, +1};

void solve(int map[4][4], POS fish[], int shark_y, int shark_x, int sum){

    POS candi_fish[17] = { 0,};
    int candi_map[4][4] = { 0,};
    for(int y = 0; y < 4; ++y){
        for(int x = 0; x < 4; ++x){
            candi_map[y][x] = map[y][x];
        }
    }
    for(int i = 1 ; i <= 16; ++i){
        candi_fish[i] = fish[i];
    }
    //eat
    int fish_num = candi_map[shark_y][shark_x];
    int shark_dir = candi_fish[fish_num].d;
    candi_map[shark_y][shark_x] = -1;
    candi_fish[fish_num].y = -1;
    candi_fish[fish_num].x = -1;
    candi_fish[fish_num].d = -1;
    
    sum += fish_num;
    if(sum > ret){
        ret = sum;
    }
    //fishmove
    for(int i = 1; i <= 16; ++i){
        if(candi_fish[i].y == -1) continue;
        int cy = candi_fish[i].y;
        int cx = candi_fish[i].x;
        int cd = candi_fish[i].d;

        for (int dir = 0; dir < 8; ++dir){
            int nd = (cd + dir) % 8;
            int ny = cy + dy[nd];
            int nx = cx + dx[nd];
            if(ny < 0 || ny >= 4 || nx < 0 || nx >=4 || (shark_y == ny && shark_x == nx)){
                continue;
            }
            if(candi_map[ny][nx] != -1){
                int target = candi_map[ny][nx];
                candi_fish[target].y = cy;
                candi_fish[target].x = cx;
                candi_fish[i].y = ny;
                candi_fish[i].x = nx;
                candi_fish[i].d = nd;

                candi_map[ny][nx] = i;
                candi_map[cy][cx] = target;
            }
            else{
                candi_fish[i].y = ny;
                candi_fish[i].x = nx;
                candi_fish[i].d = nd;

                candi_map[ny][nx] = i;
                candi_map[cy][cx] = -1;
            }
            break;
        }
    }
    //sharkmove
    for(int i = 1; i < 4; ++i){
        int ny = shark_y + dy[shark_dir] * i;
        int nx = shark_x + dx[shark_dir] * i;
        if(ny < 0 || ny >= 4 || nx < 0 || nx >=4){
            break;
        }
        if(candi_map[ny][nx] != -1){
            solve(candi_map, candi_fish, ny, nx, sum);
        }
    }
}

int main(){
    POS fish[17] = { 0,};
    int map[4][4] = { 0,};
    for(int y = 0; y < 4; ++y){
        for(int x = 0; x < 4; ++x){
            int a, b;
            cin >> a >> b;
            map[y][x] = a;
            fish[a].y = y;
            fish[a].x = x;
            fish[a].d = b - 1;
        }
    }

    ret = 0;
    solve(map, fish, 0, 0, 0);

    cout << ret << endl;
    return 0;
}
