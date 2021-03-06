// 진수의 홀수 약수

//#define _CRT_SECURE_NO_WARNINGS

#define MAX_VALUE 1000001

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

long long ary[MAX_VALUE] = { 0 };

int main()
{
	std::ios::sync_with_stdio(false);

	int T;
	int caseCount;

	//freopen("sample_input.txt", "r", stdin);
	
	//vector<long long> ary(MAX_VALUE);

	//ary = new long long[MAX_VALUE];

	/*for (int i = 1; i < 1000001; i++) {
		ary[i] = 0;
	}*/

	for (int i = 1; i < MAX_VALUE; i++) {
		// 홀수일 경우
		if (i % 2 == 1) {
			// R까지 올라가면서 본인의 배수 항에 본인을 더함
			for (int j = 1; i * j < MAX_VALUE; j++) {
				ary[i * j] += i;
			}
		}
	}

	for (int i = 1; i < 1000001; i++) {
		ary[i] += ary[i - 1];
	}

	

	cin >> T;

	for (caseCount = 1; caseCount <= T; caseCount++)
	{
		int L, R;

		cin >> L >> R;

		/*for (int i = 1; i <= R; i++) {
			cout << i << " : " << ary[i] << endl;;
		}*/

		/*long long totalSum = 0;

		for (int i = L; i <= R; i++) {
			totalSum += ary[i];
		}*/

		// 출력
		//cout << "#" << caseCount << ' ' << ary[R] - ary[L - 1] << endl;
		printf("#%d %lld\n", caseCount, ary[R] - ary[L - 1]);
	}

	//delete ary;
	getchar();
	getchar();

	return 0;
}