#include<iostream>
using namespace std;

int N, L, ret;
int map[200][100];


int main(){

    cin >> N >> L;
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < N; ++x){
            cin >> map[y][x];
        }
    }
    for(int y = 0; y < N; ++y){
        for(int x = 0 ; x < N; ++x){
            map[N + y][x] = map[x][y];
        }
    }
    
    for(int i = 0; i < 2 * N; ++i){
        int count = 1;
        bool flag = true;
        for(int j = 0; j < N - 1; ++j){
            if(map[i][j] == map[i][j + 1]) ++count;
            else if(map[i][j] == (map[i][j + 1] - 1) && count >= L){
                count = 1;
            }
            else if(map[i][j] == (map[i][j + 1] + 1) && count >= 0){
                count = (1 - L);
            }
            else{
                flag = false;
                break;
            }
        }
        if(flag && count >= 0){
            ++ret;
        }
    }

    cout << ret << endl; 
    return 0;
}