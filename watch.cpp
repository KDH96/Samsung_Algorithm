#include<iostream>
#include<cstring>

using namespace std;

struct CCTV
{
    int type, y, x;
};

int n, m, ret;
int map[8][8];
int cctv_size;
const int rot_size[] = { 4, 2, 4, 4, 1};
CCTV cctv[8];

void update(int dir, CCTV cctv){

    switch (dir % 4)
    {
    case 0:
    for(int x = cctv.x + 1; x < m; ++x){
        if(map[cctv.y][x] == 6) break;
        map[cctv.y][x] = -1;
    }
        break;
    case 1:
    for(int y = cctv.y + 1; y < n; ++y){
        if(map[y][cctv.x] == 6) break;
        map[y][cctv.x] = -1;
    }
        break;
    case 2:
    for(int x = cctv.x - 1; x >= 0; --x){
        if(map[cctv.y][x] == 6) break;
        map[cctv.y][x] = -1;
    }
        break;
    case 3:
    for(int y = cctv.y - 1; y >= 0; --y){
        if(map[y][cctv.x] == 6) break;
        map[y][cctv.x] = -1;
    }
        break;
    default:
        break;
    }
}

void dfs(int cctv_idx){
    if( cctv_idx == cctv_size){
        int candi = 0;
        for(int y = 0; y < n; ++y){
            for(int x = 0; x < m; ++x){
                if(map[y][x] == 0) ++candi;
            }
        }
        ret = min(ret, candi);
        return;
    }
    int backup[8][8];
    int type = cctv[cctv_idx].type;

    for(int dir = 0; dir < rot_size[type]; ++dir){
        memcpy(backup, map, sizeof(map));
        
        switch(type){
            case 0:
            update(dir, cctv[cctv_idx]);
                break;
            case 1:
            update(dir, cctv[cctv_idx]);
            update(dir + 2, cctv[cctv_idx]);
                break;
            case 2:
            update(dir, cctv[cctv_idx]);
            update(dir + 1, cctv[cctv_idx]);
                break;
            case 3:
            update(dir, cctv[cctv_idx]);
            update(dir + 1, cctv[cctv_idx]);
            update(dir + 2, cctv[cctv_idx]);
                break;
            case 4:
            update(dir, cctv[cctv_idx]);
            update(dir + 1, cctv[cctv_idx]);
            update(dir + 2, cctv[cctv_idx]);
            update(dir + 3, cctv[cctv_idx]);
            default:
                break;
        }

        dfs(cctv_idx +1);

        memcpy(map, backup, sizeof(backup));
        }
}

int main(){
    cin >> n >> m;
    
    for( int y = 0; y < n; ++y){
        for( int x = 0; x < m; ++x){
            cin >> map[y][x];
            if(map[y][x] != 0 && map[y][x] != 6){
                cctv[cctv_size].type = map[y][x] - 1;
                cctv[cctv_size].y = y;
                cctv[cctv_size].x = x;
                ++cctv_size; 
            }
        }
    }
    ret = 100;
    dfs(0);
    cout << ret << endl;
}