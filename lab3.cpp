#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;

struct POSI
{
    int y, x, time;
};

int n , m, ret;
int map[50][50];

vector<POSI> v;
int empty_count;

const int dy[] = {0, 0, -1, +1};
const int dx[] = {-1, +1, 0, 0};

int bfs(int pick[]){
    bool visited[50][50] = { false, };
    queue<POSI> vi;
    for(int i = 0; i < m; ++i){
        vi.push(v[pick[i]]);
        visited[v[pick[i]].y][v[pick[i]].x] = true;
    }

    int empty_cnt = empty_count;

    while(!vi.empty()){
        POSI cur = vi.front(); vi.pop();

        if(map[cur.y][cur.x] == 0){
            empty_cnt -= 1 ;
        }
        if(empty_cnt == 0) return cur.time;
        POSI next;
        next.time = cur.time + 1;
        for(int dir = 0; dir < 4; ++dir){
            int ny = cur.y + dy[dir];
            int nx = cur.x + dx[dir];
            if(ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
            if(map[ny][nx] != 1 && !visited[ny][nx]){
                visited[ny][nx] = true;
                next.y = ny; next.x = nx;
                vi.push(next);
            }
        }
    }
    return 0x7fffffff;
}

void dfs(int last_pick, int pick_count, int virus_size, int pick[]){
    if( m == pick_count ){
        int candi = bfs(pick);
        ret = min(ret, candi);
        return;
    }
    for(int i = last_pick + 1; i < virus_size; ++i){
        pick[pick_count] = i ; 
        dfs(i, pick_count + 1, virus_size, pick);
    }
}

int main(){
    cin >> n >> m;
    POSI target;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < n; ++x){
            cin >> map[y][x];
            if(map[y][x] == 2){
                target.y = y;
                target.x = x;
                target.time = 0;
                v.push_back(target);
            } else if( map[y][x] == 0){
                ++empty_count;
            }
        }
    }
    
    ret = 0x7fffffff;
    int pick[10] = { 0,};
    dfs(-1, 0, v.size(), pick);

    if(ret == 0x7fffffff){
        cout << "-1" << endl;
    }
    else{
        cout << ret << endl;
    }

    return 0;
}