#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int board[20][20] = {0,};
int n, ret;

int get_max(){
    int ret =0;
    for(int y =0; y<n; y++){
        for(int x = 0; x < n; x++){
            ret = max(ret,board[y][x]);
        }
    }
    return ret;
}
void move(int dir){
    int temp[20][20] ={0,};
    switch(dir){
        case 0: //up
            for(int x = 0; x<n; x++){
                bool flag = false; int target = -1;
                for(int y=0; y<n; y++){
                    if(board[y][x] == 0 ) continue;
                    if(flag && board[y][x] == temp[target][x]){
                        temp[target][x] *=2, flag =false;
                    }
                    else{
                        temp[++target][x] = board[y][x], flag = true;
                    }
                }
                // for(++target; target<n; ++target){
                //     temp[target][x] = 0;
                // }
                }
            memcpy(board,temp,sizeof(temp));
            break;
        case 1: // down
            for(int x = 0; x<n; x++){
                bool flag = false; int target = n;
                for(int y=n-1; y>-1; y--){
                    if(board[y][x] == 0 ) continue;
                    if(flag && board[y][x] == temp[target][x]){
                        temp[target][x] *=2, flag =false;
                    }
                    else{
                        temp[--target][x] = board[y][x], flag = true;
                    }
                }
                // for(++target; target<n; ++target){
                //     temp[target][x] = 0;
                // }
                }
            memcpy(board,temp,sizeof(temp));
            break;        
        case 2:// left
            for(int y = 0; y<n; y++){
                bool flag = false; int target = -1;
                for(int x=0; x<n; x++){
                    if(board[y][x] == 0 ) continue;
                    if(flag && board[y][x] == temp[y][target]){
                        temp[y][target] *=2, flag =false;
                    }
                    else{
                        temp[y][++target] = board[y][x], flag = true;
                    }
                }
                // for(++target; target<n; ++target){
                //     temp[target][x] = 0;
                // }
                }
            memcpy(board,temp,sizeof(temp));
            break;        
        case 3:// right
            for(int y = 0; y<n; y++){
                bool flag = false; int target = n;
                for(int x=n-1; x>-1; x--){
                    if(board[y][x] == 0 ) continue;
                    if(flag && board[y][x] == temp[y][target]){
                        temp[y][target] *=2, flag =false;
                    }
                    else{
                        temp[y][--target] = board[y][x], flag = true;
                    }
                }
                // for(++target; target<n; ++target){
                //     temp[target][x] = 0;
                // }
            }
            memcpy(board,temp,sizeof(temp));
            break;  
        default: break;
    }
}

void simulation(int cnt){
    if(cnt == 5) {
        int candi = get_max();
        if(ret < candi){
            ret = candi;
        }
        return ;
    }
    int temp[20][20];
    memcpy(temp, board, sizeof(board));

    for(int dir =0; dir<4; dir++){
        move(dir);
        simulation(cnt +1);
        memcpy(board, temp, sizeof(board));
    }

    return ;
}

int main(){

    cin >> n;
    for(int y =0; y<n; y++){
        for(int x = 0; x < n; x++){
            cin >> board[y][x];
        }
    }
    ret = 0;
    simulation(0);
    cout << ret << endl;
    return 0;
}