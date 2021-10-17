#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

struct CASE
{
    int y, x, d_1, d_2;
};
queue<CASE> q;

int n, ret;
int map[20][20];
int total;

void case_find(){
    CASE target;
    for(int y = 0; y < n - 2; ++y){
        for(int x = 1; x < n - 1; ++x){
            for(int d_1 = 1; d_1 < n ; ++d_1){
                for(int d_2 = 1; d_2 < n; ++d_2){
                    if((x - d_1) < 0 || (x + d_2) >= n || (y + d_1 + d_2) >= n)
                        continue;
                    target.y = y;
                    target.x = x;
                    target.d_1 = d_1;
                    target.d_2 = d_2;
                    q.push(target);
                }
            }
        }
    }
}

void simul(){
    case_find();

    while(!q.empty()){
        int sum[5] = { 0, };
        int area[20][20];
        for(int y = 0; y < n; ++y){
            for(int x = 0; x < n; ++x){
                area[y][x] = 5;
            }
        }

        CASE c = q.front(); q.pop();
        int ly = c.y + c.d_1; int lx = c.x - c.d_1;
        int ry = c.y + c.d_2; int rx = c.x + c.d_2;
        int dy = c.y + c.d_1 + c.d_2; int dx = c.x + c.d_2 - c.d_1;
        // 1번 구역과 그 경계선
        int line = c.x;
        bool flag = false;
        if( c.y == 0 ){
            line = c.x - 1;
            flag = true;
        }
        for(int y = 0; y < ly; ++y){
            for(int x = 0; x <= line; ++x){
                area[y][x] = 1;
                sum[0] += map[y][x];
            }
            if( (y + 1) == c.y){
                flag = true;
            }
            if(flag)
                --line;
        }
        //2번
        line = ry;
        flag = false;
        if( rx == n - 1 ){
            line = ry - 1;
            flag = true;
        }        
        for(int x = n - 1; x > c.x; --x){
            for(int y = 0; y <= line; ++y){
                area[y][x] = 2;
                sum[1] += map[y][x];
            } 
            if( (x - 1) == rx)
                flag = true;
            if(flag)
                --line;
        }
        //3번
        line = ly;
        flag = false;
        if( lx == 0 ){
            line = ly + 1;
            flag = true;
        }
        for(int x = 0; x < dx; ++x){
            for(int y = n - 1; y >= line; --y){
                area[y][x] = 3;
                sum[2] += map[y][x];
            } 
            if( (x + 1) == lx)
                flag = true;
            if(flag)
                ++line;
        }
        //4번
        line = dx;
        flag = false;
        if( dy == n - 1 ){
            line = dx + 1;
            flag = true;
        }
        for(int y = n - 1; y > ry; --y){
            for(int x = n - 1; x >= line; --x){
                area[y][x] = 4;
                sum[3] += map[y][x];
            }
            if( (y - 1) == dy){
                flag = true;
            }
            if(flag)
                ++line;
        }
        //5번
        // for(int y = c.y; y <= dy; ++y){
        //     for(int x = lx; x <= rx; ++x){
        //         if(area[y][x] == 5) sum[4] += map[y][x];
        //     }
        // }
        int total_sum = total;
        total_sum  -= sum[0];
        total_sum  -= sum[1];
        total_sum  -= sum[2];
        total_sum  -= sum[3];
        sum[4] = total_sum;
        // for(int y = 0; y < n; ++y){
        //     for(int x = 0; x < n; ++x){
        //         cout << area[y][x];
        //     }
        //     cout << "\n";
        // }
        // cout << "------------" << "\n";
        // cout << "------------" << endl;

        
        int maxp = 0; int mip = 0x7fffffff;
        for(int i = 0; i < 5; ++i){
            maxp = max(maxp, sum[i]);
            mip = min(mip, sum[i]);
        }
        int candi = maxp - mip;
        ret = min(ret, candi);
    }
}

int main(){
    cin >> n;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < n; ++x){
            cin >> map[y][x];
            total += map[y][x];
        }
    }
    ret = 0x7fffffff;

    simul();
    cout << ret << endl;
    return 0;
}