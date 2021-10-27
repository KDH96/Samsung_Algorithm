#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

struct POS
{
    int y, x;
};

int map[50][50];
bool dis_cloud[50][50];
int N, M;
vector<POS> v;
vector<POS> inc_water; 
const int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
const int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};

void magic(){
    for(int i = 0; i < inc_water.size(); ++i){
        POS target = inc_water[i];
        int count = 0;
        for(int dir = 0; dir < 8; ++dir){
            if(dir % 2 == 0) continue;
            int ny = target.y + dy[dir]; 
            int nx = target.x + dx[dir];
            if(ny < 0 || ny >= N || nx <0 || nx >=N) continue;
            if(map[ny][nx] > 0){
                ++count;
            }
        }
        map[target.y][target.x] += count;
    }
}

void make_cloud(){
    for(int y = 0; y < N; ++y){
        for(int x = 0; x <N; ++x){
            if(dis_cloud[y][x]) continue;
            if(map[y][x] >= 2){
                v.push_back({y, x});
                map[y][x] -= 2;
            }
        }
    }
}

void solve(int d, int s){
    //move
    for(int i = 0; i < v.size(); ++i){
        v[i].y = (v[i].y + (s*dy[d]) + N) % N;
        v[i].x = (v[i].x + (s*dx[d]) + N) % N;
        map[v[i].y][v[i].x] += 1;
        dis_cloud[v[i].y][v[i].x] = true;
    }
    inc_water = v;
    //dismiss
    v.clear();

    magic();
    make_cloud();
}

int get_sum(){
    int sum = 0;
    for(int y = 0; y < N; ++y){
        for(int x= 0; x <N; ++x){
            sum += map[y][x];
        }
    }
    return sum;
}

int main(){
    cin >> N >> M;
    for(int y = 0; y < N; ++y){
        for(int x = 0; x <N; ++x){
            cin >> map[y][x];
        }
    }

    v.push_back({N-1 ,0});
    v.push_back({N-1 ,1});
    v.push_back({N-2 ,0});
    v.push_back({N-2 ,1});

    while(M--){
        int s, d;
        cin >> d >> s;
        --d;
        s %= N;
        memset(dis_cloud, false, sizeof(dis_cloud));
        solve(d, s);
    }
    int ret = get_sum();
    cout << ret << endl;
    return 0;
}