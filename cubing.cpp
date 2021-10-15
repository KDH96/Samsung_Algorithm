#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int T, n;
vector<pair<char,char>> cmd;
char cube[6][3][4];
char temp[3][4];
char t[4];
const char color[] = "wyrogb";

void init(){
    cmd.clear();
    for(int z = 0; z < 6; ++z){
        for(int y = 0; y < 3; ++y){
            for(int x = 0; x < 3; ++x){
                cube[z][y][x] = color[z];
            }
        }
    }
}

void Input(){
    cin >> n;
    for(int i = 0; i < n; ++i){
        char b, c;
        cin >> b >> c;
        cmd.push_back(make_pair(b, c));
    }
}

void copy(int p){
    for(int y = 0; y < 3; ++y){
        for(int x = 0; x < 3; ++x){
            temp[y][x] = cube[p][y][x];
        }
    }
}
void cw(int p){
    copy(p);
    for(int y = 0; y < 3; ++y){
        for(int x = 0; x < 3; ++x){
            cube[p][y][2 - x] = temp[x][y];
        }
    }    
}
void ccw(int p){
    copy(p);
    for(int y = 0; y < 3; ++y){
        for(int x = 0; x < 3; ++x){
            cube[p][2- y][x] = temp[x][y];
        }
    } 
}
void rotateU(int k){
    for(int i = 0; i < 3; ++i) t[i] = cube[4][k][i];
    for(int i = 0; i < 3; ++i) cube[4][k][i] = cube[2][k][i];
    for(int i = 0; i < 3; ++i) cube[2][k][i] = cube[5][k][i];
    for(int i = 0; i < 3; ++i) cube[5][k][i] = cube[3][k][i];
    for(int i = 0; i < 3; ++i) cube[3][k][i] = t[i];
}
void rotateD(int k){
    for(int i = 0; i < 3; ++i) t[i] = cube[4][k][i];
    for(int i = 0; i < 3; ++i) cube[4][k][i] = cube[3][k][i];
    for(int i = 0; i < 3; ++i) cube[3][k][i] = cube[5][k][i];
    for(int i = 0; i < 3; ++i) cube[5][k][i] = cube[2][k][i];
    for(int i = 0; i < 3; ++i) cube[2][k][i] = t[i];
}
void rotateF(int k){
    int j = (k == 0) ? 2 : 0;
    for(int i = 0; i < 3; ++i) t[i] = cube[0][j][i];
    for(int i = 0; i < 3; ++i) cube[0][j][i] = cube[4][2 - i][j];
    for(int i = 0; i < 3; ++i) cube[4][i][j] = cube[1][k][i];
    for(int i = 0; i < 3; ++i) cube[1][k][i] = cube[5][2 - i][k];
    for(int i = 0; i < 3; ++i) cube[5][i][k] = t[i];
}
void rotateB(int k){
    int j = (k == 0) ? 2 : 0;
    for(int i = 0; i < 3; ++i) t[i] = cube[0][j][i];
    for(int i = 0; i < 3; ++i) cube[0][j][i] = cube[5][i][k];
    for(int i = 0; i < 3; ++i) cube[5][i][k] = cube[1][k][2 - i];
    for(int i = 0; i < 3; ++i) cube[1][k][i] = cube[4][i][j];
    for(int i = 0; i < 3; ++i) cube[4][i][j]= t[2 - i];
}
void rotateL(int k){
    int j = (k == 0) ? 2 : 0;
    for(int i = 0; i < 3; ++i) t[i] = cube[0][i][k];
    for(int i = 0; i < 3; ++i) cube[0][i][k] = cube[3][2 - i][j];
    for(int i = 0; i < 3; ++i) cube[3][i][j] = cube[1][2 - i][k];
    for(int i = 0; i < 3; ++i) cube[1][i][k] = cube[2][i][k];
    for(int i = 0; i < 3; ++i) cube[2][i][k] = t[i];
}
void rotateR(int k){
    int j = (k == 0) ? 2 : 0;
    for(int i = 0; i < 3; ++i) t[i] = cube[0][i][k];
    for(int i = 0; i < 3; ++i) cube[0][i][k] = cube[2][i][k];
    for(int i = 0; i < 3; ++i) cube[2][i][k] = cube[1][i][k];
    for(int i = 0; i < 3; ++i) cube[1][i][k] = cube[3][2 - i][j];
    for(int i = 0; i < 3; ++i) cube[3][i][j] = t[2 - i];
}

void rotate(char plane, char dir){
    switch (plane) {
        case 'U':
            if( dir == '+'){
                cw(0);
                rotateU(0);
            } else {
                ccw(0);
                rotateD(0);
            }
            break;
        case 'D':
            if( dir == '+'){
                cw(1);
                rotateD(2);
            } else {
                ccw(1);
                rotateU(2);
            }
            break;
        case 'F':
            if( dir == '+'){
                cw(2);
                rotateF(0);
            } else {
                ccw(2);
                rotateB(0);
            }
            break;
        case 'B':
            if( dir == '+'){
                cw(3);
                rotateB(2);
            } else {
                ccw(3);
                rotateF(2);
            }
            break;
        case 'L':
            if( dir == '+'){
                cw(4);
                rotateL(0);
            } else {
                ccw(4);
                rotateR(0);
            }
            break;
        case 'R':
            if( dir == '+'){
                cw(5);
                rotateR(2);
            } else {
                ccw(5);
                rotateL(2);
            }
            break;
        default:
            break;
    }
}

int main(void){
    cin >> T;

    for(int tc = 0; tc < T; ++tc)
    {
        init();
        Input();
        for(int i = 0; i < n; ++i){
            char dir = cmd[i].second;
            char plane = cmd[i].first;
            rotate(plane, dir);
        }  
        for(int y = 0; y < 3; ++y){
            for(int x = 0; x < 3; ++x){
                cout << cube[0][y][x];
            }
            cout << endl;
        }
    }
    return 0;
}