#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int map[64][64], temp[64][64];
int N, Q;
bool visited[64][64], checkMelt[64][64];

const int dy[] = {0, 0, -1, +1};
const int dx[] = {-1, +1, 0, 0};

void input(){
    cin >> N >> Q;
    N = (1 << N);
    for(int y = 0; y < N; ++y){
        for(int x= 0; x < N; ++x){
            cin >> map[y][x];
        }
    }
}

void rotate(int sy, int sx, int L){
    for(int y = 0; y < L; ++y){
        for(int x = 0; x <L; ++x){
            temp[y][x] = map[L - 1 - x + sy][y + sx];
        }
    }
    for(int y = 0; y < L ;++y){
        for(int x = 0; x <L; ++x){
            map[sy + y][sx + x] = temp[y][x];
        }
    }
}

void solve(int L){
    L = (1 << L);
    for(int y = 0; y < N; y+=L){
        for(int x = 0; x < N; x+=L){
            rotate(y, x, L);
        }
    }
    memset(checkMelt,false,sizeof(checkMelt));
    
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < N; ++x){
            if(map[y][x] == 0) continue;
            int count = 0;
            for(int dir = 0; dir < 4; ++dir){
                int ny = y + dy[dir];
                int nx = x + dx[dir];
                if(ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
                if(map[ny][nx] != 0) ++count;
            }
            if(count <3) checkMelt[y][x] = true;
        }
    }
    for(int y= 0; y <N; ++y){
        for(int x = 0; x< N; ++x){
            if(checkMelt[y][x]) map[y][x]--;
        }
    }
}

int bfs(int y, int x){
    queue<int> q;
    q.push(100 * y + x);
    visited[y][x] = true;
    int sum = 1;

    while(!q.empty()){
        int cur = q.front(); q.pop();
        int cy = cur / 100;
        int cx = cur % 100;
        for(int dir = 0; dir < 4; ++dir){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || ny >= N || nx <0 || nx >= N) continue;
            if(map[ny][nx] == 0 || visited[ny][nx]) continue;
            ++sum;
            visited[ny][nx] = true;
            q.push(ny*100 + nx);
        }
    }
    return sum;
}

int getSum(){
    int ret = 0;
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < N; ++x){
            ret += map[y][x];
        }
    }
    return ret;
}
int getBiggest(){
    int ret = 0;
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < N; ++x){
            if(map[y][x] == 0 || visited[y][x]) continue;
            int candi = bfs(y, x);
            if(candi > ret){
            ret = candi;
            }
        }
    }
    if(ret == 1) ret = 0;
    return ret;
}
int main(){

    input();
    for(int i = 0; i < Q; ++i){
        int L; cin >> L;
        solve(L);
    }
    cout<<getSum()<<'\n';
    cout<<getBiggest()<<'\n';
    return 0;
}