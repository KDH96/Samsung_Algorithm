#include<iostream>
#include<deque>
using namespace std;

int N, K;
int A[2][200];
deque<int> belt;
deque<bool> check;

int main(){
    cin >> N >> K;
	int x;
    for(int i = 0; i < 2*N; ++i){
		cin >> x;
		belt.push_back(x);
		check.push_back(false);
    }
    int size = 2*N;
    int ret = 0;
	int count = 0;
    while(count < K){
        ++ret;
        //È¸Àü
		belt.push_front(belt.back());
		belt.pop_back();
		check.push_front(check.back());
		check.pop_back();
        if(check[N - 1]){
            check[N -1] = false;
        }
        // ·Îº¿ ÀÌµ¿
        for(int i = N - 2 ; i >= 0; --i){
            if(!check[i]) continue;
            if((belt[i + 1] >= 1) && !check[i+1] ){
                check[i + 1] = true;
                check[i] = 0;
                belt[i + 1] -= 1;
				if(belt[i + 1] == 0){
					++count;
				}
            }
            if(i == N - 2){
                check[i + 1] = 0;
            }
        }      
        //·Îº¿ ÀûÀç
        if(belt[0] != 0 && !check[0]){
            check[0] = true;
            belt[0] -= 1;
			if(belt[0] == 0){
				++count;
			}
        }
    }
    cout << ret << endl;
    return 0;
}