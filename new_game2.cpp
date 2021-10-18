#include<iostream>
using namespace std;

struct POS
{
    int y, x, d;
};

int n, k;
int board[12][12][5];
int color[12][12];
POS horse[10];
int pos_size;

const int dy[] = {0, 0, -1, +1};
const int dx[] = {+1, -1, 0, 0};

int main(){
    cin >> n >> k;
    for(int y = 0; y < n; ++y){
        for(int x = 0; x < n; ++x){
            cin >> color[y][x];
        }
    }
    for(int i = 0; i < k; ++i){
        int y, x, d;
        cin >> y >> x >> d;
        --y, --x, --d;
        horse[pos_size].y = y;
        horse[pos_size].x = x;
        horse[pos_size].d = d;
        int& size = board[y][x][0]; 
        board[y][x][++size] = pos_size;
        ++pos_size;
    }

    int ret = -1;
    int turn = 0;
    bool flag = false;    
    while(turn <= 1000 && ret == -1){
        ++turn;

        for(int i = 0; i < k; ++i){
            POS cur = horse[i];
            POS next;
            next.y = cur.y + dy[cur.d];
            next.x = cur.x + dx[cur.d];
            next.d = cur.d;

            if(next.y < 0 || next.y >= n || next.x < 0 || next.x >= n || color[next.y][next.x] == 2 ){
                next.d = (cur.d == 0 || cur.d == 2) ? (cur.d + 1) : (cur.d - 1);
                next.y = cur.y + dy[next.d];
                next.x = cur.x + dx[next.d];
                horse[i].d = next.d;
                if(next.y < 0 || next.y >= n || next.x < 0 || next.x >= n || color[next.y][next.x] == 2 ){
                    continue;
                }
            }
            int src = -1;
            int& cur_size = board[cur.y][cur.x][0];
            // cout << i << "\n";
            // cout << cur_size << "\n";
            for(int j = 1; j <= cur_size; ++j){
                if ( board[cur.y][cur.x][j] == i){
                    src = j;
                    break;
                } 
            }
            int move[5] = {0,};
            int& move_size = move[0];
            for(int j = src; j <= cur_size; ++j){
                move[++move_size] = board[cur.y][cur.x][j];
            }
            cur_size = src - 1;

            if(color[next.y][next.x] == 1){
                for(int j = 1; j <= move_size / 2; ++j){
                    int temp = move[j];
                    move[j] = move[move_size - j + 1];
                    move[move_size - j + 1] = temp;
                }
            }

            int& next_size = board[next.y][next.x][0];
            for(int j = 1; j <= move_size ; ++j){
                board[next.y][next.x][++next_size] = move[j];
                horse[move[j]].y = next.y;
                horse[move[j]].x = next.x;
                if(next_size >= 4 ){
                    ret = turn;
                    flag = true;
                    break;
                }
            }
            if(flag){
                break;
            }
        }
    }
    
    cout << ret << endl;
    return 0;
}