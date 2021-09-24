#include<iostream>

using namespace std;

int n, m;
int map[503][503];
const char block[19][4][5] = {
    {
        "1111",
        "0000",
        "0000",
        "0000",
    },
    {
        "1000",
        "1000",
        "1000",
        "1000",
    },
    {
        "1100",
        "1100",
        "0000",
        "0000",
    },
    {
        "1000",
        "1000",
        "1100",
        "0000",
    },
    {
        "0100",
        "0100",
        "1100",
        "0000",
    },
    {
        "1110",
        "1000",
        "0000",
        "0000",
    },
    {
        "1000",
        "1110",
        "0000",
        "0000",
    },
        {
        "1100",
        "0100",
        "0100",
        "0000",
    },
        {
        "1100",
        "1000",
        "1000",
        "0000",
    },
        {
        "0010",
        "1110",
        "0000",
        "0000",
    },
        {
        "1110",
        "0010",
        "0000",
        "0000",
    },
        {
        "1000",
        "1100",
        "0100",
        "0000",
    },
        {
        "0100",
        "1100",
        "1000",
        "0000",
    },
        {
        "0110",
        "1100",
        "0000",
        "0000",
    },
        {
        "1100",
        "0110",
        "0000",
        "0000",
    },
        {
        "1110",
        "0100",
        "0000",
        "0000",
    },
        {
        "0100",
        "1100",
        "0100",
        "0000",
    },
        {
        "0100",
        "1110",
        "0000",
        "0000",
    },
        {
        "1000",
        "1100",
        "1000",
        "0000",
    }
};

int get_sum(int sy, int sx, int k){

    int ret = 0;
    for(int y = 0; y < 4 ; y++){
        for(int x = 0; x < 4 ; x++){
            ret += (block[k][y][x] - '0') * map[y + sy][x + sx];
        }
    }
    return ret;
}

int main(){

    cin >> n >> m;
    for(int y = 0; y < n; y++){
        for( int x = 0; x < m; x++){
            cin >> map[y][x];
        }
    }
    for(int y = n; y< n+3 ; y++){
        for(int x =0; x< m+3; x++){
            map[y][x] = -100000;
        }
    }
    for(int y = 0; y < n+3 ; y++){
        for(int x = m; x < m+3; x++){
            map[y][x] = -100000;
        }
    }
    int ret = 0;
    for(int y = 0; y < n ; y++ ){
        for(int x =0; x < m; x++){
            for(int k = 0; k<19;k++){
                int candi = get_sum(y, x, k);
                if(ret < candi){
                    ret = candi;
                }
            }
        }
    }
    
    cout << ret << endl;
    return 0;
}