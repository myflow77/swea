// d2_1204.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <iostream>

using namespace std;

int ary[101];

int main()
{
	int caseNum, count = 0;

	while (count++ < 10) {
		for (int i = 0; i <= 100; i++) {
			ary[i] = 0;
		}

		cin >> caseNum;
		for (int i = 0; i < 1000; i++) {
			int tempNum;
			cin >> tempNum;
			ary[tempNum]++;
		}

		int maxScore = -1;
		int maxScoreStudents = -1;
		for (int i = 0; i <= 100; i++) {
			if (ary[i] >= maxScoreStudents) {
				maxScoreStudents = ary[i];
				maxScore = i;
			}
		}

		cout << "#" << caseNum << " " << maxScore << endl;
	}



    return 0;
}

