#include<iostream>

using namespace std;

int n, b, c;
int place[1000000];
int supervisor[1000000];

int main(){
    cin >> n;
    for(int i =0; i<n; i++){
        cin >> place[i];
    }
    cin >> b >> c;
    long long sum = 0;
    for(int i = 0; i < n ; i++){
        int student = place[i];
        int val = student - b ; 
        if(val <= 0){
            supervisor[i] = 1;
        }
        else{
            int x = val / c ;
            if( (val % c) != 0 ) x += 1;
            supervisor[i] = 1 + x;
        }
    }
    for(int i = 0; i < n ; i++){
        sum = sum + supervisor[i];
    }
    cout << sum << endl;
    return 0;
}