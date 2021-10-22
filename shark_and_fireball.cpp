#include<iostream>
#include<vector>
using namespace std;

struct FB
{
    int y, x;
    int m, s, d;
};

int N, M, K;
vector<FB>fire;
vector<int>map[50][50];

const int dy[] = {-1, -1, 0, +1, +1, +1, 0, -1 };
const int dx[] = {0, +1, +1, +1, 0, -1, -1, -1};

void input(){
    cin >> N >> M >> K;
    for(int i = 0; i < M; ++i){
        int r, c, m, s, d;
        cin >> r >> c >> m >> s >>d;
        --r, --c;
        fire.push_back({r, c, m, s, d});
        map[r][c].push_back(i);
    }
}

void move(){
    vector<int>temp[50][50];
    for(int i = 0; i < fire.size(); ++i){
        int speed = fire[i].s % N;
        int dir = fire[i].d;
        int ny = (fire[i].y + (dy[dir] * speed) + N) % N;
        int nx = (fire[i].x + (dx[dir] * speed) + N) % N;
        fire[i].y = ny;
        fire[i].x = nx;
        temp[ny][nx].push_back(i);
    }
    for(int y = 0;  y <N; ++y){
        for(int x = 0; x <N; ++x){
            map[y][x] = temp[y][x];
        }
    }
}

void sum(){
    vector<FB>new_fire;
    for(int y = 0; y < N; ++y){
        for(int x = 0; x< N; ++x){
            if(map[y][x].size() == 0) continue;
            if(map[y][x].size() == 1){
                int target = map[y][x][0];
                new_fire.push_back(fire[target]);
                continue;
            } else{
                int mass = 0; int speed = 0;
                bool odd = true; bool even = true;
                for(int i = 0; i < map[y][x].size(); ++i){
                    mass += fire[map[y][x][i]].m;
                    speed += fire[map[y][x][i]].s;
                    if( fire[map[y][x][i]].d % 2 == 0){
                        odd = false;
                    } else{
                        even = false;
                    }
                }
                mass /= 5;
                if(mass == 0) continue;
                speed /= map[y][x].size();
                for(int i = 0; i < 4; ++i){
                    if(even || odd){
                        new_fire.push_back({y, x, mass , speed, i * 2});
                    }
                    else{
                        new_fire.push_back({y, x, mass , speed, i * 2 + 1});
                    }
                }
            }
        }
    }
    fire = new_fire;
}

int solve(){
    for(int k = 0; k < K; ++k){
        move();
        sum();
    }
    int candi = 0;
    for(int i = 0; i < fire.size(); ++i){
            candi += fire[i].m;
    }
    return candi;
}

int main(){
    
    input();
    int ret = solve();
    cout << ret << endl;
    return 0;
}