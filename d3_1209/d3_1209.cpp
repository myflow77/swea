// d3_1209.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <iostream>
#include <cstdlib>

using namespace std;

int rows[101];
int cols[101];
int leftRight, rightLeft;

int max(int a, int b) {
	if (a > b)
		return a;
	return b;
}

void initGloboal() {
	leftRight = 0;
	rightLeft = 0;
	for (int i = 1; i <= 100; i++) {
		rows[i] = 0;
		cols[i] = 0;
	}
}

int main()
{
	int count = 0;

	while (count++ < 10) {
		int caseNum;

		cin >> caseNum;

		initGloboal();

		for (int i = 1; i <= 100; i++) {
			for (int j = 1; j <= 100; j++) {
				int tempNum;
				cin >> tempNum;

				rows[i] += tempNum; // 행
				cols[j] += tempNum; // 열
				// 좌상 우하 대각선
				if (i == j) {
					leftRight += tempNum;
				}
				 // 우상 좌하 대각선
				if (i + j == 101) {
					rightLeft += tempNum;
				}
			}
		}

		int rowMax = -1;
		int colMax = -1;
		int totalMax = -1;
		for (int i = 1; i <= 100; i++) {
			rowMax = max(rowMax, rows[i]);
			colMax = max(colMax, cols[i]);
		}
		totalMax = max(rowMax, colMax);
		totalMax = max(totalMax, leftRight);
		totalMax = max(totalMax, rightLeft);

		cout << "#" << count << " " << totalMax << endl;
	}

    return 0;
}

