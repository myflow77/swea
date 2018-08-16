// 미로 2

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int direction[4][2] = {
	{ 1, 0 },
{ 0, 1 },
{ -1, 0 },
{ 0, -1 }
};

int explore(int map[][100], int currentRow, int currentCol)
{
	int result = 0;
	map[currentRow][currentCol] = -1;
	// 사방을 탐색
	for (int i = 0; i < 4; i++) {
		// 다음 위치
		int nextRow = currentRow + direction[i][0];
		int nextCol = currentCol + direction[i][1];

		// 다음 위치가 지도 안에 존재하는지 확인
		if (0 <= nextRow && nextRow < 100 && 0 <= nextCol && nextCol < 100) {
			// 벽이면
			if (map[nextRow][nextCol] == 1) {
				// Pass
			}
			// 길이면
			else if (map[nextRow][nextCol] == 0) {
				result = explore(map, nextRow, nextCol);
			}
			// 목표 지점이면
			else if (map[nextRow][nextCol] == 3) {
				result = 1;
			}
			// 이미 지나간 지점이면
			else if (map[nextRow][nextCol] == -1) {
				// Pass
			}
			// 그 외
			else {
				// Error
			}
		}
		if (result == 1)
			break;
	}
	return result;
}

int main()
{
	freopen("input.txt", "r", stdin);

	int caseCount = 1;

	while (1)
	{
		int caseNumber;
		cin >> caseNumber;

		////////////////////////////////////////////////////////////////////////////////////////////

		// 입력
		int map[100][100];
		int startRow = 0, startCol = 0; // 시작 지점
		int targetRow = 0, targetCol = 0; // 목표 지점

		/*
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				char tempChar;
				cin >> tempChar;
				
				map[i][j] = tempChar - '0';
				if (map[i][j] == 2) {
					startRow = i;
					startCol = j;
				}
				else if (map[i][j] == 3) {
					targetRow = i;
					targetCol = j;
				}
			}
		}
		*/
		for (int i = 0; i < 100; i++) {
			string oneLine;
			cin >> oneLine;
			for (int j = 0; j < 100; j++) {
				char tempChar = oneLine[j];

				map[i][j] = tempChar - '0';
				if (map[i][j] == 2) {
					startRow = i;
					startCol = j;
				}
				else if (map[i][j] == 3) {
					targetRow = i;
					targetCol = j;
				}
			}
		}


		// 시작 지점에서 목표 지점을 탐색하면서 이동(DFS)
		int result = explore(map, startRow, startCol);

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseNumber << ' ';
		cout << result << endl;
		if (caseNumber == 10)
			break;
	}

	return 0;
}