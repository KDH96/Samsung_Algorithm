#include<iostream>
#include<queue>
using namespace std;

struct TAXI{
    int pos, count;
};
struct CUSTOMER{
    int start, end;
};
int N, M, fuel;
int map[20][20];
int taxi_y, taxi_x;
CUSTOMER customer[400];
const int dy[] = {-1, 0, +1, 0};
const int dx[] = {0, -1, 0, +1};

const int WALL = -1;
const int EMT = -2;

int search_bfs(){
    bool visited[20][20] = {false,};
    queue<TAXI> q;
    TAXI cur = {100 * taxi_y + taxi_x, 0};
    q.push(cur);

    visited[taxi_y][taxi_x] = true;

    int candi_size = 0;
    int candi[400] = {0,};
    int candi_count = -1;

    while(!q.empty()){
        cur = q.front(); q.pop();
        if(candi_count != -1 && candi_count < cur.count){
            break;
        }
        int cy = cur.pos / 100; 
        int cx = cur.pos % 100;

        if(map[cy][cx] >= 0){
            candi[candi_size++] = map[cy][cx];
            candi_count = cur.count;
        }
        for(int dir = 0; dir < 4; ++dir){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || ny >= N || nx < 0 || nx >= N 
                    || map[ny][nx] == WALL || visited[ny][nx]){
                continue;
            }
            visited[ny][nx] = true;
            q.push({100*ny + nx, cur.count + 1});
        }
    }
    if(fuel < candi_count){ // 연료 부족
        return -1;
    }
    int candi_val = 10000;
    int target = -1;
    for(int i = 0; i < candi_size; ++i){
        if(candi_val > customer[candi[i]].start){
            candi_val = customer[candi[i]].start;
            target = candi[i];
        }
    }
    taxi_y = customer[target].start / 100;
    taxi_x = customer[target].start % 100;
    map[taxi_y][taxi_x] = EMT;
    fuel -= candi_count;
    return target;
}

bool move_bfs(int who){
    bool visited[20][20] = {false,};
    queue<TAXI> q;
    TAXI cur = {100*taxi_y + taxi_x, 0 };
    q.push(cur);
    visited[taxi_y][taxi_x] = true;

    while(!q.empty()){
        cur = q.front(); q.pop();
        if(cur.count > fuel){
            return false;
        }
        if(cur.pos == customer[who].end){
            taxi_y = cur.pos / 100;
            taxi_x = cur.pos % 100;
            fuel += cur.count;
            return true;
        }
        int cy = cur.pos / 100;
        int cx = cur.pos % 100;
        for(int dir = 0; dir < 4 ; ++dir){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || ny >= N || nx < 0 || nx >= N 
                    || map[ny][nx] == WALL || visited[ny][nx]){
                continue;
            }
            visited[ny][nx] = true;
            q.push({100*ny + nx, cur.count + 1});
        }
    }
    return false; // 도착 못함
}

int solve(){
    int ret = -1;

    for(int i = 0; i < M; ++i){
        int target = search_bfs();
        if(target == -1){
            return ret;
        }
        bool sucess = move_bfs(target);
        if(!sucess){
            return ret;
        }
    }
    ret = fuel;
    return ret;
}

int main(){
    cin >> N >> M >> fuel;
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < N; ++x){
            cin >> map[y][x];
            map[y][x] -= 2;
        }
    }
    cin >> taxi_y >> taxi_x;
    --taxi_y, --taxi_x;
    for(int i = 0; i < M; ++i){
        int sy, sx, dey, dex;
        cin >> sy >> sx >> dey >> dex;
        --sy, --sx, --dey, --dex;
        map[sy][sx] = i;
        customer[i].start = (100 * sy + sx); 
        customer[i].end = (100 * dey + dex);
    }

    int ret = solve();

    cout << ret << endl;
    return 0;
}