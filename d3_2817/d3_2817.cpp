// d3_2817.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <iostream>

using namespace std;

void findMatch(int ary[], int currentK, int position, int max, int &matchCount)
{
	// 성공 조건
	if (currentK == 0) {
		matchCount++;
		return;
	}
	// 실패 조건
	else if (position >= max || currentK < 0) {
		return;
	}
	// 그 외
	else {
		for (int i = position; i < max; i++) {
			findMatch(ary, currentK - ary[i], i + 1, max, matchCount);
		}
	}
}

int main()
{
	int caseNumber, caseCount = 0;

	cin >> caseNumber;

	while (caseCount++ < caseNumber) {
		int N, K;
		int ary[20];
		int matchCount = 0;

		cin >> N >> K;

		for (int i = 0; i < N; i++) {
			cin >> ary[i];
		}

		for (int i = 0; i < N; i++) {
			findMatch(ary, K - ary[i], i + 1, N, matchCount);
		}

		cout << "#" << caseCount << " " << matchCount << endl;
	}

    return 0;
}

