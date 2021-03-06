// 보급로

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

int direction[][2] = {
	{1, 0}, // 하
	{0, 1}, // 우
	{-1, 0}, // 상
	{0, -1} // 좌
};

struct location
{
	int row;
	int col;
};

deque<location> locationQueue;

void explore(int map[][100], int cache[][100], int N, int currentRow, int currentCol)
{
	if (currentRow == N - 1 && currentCol == N - 1) {
		return;
	}
	//map[currentRow][currentCol] = -1;

	for (int d = 0; d < 4; d++) {
		int nextRow = currentRow + direction[d][0];
		int nextCol = currentCol + direction[d][1];

		// 지도 범위 안에 있는지 확인
		if (0 <= nextRow && nextRow < N && 0 <= nextCol && nextCol < N) {
			// 이미 지나간 경로가 아닌지 확인
			//if (map[nextRow][nextCol] != -1) {
			if (true) {
				// 현재 위치에서 다음 위치로 가는 것이 최단경로라면 탐색
				if (cache[nextRow][nextCol] > cache[currentRow][currentCol] + map[nextRow][nextCol]) {
					// 다음 위치의 최단시간 = 현재 위치의 최단시간 + 다음 위치의 깊이
					cache[nextRow][nextCol] = cache[currentRow][currentCol] + map[nextRow][nextCol];
					location tempLocation = { nextRow, nextCol };
					locationQueue.push_back(tempLocation);
				}
				else {
					// 최단경로가 아님
				}
			}
		}
	}
}

void printCache(int map[][100], int cache[][100], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%2d ", cache[i][j]);
		}
		cout << endl;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	int maxCount;

	cin >> maxCount;

	for (int caseCount = 1; caseCount <= maxCount; caseCount++)
	{
		////////////////////////////////////////////////////////////////////////////////////////////
		locationQueue.clear();

		int map[100][100];
		int cache[100][100];

		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				map[i][j] = -1;
				cache[i][j] = 99999999;
			}
		}
		cache[0][0] = 0;

		int N;

		cin >> N;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				char tempChar;
				cin >> tempChar;
				map[i][j] = tempChar - '0';
			}
		}

		explore(map, cache, N, 0, 0);
		while (locationQueue.empty() == false) {
			location tempLocation = locationQueue.front();
			explore(map, cache, N, tempLocation.row, tempLocation.col);
			locationQueue.pop_front();
		}

		//printCache(map, cache, N);

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount << ' ';
		cout << cache[N - 1][N - 1] << endl;
	}

	return 0;
}