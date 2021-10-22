#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct POS
{
    int pos;
    int Nearly_empty;
    int Nearly_friend;
};

int N, ret;
int map[20][20];
int info[401][5];
int posi[401];

const int dy[] = {0, 0, -1, +1};
const int dx[] = {+1, -1, 0, 0};

bool cmp(POS a, POS b){
    if(a.Nearly_friend == b.Nearly_friend){
        if(a.Nearly_empty == b.Nearly_empty){
            if(a.pos < b.pos){
                return true;
            }
            return false;
        }
        else if(a.Nearly_empty > b.Nearly_empty){
            return true;
        }
        else{
            return false;
        }
    }
    else if(a.Nearly_friend > b.Nearly_friend){
        return true;
    }
    else{
        return false;
    }
}

void set_seat(){
    for(int i = 1; i <= N*N; ++i){
        vector<POS> candi;
        int student_num = info[i][0];
        for(int y = 0; y < N; ++y){
            for(int x = 0; x < N; ++x){
                if(map[y][x] != 0) continue; //빈자리가 아니면
                int Nearly_friend = 0;
                int Nearly_empty = 0;
                for(int d = 0; d < 4; ++d){ //인접한 칸 탐색
                    int ny = y + dy[d];
                    int nx = x + dx[d];
                    if(ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
                    if(map[ny][nx] != 0){
                        for(int k = 1; k < 5; ++k){
                            if(info[i][k] == map[ny][nx]){
                                ++Nearly_friend;
                                break;
                            }
                        }
                    }
                    else{
                        ++Nearly_empty;
                    }
                }
                candi.push_back({100 * y + x, Nearly_empty, Nearly_friend});
            }
        }
        sort(candi.begin(),candi.end(), cmp);
        int pick = candi[0].pos;
        int pick_y = pick / 100;
        int pick_x = pick % 100;
        //cout << student_num << ",,, (" << pick_y << ", " << pick_x << ") \n"; 
        map[pick_y][pick_x] = student_num;
        posi[student_num] = pick; // 앉은 학생의 좌표
    }
}

void solve(){
    set_seat();
/*
    for(int y = 0; y < N; ++y){
        for(int x= 0; x < N; ++x){
            cout << map[y][x];
        }
        cout << "\n";
    }
    cout << "\n";
*/
    for(int i = 1; i <= N*N; ++i){
        int student_num = info[i][0];
        int num = posi[student_num];
        int cy = num / 100;
        int cx = num % 100;
        //cout << student_num << ",,, (" << cy << ", " << cx << ") \n"; 
        int F = 0;
        for(int dir = 0; dir <4; ++dir){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || ny >=N || nx < 0 || nx >= N){
                continue;
            }
            for(int k = 1; k < 5; ++k){
                if(map[ny][nx] == info[i][k]){
                    ++F;
                    break;
                }
            }
        }
        if (F == 1) ret += 1;
        if (F == 2) ret += 10;
        if (F == 3) ret += 100;
        if (F == 4) ret += 1000;
    }
}

int main(){
    cin >> N;
    for(int y = 1; y <= N*N; ++y){
        for(int x =0; x < 5; ++x){
            cin >> info[y][x]; //1 ~ N 번으로 입력
        }//info[y][0] 에 우선순위에 따른 학생번호 
    }

    ret = 0;
    solve();
    cout << ret << endl;
    
    return 0;
}