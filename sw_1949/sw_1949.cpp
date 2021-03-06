// 등산로 조성

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

// 하, 우, 상, 좌
int Directions[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

struct Coord {
	int row, col;
};

// 주어진 위치에 근접한 장소 중 가장 높은 위치를 반환
int highestHeightFromNear(int map[][8], Coord current) {
	int highestHeight = -1;
	for (int row = current.row - 1; row <= current.row + 1; row++) {
		for (int col = current.col - 1; col <= current.col + 1; col++) {
			// 주어진 장소가 아닐 경우
			if (row != current.row && col != current.col) {
				if (map[row][col] > highestHeight) {
					highestHeight = map[row][col];
				}
			}
		}
	}
	int currentValue = map[current.row][current.col];
	while (currentValue > highestHeight) {
		currentValue--;
		if (currentValue > highestHeight)
			break;
	}
	return currentValue;
}

// 주어진 위치로부터 주변을 탐색하며 최대 길이의 등산로를 찾는다
// 공사 조건 : 주어진 위치에서 다음 위치로 이동할 때 주어진 위치보다 높이가 낮으면서 최대한 높은 것이 좋으므로 진행이 불가능할 경우만 공사를 시행한다.
int explore(int map[][8], int N, int K, Coord current, int length)
{
	// 현재까지 가장 긴 등산로 길이
	int bestLength = length;
	// 현재 위치의 높이
	int currentHeight = map[current.row][current.col];
	// 현재 위치로부터 사방을 탐색
	for (int d = 0; d < 4; d++) {
		// 다음 위치
		Coord next = { current.row + Directions[d][0], current.col + Directions[d][1] };
		// 다음 위치의 높이
		int nextHeight = map[next.row][next.col];
		// 다음 위치가 지도 내부이면서 지나가지 않은 길일 경우
		if (0 <= next.row && next.row < N && 0 <= next.col && next.col < N && -100 < nextHeight) {
			// 다음 위치가 현재 위치보다 높이가 낮을 경우
			if (nextHeight < currentHeight) {
				// 지도에서 현재 위치 높이 저장 후 마킹
				int markedValue = currentHeight;
				map[current.row][current.col] = -100;
				// 재귀 탐색
				int result = explore(map, N, K, next, length + 1);
				bestLength = max<int>(bestLength, result);
				// 마킹된 위치의 값 복구
				map[current.row][current.col] = markedValue;
			}
			else {
				// 공사 기회가 있으면서
				if (K > -1) {
					// 다음 위치가 공사 후 현재 위치보다 높이가 낮아질 수 있다면
					//int targetHeight = highestHeightFromNear(map, next);
					int minNextHeight = nextHeight - K;
					if (minNextHeight < currentHeight) {
						// 지도에서 현재 위치 높이 저장 후 마킹
						int markedValue = currentHeight;
						map[current.row][current.col] = -100;
						// 기존의 다음 위치 높이 저장
						int constructValue = nextHeight;
						// 공사 실시
						int targetHeight = nextHeight;
						while (targetHeight >= minNextHeight) {
							if (targetHeight < currentHeight)
								break;
							targetHeight--;
						}
						map[next.row][next.col] = targetHeight;
						// 재귀 탐색
						int result = explore(map, N, -1, next, length + 1);
						bestLength = max<int>(bestLength, result);
						// 공사 값 복구
						map[next.row][next.col] = constructValue;
						// 마킹된 위치의 값 복구
						map[current.row][current.col] = markedValue;
					}
				}
			}
		}
	}
	return bestLength;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int maxCase;

	cin >> maxCase;

	for (int caseCount = 1; caseCount <= maxCase; caseCount++)
	{
		// 변수 선언
		int N, K;
		int map[8][8];

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				map[i][j] = -1;
			}
		}

		// 데이터 입력
		cin >> N >> K;

		int highestHeight = -1;
		vector<Coord> highestMountains;

		for (int row = 0; row < N; row++) {
			for (int col = 0; col < N; col++) {
				int currentHeight;
				cin >> currentHeight;
				if (currentHeight > highestHeight) {
					highestHeight = currentHeight;
				}
				map[row][col] = currentHeight;
			}
		}

		// 가장 높은 봉우리 위치를 저장
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < N; col++) {
				if (map[row][col] == highestHeight) {
					highestMountains.push_back({ row, col });
				}
			}
		}
		
		// 최대 경로 길이
		int bestValue = -1;
		// 가장 높은 봉우리 개수만큼 알고리즘 시행
		while (highestMountains.empty() == false) {
			// 가장 높은 봉우리 위치를 vector에서 반환
			Coord highestCoord = highestMountains.back();
			highestMountains.pop_back();

			// 가장 높은 봉우리로부터 주변을 탐색
			int result = explore(map, N, K, highestCoord, 1);
			// 결과 비교
			bestValue = max<int>(bestValue, result);
		}

		// 출력
		cout << "#" << caseCount << ' ';
		cout << bestValue << endl;
	}

	return 0;
}