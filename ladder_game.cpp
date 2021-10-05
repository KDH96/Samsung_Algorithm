#include<iostream>
using namespace std;

int n, m, h, ret;
int map[31][11];

bool check(){
    bool ret = true;

    for(int x = 1; x <=n; ++x){
        int pos = x;

        for(int y = 0; y <=h; ++y){
            if(map[y][pos] == 1){
                ++pos;
            } else if(map[y][pos -1] == 1){
                --pos;
            }
        }

        if(pos != x){
            ret = false;
            break;
        }
    }
    return ret;
}

void dfs( int count, int y, int x){
    if( count >= ret) return;
    if(check()){
        ret = count;
        return;
    }
    if(count == 3) return;
    for(int sy = y; sy <= h; ++sy){
        for(int sx = x; sx < n; ++sx){
            if(map[sy][sx] == 0 && map[sy][sx+1] == 0 && map[sy][sx-1] == 0){
                map[sy][sx] = 1;
                dfs(count + 1, sy, sx);
                map[sy][sx] = 0;
            }
        }
        x = 1;
    }
}

int main(){
    cin >> n >> m >> h;
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        map[a][b] = 1;
    }

    ret = 4;
    dfs(0, 1, 1);
    if(ret == 4) ret = -1;
    cout << ret << endl;
    
    return 0;
}