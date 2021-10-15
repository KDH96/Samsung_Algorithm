#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

struct Tree
{
    int y, x, age;
};

queue<Tree> q[2];
queue<Tree> new_tree;
queue<Tree> dead; queue<Tree> parent;
Tree init_tree[100];

int n, m, k, ret;
int map[10][10];
int A[10][10];


const int dy[] = {-1, +1, 0, 0, -1, -1, +1, +1};
const int dx[] = {0, 0, -1, +1, -1, +1, -1, +1};

bool cmp(Tree& a, Tree& b){
    return (a.age < b.age);
}

int main(){

    cin >> n >> m >> k;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < n; ++x){
            cin >> A[y][x];
            map[y][x] = 5;
        }
    }
    
    for(int i = 0; i < m; ++i){
        cin >> init_tree[i].y >> init_tree[i].x >> init_tree[i].age;
        --init_tree[i].x, --init_tree[i].y;
    }
    //오름차 정렬
    sort(init_tree, init_tree + m, cmp);

    int cur = 0, next = 0;
    for(int i = 0; i < m; ++i){
        q[cur].push(init_tree[i]);
    }
    
    for(int i = 0; i < k; ++i){
        next = (cur + 1) % 2;

        while(!new_tree.empty()){
            Tree cur_tree = new_tree.front(); new_tree.pop();
            if(map[cur_tree.y][cur_tree.x] >= cur_tree.age){
                map[cur_tree.y][cur_tree.x] -= cur_tree.age;

                ++cur_tree.age;
                q[next].push(cur_tree);
            }
            else{
                dead.push(cur_tree);
            }
        }

        while(!q[cur].empty()){
            Tree cur_tree = q[cur].front(); q[cur].pop();
            if(map[cur_tree.y][cur_tree.x] >= cur_tree.age){
                map[cur_tree.y][cur_tree.x] -= cur_tree.age;
                ++cur_tree.age;
                q[next].push(cur_tree);

                if((cur_tree.age % 5) == 0){
                    parent.push(cur_tree);
                }
            }
            else{
                dead.push(cur_tree);
            }
        }

        while(!dead.empty()){
            Tree cur_tree = dead.front(); dead.pop();
            map[cur_tree.y][cur_tree.x] += (cur_tree.age / 2);
        }

        while(!parent.empty()){
            Tree cur_tree = parent.front(); parent.pop();

            for(int dir = 0; dir < 8; ++dir){
                Tree next_tree;
                next_tree.y = cur_tree.y + dy[dir];
                next_tree.x = cur_tree.x + dx[dir];
                next_tree.age = 1;
                if(next_tree.y < 0 || next_tree.y >= n 
                || next_tree.x < 0 || next_tree.x >= n ) continue;
                new_tree.push(next_tree);
            }
        }

        for(int y = 0; y < n; ++y){
            for(int x = 0; x < n; ++x){
                map[y][x] += A[y][x];
            }
        }
        cur = next;
    }
    // 살아남은 나무
    ret = int(q[cur].size() + new_tree.size());

    cout << ret << endl;
    return 0;
}