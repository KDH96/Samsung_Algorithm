#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
 
struct ROAD
{
    int y, x, count;
};
 
int N, K;
int map[8][8];
ROAD high[5];
int high_idx;
const int dy[] = {0, 0, -1, +1};
const int dx[] = {-1, +1, 0, 0};
 
void init(){
    for(int i = 0; i < 5; ++i){
        high[i].y = 0;
        high[i].x = 0;
        high[i].count = 0;
    }
    high_idx = 0;
}
 
int simul(int m){
    bool visited[8][8] = {false,};
    queue<ROAD>q;
    q.push(high[m]);
    visited[high[m].y][high[m].x] = true;
    int ret = 0;
    while(!q.empty()){
        ROAD cur = q.front(); q.pop();
        if(ret < cur.count){
            ret = cur.count;
        }
        int cy = cur.y;
        int cx = cur.x;
         
        for(int dir = 0; dir < 4; ++dir){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            int nt = cur.count + 1;
            if(ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
            if(map[ny][nx] >= map[cy][cx]) continue;
            visited[ny][nx] = true;
            q.push({ny ,nx, nt});
        }
    }
    return ret;
}
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
 
    cin>>T;
    for(test_case = 1; test_case <= T; ++test_case)
    {
        init();
        int max_v = 0;
        cin >> N >> K;
        for(int y = 0; y < N; ++y){
            for(int x = 0; x<N; ++x){
                cin >> map[y][x];
                if(map[y][x] > max_v){
                    max_v = map[y][x];
                }
            }
        }
 
        for(int y = 0; y < N; ++y){
            for(int x = 0; x<N; ++x){
                    if(max_v == map[y][x]){
                        high[high_idx].y = y;
                        high[high_idx].x = x;
                        high[high_idx++].count = 0;
                    }
                }
        }
        
            int ans = 0;
            for(int i = 1; i <= K; ++i){
                for(int y = 0; y < N; ++y){
                    for(int x = 0; x < N; ++x){
                        map[y][x] -= i;
                        for(int m = 0; m < high_idx;++m){
                             int candi = simul(m);
                             if( ans < candi)  ans = candi;
                        }
                        map[y][x] +=i;
                    }
                }
            }
        cout << "#" << test_case << " "<< ans + 1 << "\n";
    }
 
 
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}