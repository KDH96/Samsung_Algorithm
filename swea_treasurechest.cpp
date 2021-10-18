#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;

char in[29];
int N, K;

int what_ch(char f){
    int ret = 0;
    if(f < 'A')
        ret = f - '0';
    else {
        if( f == 'A'){
            ret = 0x0a;
        } else if (f == 'B'){
            ret = 0x0b;
        } else if (f == 'C'){
            ret = 0x0c;
        } else if (f == 'D'){
            ret = 0x0d;
        } else if (f == 'E'){
            ret = 0x0e;
        } else if (f == 'F'){
            ret = 0x0f;
        }
    }
    return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        // in �ʱ�ȭ �ʿ�?
        cin >> N >> K;
        cin >> in;
        int ret = 0;
        int candi[28] = {0,};
        int candi_idx = 0;
        int slice = N / 4;

        for(int i = 0; i < slice; ++i){
            // �� ���� ����
            for(int y = 0; y < 4; ++y){
                int start_idx = y * slice;
                int sum = 0;
                for(int x = 0; x < slice; ++x){
                    char f = in[start_idx + x];
                    int num = what_ch(f);
                    num = (num << (4 * (slice - 1 - x)));
                    sum += num;
                }
                candi[candi_idx++] = sum;
                for(int m = 0; m < 16; ++m){
                    if(candi[m] == sum && candi_idx - 1 != m){
                        candi[--candi_idx] = 0;
                        break;
                    }
                }
            }
            // ȸ�� ���.
            char temp[29] = "";
            for(int y = 0; y < N; ++y){
                temp[(y + 1 + N) % N] = in[y]; // +1�� �̵��Ϸ��� ĭ�� ���� �ݴ� ������ ���� -1
            }
            for(int y = 0; y < N; ++y){
                in[y] = temp[y];
            }
        }

        sort(candi, candi + candi_idx , greater<int>());
        ret = candi[K - 1];
        cout << "#" << test_case << " " << ret << "\n";
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}