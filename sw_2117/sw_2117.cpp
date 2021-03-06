// 홈 방범 서비스

#define _CRT_SECURE_NO_WARNINGS

//#define DEBUG

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

// 각각의 K에 대해서 최대 서비스 인원을 구함(row, col ==> 방범 범위 좌측 위 칸 지도에서의 위치, 지도 끝에 도달하면 종료)
int searchForSingleK(int map[][20], int &N, int &M, int **area, int &areaN, int &cost, int row, int col)
{
	// 행이 좌표 밖이면 탐색 종료
	if (row >= N) {
		return 0;
	}
	// 열이 좌표 밖이면 행 +1 후 열 초기화
	else if (col >= N) {
		row++;
		col = 0 - areaN + 1;

		return searchForSingleK(map, N, M, area, areaN, cost, row, col);
	}
	// 그 외
	else {
		int numberOfSame = 0;

		for (int i = 0; i < areaN; i++) {
			for (int j = 0; j < areaN; j++) {
				// area의 좌표가 map 안에 있으면
				if (0 <= i + row && i + row < N && 0 <= j + col && j + col < N) {
					if (area[i][j] == 1 && map[i + row][j + col] == 1) {
						numberOfSame++;
					}
				}
			}
		}

		/*printf("row : %d, col : %d\n", row, col);

		if (row == 1 && col == 1) {
			printf("cost : %d, same : %d\n", cost, numberOfSame);
		}*/

		if (numberOfSame * M < cost)
			numberOfSame = 0;

		int maxNumberOfSame = max<int>(numberOfSame, searchForSingleK(map, N, M, area, areaN, cost, row, col + 1));

		return maxNumberOfSame;
	}
}

// maxK부터 모든 K에 대해서 최대 서비스 인원을 구함
int searchForEveryK(int map[][20], int N, int M, int numberOfHouses, int maxK)
{
	int K = maxK;
	int maxPeople = 0;
	
	while (K > 0) {
		int cost = K * K + (K - 1) * (K - 1);
		// 서비스를 제공받는 최대 사람 수가 현재 K의 넓이보다 크다면 탐색 중지
		if (maxPeople > cost) {
			break;
		}

		// 방범 서비스 제공 범위 배열을 동적할당
		int areaN = 1 + (K - 1) * 2;
		int **area;
		area = new int*[areaN];
		for (int i = 0; i < areaN; i++) {
			area[i] = new int[areaN];
			//memset(area[i], 0, sizeof(int) * areaN);
			for (int j = 0; j < areaN; j++) {
				area[i][j] = 0;
			}
		}

		// 배열에 밤범 범위를 1로 채움
		int mid = (areaN - 1) / 2;
		for (int i = 0; i <= mid; i++) {
			// 가운데를 기준으로 좌우로 진행
			for (int j = 1; j < i + 1; j++) {
				area[i][mid - j] = 1;
			}
			area[i][mid] = 1;
			for (int j = 1; j < i + 1; j++) {
				area[i][mid + j] = 1;
			}
		}
		for (int i = mid + 1; i < areaN; i++) {
			// 가운데를 기준으로 좌우로 진행
			for (int j = 1; j < areaN - i; j++) {
				area[i][mid - j] = 1;
			}
			area[i][mid] = 1;
			for (int j = 1; j < areaN - i; j++) {
				area[i][mid + j] = 1;
			}
		}

#ifdef DEBUG
		for (int i = 0; i < areaN; i++) {
			for (int j = 0; j < areaN; j++) {
				printf("%2d", area[i][j]);
			}
			cout << endl;
		}
		cout << endl;
#endif // DEBUG


		for (int row = 0 - areaN + 1; row < N; row++) {
			for (int col = 0 - areaN + 1; col < N; col++) {
				int numberOfSame = 0;

				for (int i = 0; i < areaN; i++) {
					for (int j = 0; j < areaN; j++) {
						// area의 좌표가 map 안에 있으면
						if (0 <= i + row && i + row < N && 0 <= j + col && j + col < N) {
							if (area[i][j] == 1 && map[i + row][j + col] == 1) {
								numberOfSame++;
							}
						}
					}
				}

				if (numberOfSame * M < cost)
					numberOfSame = 0;

				maxPeople = max<int>(maxPeople, numberOfSame);
			}
		}

		//// 현재 K의 방범 범위를 지도에 대조해서 최대 사용자를 구함
		//int result = searchForSingleK(map, N, M, area, areaN, cost, 0 - areaN + 1, 0 - areaN + 1);
		//maxPeople = max<int>(maxPeople, result);

		// 동적할당 해제
		for (int i = 0; i < areaN; i++) {
			delete[] area[i];
		}
		delete[] area;

		// K를 1 감소 후 반복
		K--;
	}

	return maxPeople;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		int map[20][20];
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				map[20][20] = 0;
			}
		}
		int numberOfHouses = 0;

		// 도시 크기, 1개의 집이 지불할 수 있는 비용
		int N, M;

		// 입력 데이터
		cin >> N >> M;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1)
					numberOfHouses++;
			}
		}

		// 지도의 모든 집이 서비스를 신청할 때 가능한 최대 K를 탐색
		int maxRevenue = numberOfHouses * M;
		int maxK = 1;
		while (true) {
			int cost = maxK * maxK + (maxK - 1) * (maxK - 1);
			if (cost <= maxRevenue) {
				maxK++;
			}
			else {
				maxK--;
				break;
			}
		}

#ifdef DEBUG
		cout << "집 수 = " << numberOfHouses << ", " << "최대 K = " << maxK << endl;
#endif // DEBUG

		int maxNumberOfPeople = searchForEveryK(map, N, M, numberOfHouses, maxK);

		// 출력
		cout << "#" << caseCount << ' ' << maxNumberOfPeople << endl;
#ifdef DEBUG
		cout << endl;
#endif // DEBUG

	}

	return 0;
}