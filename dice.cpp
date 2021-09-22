#include<iostream>
using namespace std;

int n, m, k, r, c;
int deploy[4][3];
int map[20][20];
int dice[7];
int cmd[1000];

const int dy[] = {0, 0, -1, +1};
const int dx[] = {+1, -1, 0, 0};

int main(){
    
    cin >> n >> m >> r >> c >> k;
    
    for(int y = 0; y<n; ++y){
        for(int x = 0; x<m ; ++x){
            cin >> map[y][x];
        }
    }
    for(int i =0; i<k; i++){
        cin >> cmd[i];
    }
    deploy[0][1] = 2, deploy[1][0] = 4 , deploy[1][1] = 1, deploy[1][2] = 3;
    deploy[2][1] = 5, deploy[3][1] = 6;

    for(int i = 0; i<k ; i++)
    {
        int dir = cmd[i] - 1;
        r += dy[dir]; c += dx[dir];

        if(r < 0 || r > n-1 || c < 0 || c > m-1 ){
            r -= dy[dir]; c -= dx[dir];
            continue;
        }
        switch (dir) {
            case 0: {// µ¿
                int temp = deploy[1][2];
                int temp2 = deploy[3][1];
                for(int j = 2; j>0;j--){
                    deploy[1][j] = deploy[1][j-1];
                }
                deploy[1][0] = temp2;
                deploy[3][1] = temp;
                break;
            }
            case 1:{ // ¼­
                int temp = deploy[1][0];
                int temp2 = deploy[3][1];
                for(int j = 0; j<2;j++){
                    deploy[1][j] = deploy[1][j+1];
                }
                deploy[1][2] = temp2;
                deploy[3][1] = temp;
                break;
            }
            case 2: {// ºÏ
                int temp = deploy[0][1];
                for(int j = 0; j<3;j++){
                    deploy[j][1] = deploy[j+1][1];
                }
                deploy[3][1] = temp;
                break;
            }            
            case 3:{ // ³²
                int temp = deploy[3][1];
                for(int j = 3; j>0;j--){
                    deploy[j][1] = deploy[j-1][1];
                }
                deploy[0][1] = temp;
                break;
        }             
            default: 
                break;
        }
        
        if( map[r][c] != 0 ){
            dice[deploy[3][1]] = map[r][c];
            map[r][c] = 0;
        }
        else{
            map[r][c] = dice[deploy[3][1]];
        }
        printf("%d\n", dice[deploy[1][1]]);
    }

    return 0;
}