#include<iostream>
using namespace std;

int n;

int map[101][101];
int curve[1024];

const int dy[] = {0, -1, 0, +1};
const int dx[] = {+1, 0, -1, 0};

int main(){
    cin >> n;
    for(int i = 0; i < n; ++i){
        int x, y, g, d;
        cin >> x >> y >> d >> g;
        map[y][x] = 1;
        int curve_idx = 0;
        curve[curve_idx++] = d;

        for(int j = 0; j < g; ++j){
            for(int k = curve_idx - 1; k >= 0; --k){
                curve[curve_idx++] = ( curve[k] + 1 ) % 4;
            }
        }

        for(int j = 0; j < curve_idx; ++j){
            y += dy[curve[j]];
            x += dx[curve[j]];
            if(y < 0 || y > 100 || x < 0 || x > 100 )
                continue;    
            map[y][x] = 1;
        }
    }
    int ret = 0;
    for(int y = 0; y < 100; ++y){
        for(int x = 0; x < 100; ++x){
            if(map[y][x] == 1 && map[y + 1][x] == 1 && map[y][x + 1] == 1 && map[y + 1][x + 1] == 1)
                ++ret;
        }
    }
    cout << ret << endl;

    return 0;
}