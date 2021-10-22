#include<iostream>
using namespace std;

struct TOR
{
    int y, x, d;
    int moved, moving;
    int check_dir;
};
TOR T;
int N;
int map[499][499];
int outside_sand;
int count;

const int dy[] = {0, +1, 0, -1};
const int dx[] = {-1, 0, +1, 0};

void input(){
    cin >> N;
    for(int y = 0; y < N; ++y){
        for(int x = 0; x <N; ++x){
            cin >> map[y][x];
        }
    }
}

int percent[5][5] = 
{
    {0, 0, 2, 0, 0},
    {0, 10, 7, 1, 0},
    {5, 0, 0, 0, 0},
    {0, 10, 7, 1, 0},
    {0, 0, 2, 0, 0}
};

void rot(int map[5][5]){
    int temp[5][5] = {0,};

    for(int y = 0; y < 5; ++y){
        for(int x = 0; x <5; ++x){
            temp[y][x] = map[x][4 - y];
        }
    }
    for(int y = 0; y < 5; ++y){
        for(int x = 0; x <5; ++x){
            map[y][x] = temp[y][x];
        }
    }
}

void move(){
    int ny = T.y + dy[T.d];
    int nx = T.x + dx[T.d];
    int flying_sand = map[ny][nx];
    int sand_map[5][5] = { 0,};
    int alpha_y = 2;
    int alpha_x = 1;
    int sum = 0;
    for(int y =0; y < 5; ++y){
        for(int x = 0; x <5; ++x){
            sand_map[y][x] = (percent[y][x] * flying_sand) / 100;
            if(sand_map[y][x] != 0){
                sum += sand_map[y][x];
            }
        }
    }
    sand_map[alpha_y][alpha_x] = flying_sand - sum;
    if( T.d ==1){
        rot(sand_map);
    }
    else if( T.d ==2){
        rot(sand_map);
        rot(sand_map);
    }
    else if( T.d ==3){
        rot(sand_map);
        rot(sand_map);
        rot(sand_map);
    }
    int move_y = ny - 2;
    int move_x = nx - 2;
    for(int y = 0; y <5; ++y){
        int nny = y + move_y; 
        for(int x = 0; x <5; ++x){
            int nnx = x + move_x;
            if(nny < 0 || nny >=N ||nnx < 0 || nnx >=N ){
                outside_sand += sand_map[y][x];
                continue;
            }
            map[nny][nnx] += sand_map[y][x];
        }
    }
    T.y = ny;
    T.x = nx;
}

void solve(){
    T.y = N / 2; T.x = T.y;
    count = 1; T.moved = 0;
    T.moving = 2 * count;
    T.check_dir = 0;
    T.d = 0;
    while(T.y != 0 || T.x != 0){
        if(count == T.check_dir){
            T.check_dir = 0;
            T.d = (T.d + 1) % 4;
        }
        if(T.moved == T.moving){
            ++count;
            T.moved = 0;
            T.moving = 2 * count;
        }
        ++T.moved;
        ++T.check_dir;
        move();
    }
}

int main(){
    input();
    solve();
    cout << outside_sand << endl;
    return 0;
}