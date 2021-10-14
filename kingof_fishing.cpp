#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct SHARK 
{
    int y, x, s, d, z;
};

int R, C, M, ret;
vector<SHARK> map[100][100];
const int dy[] = {-1, +1, 0, 0};
const int dx[] = { 0, 0, +1, -1};

int change_dir(int d) { 
    if (d == 0) return 1; 
    else if (d == 1) return 0; 
    else if (d == 2) return 3; 
    else if (d == 3) return 2; 

}

void fishing(int fisher){
    for(int y = 0; y < R; ++y){
        if(!map[y][fisher].empty()){
            ret += map[y][fisher][0].z;
            map[y][fisher].pop_back();
            break;
        } 
    }
}
void move(){
    vector<SHARK> new_shark[100][100];
    for(int y = 0; y < R; ++y){
        for(int x = 0; x < C; ++x){
            if(map[y][x].empty()) continue;
            SHARK cur_shark = map[y][x][0];
            map[y][x].pop_back();
            
            int& cy = cur_shark.y;
            int& cx = cur_shark.x;
            int& cd = cur_shark.d;
            int cs = cur_shark.s;

            while(cs--){
                int ny = cy + dy[cd];
                int nx = cx + dx[cd];
                if(ny < 0 || ny >= R || nx < 0 || nx >= C){
                    cd = change_dir(cd);
                }
                cy += dy[cd];
                cx += dx[cd];
            }

            if(!new_shark[cy][cx].empty()){
                if(new_shark[cy][cx][0].z < cur_shark.z){
                    new_shark[cy][cx].pop_back();
                    new_shark[cy][cx].push_back(cur_shark);
                }
            }
            else{
                    new_shark[cy][cx].push_back(cur_shark);                
            }
        }
    }
    for(int y = 0; y < R; ++y){
        for(int x = 0; x < C; ++x){
            map[y][x] = new_shark[y][x];
        }
    }
}

int main(){
    cin >> R >> C >> M;

    for(int i = 0; i < M; ++i){
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;
        --r; --c; --d;
        if(d == 0 || d == 1) s = s % (2 * (R - 1));
        else if(d == 2 || d == 3) s = s % (2 * (C - 1));
        map[r][c].push_back({r, c, s, d, z});
    }
    for(int fisher = 0; fisher < C; ++fisher){
        fishing(fisher);
        move();
    }

    cout << ret << endl;
    return 0;
}