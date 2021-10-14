#include<iostream>
#include<queue>
using namespace std;

#define upper 0
#define down 1

struct POSI
{
    int y ,x;
};


int r, c, t;
int map[50][50];
int update[50][50];
queue<POSI> dust;

const int dy[] = {+1, 0, -1, 0};
const int dx[] = {0, -1, 0, +1};

int main(){
    cin >> r >> c >> t;
    POSI cleaner[2];
    int cleaner_idx = 0;
    POSI target;

    for(int y = 0; y < r; ++y){
        for(int x = 0; x < c; ++x){
            cin >> map[y][x];
            if(map[y][x] == -1){
                cleaner[cleaner_idx].y = y;
                cleaner[cleaner_idx].x = x;
                ++cleaner_idx;
            }
            else if(map[y][x] != 0){
                target.y = y; target.x = x;
                dust.push(target);
            }
        }
    }
    int upy = cleaner[upper].y;
    int dpy = cleaner[down].y;

    for(int time = 0; time < t; ++time){
            //확산
        while(!dust.empty()){
            POSI cur_d = dust.front(); dust.pop(); 
            int count = 0;
            for(int dir = 0; dir < 4; ++dir){
                POSI next_d;
                next_d.y = cur_d.y + dy[dir];
                next_d.x = cur_d.x + dx[dir];
                if(next_d.y < 0 || next_d.y >= r ||
                next_d.x < 0 || next_d.x >= c || map[next_d.y][next_d.x] == -1)
                    continue;
                ++count;
                update[next_d.y][next_d.x] += (map[cur_d.y][cur_d.x] / 5);
            }
            update[cur_d.y][cur_d.x] -= ((map[cur_d.y][cur_d.x] / 5) * count); 
        }
        for(int y = 0; y < r; ++y){
            for(int x = 0; x < c; ++x){
                map[y][x] += update[y][x];
                update[y][x] = 0;
                }
        }
    //공기청정기 
        for(int y = upy - 1; y > 0; --y){
            map[y][0] = map[y - 1][0];
        }
        for(int x = 0; x < c - 1; ++x){
            map[0][x] = map[0][x + 1];
        }
        for(int y = 0; y < upy; ++y){
            map[y][c - 1] = map[y + 1][c - 1];
        }        
        for(int x = c - 1; x > 1; --x){
            map[upy][x] = map[upy][x - 1];
        }
        map[upy][1] = 0; 
    //아래 공청기
        for(int y = dpy + 1; y < r - 1; ++y){
            map[y][0] = map[y + 1][0];
        }
        for(int x = 0; x < c - 1; ++x){
            map[r - 1][x] = map[r - 1][x + 1];
        }
        for(int y = r - 1; y > dpy; --y){
            map[y][c - 1] = map[y - 1][c - 1];
        }                
        for(int x = c - 1; x > 1; --x){
            map[dpy][x] = map[dpy][x - 1];
        }
        map[dpy][1] = 0;        

        for(int y = 0; y < r; ++y){
            for(int x = 0; x < c; ++x){
                if(map[y][x] != 0 && map[y][x] != -1){
                    target.y = y; target.x = x;
                    dust.push(target);
                }
            }
        }
    }

    int ret = 0;
    while(!dust.empty()){
        POSI cur_d = dust.front(); dust.pop();
        ret += map[cur_d.y][cur_d.x];
    }
    cout << ret << endl;
    
    return 0;
}