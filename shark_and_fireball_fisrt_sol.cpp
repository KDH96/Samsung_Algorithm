#include<iostream>
#include<vector>
using namespace std;

struct FB
{
    int y, x;
    int m, s, d;
};

int N, M, K, ret;
vector<FB>fire[2];
int cur, nnnext;

const int dy[] = {-1, -1, 0, +1, +1, +1, 0, -1 };
const int dx[] = {0, +1, +1, +1, 0, -1, -1, -1};

void input(){
    cin >> N >> M >> K;
    for(int i = 0; i < M; ++i){
        int r, c, m, s, d;
        cin >> r >> c >> m >> s >>d;
        --r, --c;
        fire[0].push_back({r, c, m, s, d});
    }
}

void get_sum(){
    for(int i = 0; i < fire[cur].size(); ++i){
            ret += fire[cur][i].m;
    }
}

void simul(){
    vector<int>temp[50][50];
    for(int i = 0; i < fire[cur].size(); ++i){
        int speed = fire[cur][i].s % N;
        int dir = fire[cur][i].d;
        int ny = (fire[cur][i].y + (dy[dir] * speed) + N ) % N;
        int nx = (fire[cur][i].x + (dx[dir] * speed) + N ) % N;
        fire[cur][i].y = ny;
        fire[cur][i].x = nx;
        temp[ny][nx].push_back(i);
    }
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < N; ++x){
            if(temp[y][x].size() != 0){
                if(temp[y][x].size() >= 2){
                    int count = temp[y][x].size();
                    int mass = 0; int speed = 0;
                    bool even = true;
                    bool odd = true;
                    for(int t = 0; t < count; ++t){
                        int target = temp[y][x][t];
                        mass += fire[cur][target].m;
                        speed += fire[cur][target].s;
                        if( fire[cur][target].d % 2 == 0){
                            odd = false;
                        }
                        else{
                            even = false;
                        }
                    }
                    mass /= 5;
                    if(mass == 0) continue;
                    speed /= count;
                    int dir = 0;
                    if(even || odd){
                        dir = 0;
                    }
                    else{
                        dir = 1;
                    }
                    for(int t = 0; t < 4; ++t){
                        fire[nnnext].push_back({y, x, mass, speed, dir + (t * 2)});
                    }
                } else{ // 1ÀÏ ¶§,
                    int target = temp[y][x][0];
                    fire[nnnext].push_back(fire[cur][target]);
                }
            }
        }
    }
    fire[cur].clear();
    vector<FB>().swap(fire[cur]);
}

void solve(){
    cur = 0;
    for(int k = 0; k < K; ++k){
        nnnext = (cur + 1) % 2;
        simul();
        cur = nnnext;
    }
    get_sum();
}

int main(){
    
    input();
    ret = 0;
    solve();
    cout << ret << endl;
    return 0;
}