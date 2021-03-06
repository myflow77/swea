// 활주로 건설

#define _CRT_SECURE_NO_WARNINGS

//#define DEBUG

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

bool checkColValue(int map[][20], bool cache[][20], int &N, int &col, int &from, int &to, int &value) {
	if (0 <= from && from < N && 0 <= to && to < N) {
		bool isSame = true;
		for (int row = from; row <= to; row++) {
			if (map[row][col] != value || cache[row][col] == false) {
				isSame = false;
				break;
			}
		}

		if (isSame) {
			for (int row = from; row <= to; row++) {
				cache[row][col] = false;
			}

#ifdef DEBUG
			printf("%d열 경사로 성공 : ", col);
			for (int row = from; row <= to; row++) {
				cout << row << " ";
			}
			cout << endl;
#endif // DEBUG

		}
		else {
#ifdef DEBUG
			printf("%d열 경사로 실패 : ", col);
			for (int row = from; row <= to; row++) {
				cout << row << " ";
			}
			cout << endl;
#endif // DEBUG
		}

		return isSame;
	}
	else {
		return false;
	}
}

bool checkCol(int &N, int &X, int map[][20], bool cache[][20], int &col)
{
	int prevHeight = map[0][col];
	bool isContinuous = true;
	for (int row = 1; row < N; row++) {
		int currentHeight = map[row][col];
		// 현재 높이가 이전 높이와 다를 경우
		if (prevHeight != currentHeight) {
			if (abs(prevHeight - currentHeight) > 1) {
				isContinuous = false;
				break;
			}
			// 현재 높이가 이전 높이보다 낮을 경우
			if (currentHeight < prevHeight) {
				// 현재 위치부터 이후로 X만큼 위치가 현재 높이와 같아야 함
				int from = row;
				int to = row + X - 1;
				if (checkColValue(map, cache, N, col, from, to, currentHeight)) {

				}
				else {
					isContinuous = false;
					break;
				}
			}
			// 현재 높이가 이전 높이보다 높을 경우
			else {
				// 이전 위치부터 전으로 X만큼 위치가 이전 높이와 같아야 함
				int from = row - X;
				int to = row - 1;
				if (checkColValue(map, cache, N, col, from, to, prevHeight)) {

				}
				else {
					isContinuous = false;
					break;
				}
			}
			prevHeight = currentHeight;
		}
	}

#ifdef DEBUG
	if (isContinuous) {
		printf("%d열 통과\n", col);
	}
	else {
		printf("%d열 실패\n", col);
	}
#endif // DEBUG

	return isContinuous;
}

bool checkRowValue(int map[][20], bool cache[][20], int &N, int &row, int &from, int &to, int &value) {
	if (0 <= from && from < N && 0 <= to && to < N) {
		bool isSame = true;
		for (int col = from; col <= to; col++) {
			if (map[row][col] != value || cache[row][col] == false) {
				isSame = false;
				break;
			}
		}

		if (isSame) {
			for (int col = from; col <= to; col++) {
				cache[row][col] = false;
			}

#ifdef DEBUG
			printf("%d행 경사로 성공 : ", row);
			for (int col = from; col <= to; col++) {
				cout << col << " ";
			}
			cout << endl;
#endif // DEBUG

		}
		else {
#ifdef DEBUG
			printf("%d행 경사로 실패 : ", row);
			for (int col = from; col <= to; col++) {
				cout << col << " ";
			}
			cout << endl;
#endif // DEBUG
		}

		return isSame;
	}
	else {
		return false;
	}
}

bool checkRow(int &N, int &X, int map[][20], bool cache[][20], int &row)
{
	int prevHeight = map[row][0];
	bool isContinuous = true;
	for (int col = 1; col < N; col++) {
		int currentHeight = map[row][col];
		// 현재 높이가 이전 높이와 다를 경우
		if (prevHeight != currentHeight) {
			if (abs(prevHeight - currentHeight) > 1) {
				isContinuous = false;
				break;
			}
			// 현재 높이가 이전 높이보다 낮을 경우
			if (currentHeight < prevHeight) {
				// 현재 위치부터 이후로 X만큼 위치가 현재 높이와 같아야 함
				int from = col;
				int to = col + X - 1;
				if (checkRowValue(map, cache, N, row, from, to, currentHeight)) {

				}
				else {
					isContinuous = false;
					break;
				}
			}
			// 현재 높이가 이전 높이보다 높을 경우
			else {
				// 이전 위치부터 전으로 X만큼 위치가 이전 높이와 같아야 함
				int from = col - X;
				int to = col - 1;
				if (checkRowValue(map, cache, N, row, from, to, prevHeight)) {

				}
				else {
					isContinuous = false;
					break;
				}
			}
			prevHeight = currentHeight;
		}
	}

#ifdef DEBUG
	if (isContinuous) {
		printf("%d행 통과\n", row);
	}
	else {
		printf("%d행 실패\n", row);
	}
#endif // DEBUG

	return isContinuous;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		int map[20][20]; // 지도
		bool cache[20][20]; // 경사로를 만들어도 되는지 저장하는 배열

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				map[i][j] = -1;
				cache[i][j] = true;
			}
		}

		int N, X;

		cin >> N >> X;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		// 모든 행에 대해서 검사
		int possibleRow = 0;
		for (int row = 0; row < N; row++) {
			if (checkRow(N, X, map, cache, row)) {
				possibleRow++;
			}
		}

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				cache[i][j] = true;
			}
		}

		// 모든 열에 대해서 검사
		int possibleCol = 0;
		for (int col = 0; col < N; col++) {
			if (checkCol(N, X, map, cache, col)) {
				possibleCol++;
			}
		}

#ifdef DEBUG
		printf("행 : %d개, 열 %d개\n", possibleRow, possibleCol);
#endif // DEBUG


		int result = possibleRow + possibleCol;

		// 출력
		cout << "#" << caseCount << ' ' << result << endl;
	}

	return 0;
}