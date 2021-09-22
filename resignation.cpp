#include<iostream>
#include<algorithm>
#include<climits>

using namespace std;

int n;
int t[15];
int p[15];
int cache[15];

int solve(int day){

    if(day > n ) return INT_MIN;
    if(day == n) return 0;

    int& ret = cache[day];
    if(ret != -1) return ret;

    ret = max(solve(day+1), solve(day+t[day]) + p[day]);
    return ret;
}

int main(){

    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> t[i] >> p[i];
        cache[i] = -1;
    }
    
    int answer = solve(0);

    cout << answer << endl;
    return 0;
}