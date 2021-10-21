#include<iostream>
using namespace std;

struct SHARK
{
    int y, x, d;
    int pre_dir[4][4];
};

int map[20][20][3];
int N, M, K, ret;

SHARK shark[400];
const int dy[] = {-1, +1, 0, 0};
const int dx[] = {0, 0, -1, +1};

int main(){
    cin >> N >> M >> K;
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < N; ++x){
            cin >> map[y][x][0];
            if(map[y][x][0] != 0){
                int shark_n = map[y][x][0] - 1;
                shark[shark_n].y = y;
                shark[shark_n].x = x;
                map[y][x][1] = map[y][x][0];
                map[y][x][2] = K;
            }
        }
    }

    for(int i = 0; i < M; ++i){
        cin >> shark[i].d ;
        --shark[i].d;
    }

    for(int i = 0; i < M; ++i){
        for(int j = 0; j < 4; ++j){
            cin >> shark[i].pre_dir[j][0] >> shark[i].pre_dir[j][1] >> shark[i].pre_dir[j][2] >> shark[i].pre_dir[j][3];
            --shark[i].pre_dir[j][0], --shark[i].pre_dir[j][1], --shark[i].pre_dir[j][2], --shark[i].pre_dir[j][3];
        }
    }

    ret = -1;
    int time = 0;
    int kill_shark = 0;

    while(time <= 1000){
        ++time;
        
        int new_map[20][20][3] = { 0,};
        for(int y = 0; y < N; ++y){
            for(int x = 0; x < N; ++x){
                new_map[y][x][0] = map[y][x][0];
                new_map[y][x][2] = map[y][x][2];
                if(new_map[y][x][2] > 0){
                    --new_map[y][x][2];
                }
                if(new_map[y][x][2] > 0){
                    new_map[y][x][1] = map[y][x][1];
                }
            }
        }

        for(int i = 0; i < M; ++i){
            
            int cd = shark[i].d;
            int cy = shark[i].y;
            int cx = shark[i].x;
            if(cy == -1) continue;

            bool is_move = false;
            for(int dir = 0; dir < 4; ++dir){
                int nd = shark[i].pre_dir[cd][dir];
                int ny = cy + dy[nd];
                int nx = cx + dx[nd];
                if(ny < 0 || ny >= N || nx < 0 || nx >= N || map[ny][nx][2] != 0){
                    continue;
                }
                is_move = true;
                new_map[cy][cx][0] = 0;
                if(new_map[ny][nx][0] == 0){
                    new_map[ny][nx][0] = i + 1;
                    new_map[ny][nx][1] = i + 1;
                    new_map[ny][nx][2] = K;
                    
                    shark[i].y = ny;
                    shark[i].x = nx;
                    shark[i].d = nd;
                } else{
                    ++kill_shark;
                    shark[i].y = -1;
                }
                break;
            }
            if(is_move==false){
                for(int dir = 0; dir < 4; ++dir){
                    int nd = shark[i].pre_dir[cd][dir];
                    int ny = cy + dy[nd];
                    int nx = cx + dx[nd];
                    if(ny < 0 || ny >= N || nx < 0 || nx >= N ){
                        continue;
                    }
                    if(map[ny][nx][2] != 0 && map[ny][nx][1] != i + 1){
                        continue;
                    }
                    new_map[cy][cx][0] = 0;
                    if(new_map[ny][nx][0] == 0){
                        new_map[ny][nx][0] = i + 1;
                        new_map[ny][nx][1] = i + 1;
                        new_map[ny][nx][2] = K;
                        
                        shark[i].y = ny;
                        shark[i].x = nx;
                        shark[i].d = nd;
                    }
                    else{
                        ++kill_shark;
                        shark[i].y = -1;
                    }
                    break;
                }
            }
        }

        if(kill_shark == M - 1){
            break;
        }
        for(int y = 0; y < N; ++y){
            for(int x = 0; x < N; ++x){
                map[y][x][0] = new_map[y][x][0];
                map[y][x][1] = new_map[y][x][1];
                map[y][x][2] = new_map[y][x][2];
            }
        }
        //end
    }

    if(time <= 1000){
        ret = time;
    }

    cout << ret <<endl;
    return 0;
}