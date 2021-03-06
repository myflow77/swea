// 벌꿀 채취

#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

// 선택된 벌통에서 어떤 조합이 최고 수익을 내는지 dfs를 통해서 탐색
int getBestCombination(int table[][10], const int C, const int row, const int to, int maxSum, int current, int honey, int sum)
{
	// 최대 꿀 채취량보다 현재 꿀이 많아지면 탐색 중지
	if (C < honey) {
		return maxSum;
	}
	// 범위를 벗어나면 수익을 계산 후 결과 반환
	else if (current > to) {
		return sum;
	}
	else {
		int currentValue = table[row][current];
		int result;
		// 현재 위치의 항목을 추가하지 않음
		result = getBestCombination(table, C, row, to, maxSum, current + 1, honey, sum);
		maxSum = max<int>(result, maxSum);
		// 현재 위치의 항목을 추가
		result = getBestCombination(table, C, row, to, maxSum, current + 1, honey + currentValue, sum + int(pow(currentValue, 2)));
		maxSum = max<int>(result, maxSum);
		
		return maxSum;
	}
}

// 각 라인에서 M만큼 길이의 모든 조합을 탐색
int exploreEachCombination(int table[][10], const int N, const int M, const int C)
{
	int cache[10][10];
	priority_queue<int> pq;

	// 꿀 채취자가 채취할 수 있는 각 범위에서 최대수익조합을 저장
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= N - M; j++) {
			int value = getBestCombination(table, C, i, j + M - 1, 0, j, 0, 0);
			cache[i][j] = value;
#ifdef DEBUG
			printf("%d ~ %d : %d\n", i, j + M - 1, value);
#endif // DEBUG
		}
	}

#ifdef DEBUG
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= N - M; j++) {
			cout << cache[i][j] << ' ';
		}
		cout << endl;
	}
#endif // DEBUG


	// 겹치지 않는 두 꿀 채취자의 최대 수익 합을 탐색
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= N - M; j++) {
			// 최대수익 배열의 각 항에 대해서 겹치지 않는 두 수익 합을 pq에 삽입
			for (int ti = i; ti < N; ti++) {
				for (int tj = (ti == i) ? j : 0; tj <= N - M; tj++) {
					// 겹치는 조건
					if (i == ti && tj - j < M) {
						continue;
					}
					else {
						pq.push(cache[i][j] + cache[ti][tj]);
					}
				}
			}
		}
	}

	return pq.top();
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		int table[10][10];

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				table[i][j] = -1;
			}
		}

		// 벌통의 크기, 선택가능한 벌통 개수, 채취가능한 꿀의 최대 양
		int N, M, C;

		// 입력 데이터
		cin >> N >> M >> C;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> table[i][j];
			}
		}

		int result = exploreEachCombination(table, N, M, C);

		// 출력
		std::cout << "#" << caseCount << ' ' << result << endl;
	}

	return 0;
}