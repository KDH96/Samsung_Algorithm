#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct CORDI
{
    int y, x;
};

int n, m, type, ret;
vector<CORDI> house, shop, pick;

void dfs(int close){
    if( m == pick.size() ){
        int candi = 0;
        for(int k = 0; k < house.size(); ++k){
            int min_dist = 0x7fffffff;
            for(int j = 0; j < pick.size(); ++j){
                min_dist = min(min_dist,
                    abs(house[k].y - pick[j].y) + abs(house[k].x - pick[j].x));
            }
            candi += min_dist;
        }
        ret = min(ret, candi);
        return;
    }
    for(int i = close; i < shop.size(); ++i){
        pick.push_back(shop[i]);
        dfs(i + 1);
        pick.pop_back();
    }
}

int main(){
    cin >> n >> m;
    CORDI target;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < n; ++x){
            cin >> type;
            if( type == 1){
                target.y = y; target.x = x;
                house.push_back(target);
            }
            else if(type == 2){
                target.y = y; target.x = x;
                shop.push_back(target);
            }
        }
    }
    ret = 0x7fffffff;
    dfs(0);
    cout << ret << endl;

    return 0;
}