#include<iostream>
#include<queue>

using namespace std;

void rotate(int n, int dir);
void simul(int y, int x);
int k;
char gear[4][9];

int main(){
    for(int y = 0; y < 4; ++y){
        cin >> gear[y];
    }

    cin >> k;

    queue<pair<int, int>> q;
    int target, cmd;

    for(int i = 0; i < k; ++i){
        cin >> target >> cmd;
        q.push(make_pair(target, cmd));
    }
    


    while(!q.empty())
    {
        pair<int, int> p = q.front(); q.pop();
        target = p.first; 
        cmd = p.second;
        simul(target-1,cmd);
    }

    int ans = 0;
    for(int i = 0; i < 4; ++i){
        if( gear[i][0] == '1') 
            ans += (1 << i);
    }

    cout << ans << endl;
    return 0;
}

void simul(int n, int x){

switch (n)
        {
        case 0:
            if(gear[0][2] == gear[1][6]) rotate(0,x);
            else if(gear[1][2] == gear[2][6]){
                rotate(0,x);
                rotate(1,-x);
            }
            else if(gear[2][2] == gear[3][6]){
                rotate(0,x);
                rotate(1,-x);
                rotate(2,x);
            }
            else{
                rotate(0,x);
                rotate(1,-x);
                rotate(2,x);
                rotate(3,-x);
            }
            break;
        case 1:
            if(gear[0][2] != gear[1][6]){
                rotate(0,-x);
            }
            if(gear[1][2] == gear[2][6]) rotate(1,x);
            else if( gear[2][2] == gear[3][6]){
                rotate(1,x);
                rotate(2,-x);
            }
            else{
                rotate(1,x);
                rotate(2,-x);
                rotate(3,x);
            }
            break;
        case 2:
            if(gear[2][2] != gear[3][6]){
                rotate(3,-x);
            }
            if(gear[1][2] == gear[2][6]) rotate(2,x);
            else if( gear[0][2] == gear[1][6]){
                rotate(2,x);
                rotate(1,-x);
            }
            else{
                rotate(2,x);
                rotate(1,-x);
                rotate(0,x);
            }            
            break;
        case 3:
            if(gear[3][6] == gear[2][2]) rotate(3,x);
            else if(gear[2][6] == gear[1][2]){
                rotate(3,x);
                rotate(2,-x);
            }
            else if(gear[1][6] == gear[0][2]){
                rotate(3,x);
                rotate(2,-x);
                rotate(1,x);
            }
            else{
                rotate(3,x);
                rotate(2,-x);
                rotate(1,x);
                rotate(0,-x);
            }
            break;                                
        default:
            break;
        }

}


void rotate(int n, int dir){

    char temp;
    switch (dir)
    {
    case 1: // 시계방향
        temp = gear[n][7];
        for(int i = 7; i > 0; --i){
            gear[n][i] = gear[n][i-1];
        }
        gear[n][0] = temp;
        break;
    case -1:
        temp = gear[n][0];
        for(int i = 0; i < 7; ++i){
            gear[n][i] = gear[n][i+1];
        }
        gear[n][7] = temp;    
        break;
    default: 
        break;
    }

}
