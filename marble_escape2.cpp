#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct INFO{
    int rx, ry, bx, by, cnt ; 
};

INFO start;
//문자열 종료문자까지 저장하기 위해 x를 11로 설정.
char map[10][11];
int bfs(){
    // 네 방향 문제 기본 설정
    const int dy[] = { -1, 1, 0, 0};
    const int dx[] = { 0, 0, -1, 1};
    //방문했는지 표시를 위함.
    int visited[10][10][10][10] = { 0, };
    queue<INFO> q;
    q.push(start);
    visited[start.ry][start.rx][start.by][start.bx] = 1;
    
    int ret = -1;
    while (!q.empty()) {
        INFO cur = q.front(); q.pop();
        // 탈출 조건
        if (cur.cnt > 10 ) break;
        if (map[cur.ry][cur.rx] == 'O' && map[cur.by][cur.bx] != 'O'){
            ret = cur.cnt;
            break;
        }
        //공 이동
        for(int dir =0; dir<4; ++dir){
            int next_ry = cur.ry;
            int next_rx = cur.rx;
            int next_by = cur.by;
            int next_bx = cur.bx;

            while(1){
                if(map[next_ry][next_rx] != '#' && map[next_ry][next_rx] != 'O'){
                    next_ry += dy[dir], next_rx += dx[dir];
                }
                else{
                    if (map[next_ry][next_rx] == '#'){
                        next_ry -= dy[dir], next_rx -= dx[dir];
                    }
                    break;
                }
            }
            while(1){
                if(map[next_by][next_bx] != '#' && map[next_by][next_bx] != 'O'){
                    next_by += dy[dir], next_bx += dx[dir];
                }
                else{
                    if (map[next_by][next_bx] == '#'){
                        next_by -= dy[dir], next_bx -= dx[dir];
                    }
                    break;
                }
            }
            // 공이 같은 위치에 있는 경우 처리
            if(next_ry == next_by && next_rx == next_bx) {
                if (map[next_ry][next_rx] != 'O'){
                    int red_dist = abs(next_ry - cur.ry) + abs(next_rx - cur.rx);
                    int blue_dist = abs(next_by - cur.by) + abs(next_bx - cur.bx);
                    if (red_dist > blue_dist) {
                        next_ry -= dy[dir], next_rx -= dx[dir];
                    }
                    else{
                        next_by -= dy[dir], next_bx -= dx[dir];
                    }
                }
            }

            if(visited[next_ry][next_rx][next_by][next_bx] == 0){
                visited[next_ry][next_rx][next_by][next_bx] = 1;
                INFO next;
                next.ry = next_ry;
                next.rx = next_rx;
                next.by = next_by;
                next.bx = next_bx;
                next.cnt = cur.cnt + 1;
                q.push(next);
            }
        }
    }

    return ret;
}

int main(){
    //문자열 입력 받는 부분.
    int n, m;
    cin >> n >> m ;
    for(int i=0; i<n;++i){
        cin >> map[i];
    }
    // 공의 좌표 찾기
    for(int y=0;y<n;++y){
        for(int x=0;x<m;++x){
            if(map[y][x] =='R'){
                start.rx = x, start.ry = y;
            }
            if(map[y][x] =='B'){
                start.bx = x, start.by = y;
            }            
        }
    }
    start.cnt = 0;
    int ret = bfs();
    cout << ret <<endl;

    return 0;
}