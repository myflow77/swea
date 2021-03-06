// 핀볼 게임

//#define DEBUG

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

// 동(0), 남(1), 서(2), 북(3)
int Directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

// 지도, 캐시
int map[100][100];
int cache[100][100][4];

// 장애물 1~5에 대해서 들어오는 방향 0~3에 대한 나가는 방향
// 1 ==> 동 : 서, 남 : 동, 서 : 북, 북 : 남
// 2 ==> 동 : 서, 남 : 북, 서 : 남, 북 : 동
// 3 ==> 동 : 남, 남 : 북, 서 : 동, 북 : 서
// 4 ==> 동 : 북, 남 : 서, 서 : 동, 북 : 남
// 5 ==> 동 : 서, 남 : 북, 서 : 동, 북 : 남
int Obstacle[6][4] = { {-1, -1, -1, -1},
{ 2, 0, 3, 1},
{ 2, 3, 1, 0},
{ 1, 3, 0, 2},
{ 3, 2, 0, 1},
{ 2, 3, 0, 1}
};

struct Point {
	int row;
	int col;

	bool operator==(Point p) const {
		return (row == p.row && col == p.col);
	}

	bool operator!=(Point p) const {
		return (row != p.row || col != p.col);
	}
};

class WarmHole {
public:
	int r1, c1, r2, c2;
	Point p1, p2;

	WarmHole() {
		r1 = 0;
		c1 = 0;
		r2 = 0;
		c2 = 0;

		p1 = { r1, c1 };
		p2 = { r2, c2 };
	}

	void setWarmHole(int _r1, int _c1, int _r2, int _c2) {
		r1 = _r1;
		c1 = _c1;
		r2 = _r2;
		c2 = _c2;

		p1 = { _r1, _c1 };
		p2 = { _r2, _c2 };
	}

	Point rideWarmHole(Point p) {
		if (p == p1) {
			return p2;
		}
		else if (p == p2) {
			return p1;
		}
		else {
			cout << "WarmHole ERROR" << endl;
			return p;
		}
	}
};

int dfs(bool beforeCollision, bool isStart, Point startPoint, int &N, vector<WarmHole> &warmHoles, int map[][100], int cache[][100][4], Point currentPoint, int currentDirection, int currentScore) {
	while (1) {
#ifdef DEBUG
		printf("%d, %d -> %d\n", currentPoint.row, currentPoint.col, currentDirection);
#endif // DEBUG

		Point nextPoint;
		int currentValue;
		int nextScore;
		int nextDirection;

		// 벽 안일 경우
		if (0 <= currentPoint.row && currentPoint.row < N && 0 <= currentPoint.col && currentPoint.col < N) {
			// 아직 충돌하기 전이라면 현재 위치, 방향에 대해 캐시에 체크
			if (beforeCollision) {
				cache[currentPoint.row][currentPoint.col][currentDirection] = 1;
			}

			currentValue = map[currentPoint.row][currentPoint.col];
			nextScore = currentScore;

			// 블랙홀일 경우 탐색 종료
			if (currentValue == -1) {
				return currentScore;
			}
			// 시작점으로 돌아올 경우 탐색 종료
			else if (currentPoint == startPoint && isStart == false) {
				return currentScore;
			}
			// 빈 공간일 경우
			else if (currentValue == 0) {
				nextPoint = { currentPoint.row + Directions[currentDirection][0], currentPoint.col + Directions[currentDirection][1] };

				isStart = false;
				currentPoint = nextPoint;
			}
			// 블록일 경우
			else if (0 < currentValue && currentValue <= 5) {
				nextDirection = Obstacle[currentValue][currentDirection];
				nextPoint = { currentPoint.row + Directions[nextDirection][0], currentPoint.col + Directions[nextDirection][1] };
				//printf("%d, %d -> %d\n", currentPoint.row, currentPoint.col, currentDirection);

				beforeCollision = false;
				isStart = false;
				currentPoint = nextPoint;
				currentDirection = nextDirection;
				currentScore++;
			}
			// 웜홀일 경우
			else if (5 < currentValue && currentValue <= 10) {
				nextPoint = warmHoles[currentValue].rideWarmHole(currentPoint);
				nextPoint = { nextPoint.row + Directions[currentDirection][0], nextPoint.col + Directions[currentDirection][1] };

				isStart = false;
				currentPoint = nextPoint;
			}
		}
		// 벽 밖일 경우
		else {
			nextDirection = Obstacle[5][currentDirection];
			nextPoint = { currentPoint.row + Directions[nextDirection][0], currentPoint.col + Directions[nextDirection][1] };
			//printf("%d, %d -> %d\n", currentPoint.row, currentPoint.col, currentDirection);

			beforeCollision = false;
			isStart = false;
			currentPoint = nextPoint;
			currentDirection = nextDirection;
			currentScore++;
		}
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		int N;

		cin >> N;

		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				map[i][j] = -1;
				for (int k = 0; k < 4; k++) {
					cache[i][j][k] = -1;
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int tempInt;
				cin >> tempInt;
				map[i][j] = tempInt;
			}
		}

		// 더미 웜홀 6개(0~5) 생성
		vector<WarmHole> warmHoles(11);

		for (int w = 6; w <= 10; w++) {
			// w번 웜홀이 존재하는가
			bool existWarmHole = false;
			int r1, c1, r2, c2;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (map[i][j] == w) {
						if (existWarmHole == false) {
							r1 = i;
							c1 = j;
							existWarmHole = true;
						}
						else {
							r2 = i;
							c2 = j;
						}
					}
				}
			}
			// 웜홀이 존재하면 배열에 추가
			if (existWarmHole) {
				warmHoles[w].setWarmHole(r1, c1, r2, c2);
			}
			// 존재하지 않으면 탐색 종료
			else {
				//break;
			}
		}

		// 지도의 모든 빈 공간과 방향에 대해서 탐색
		int maxScore = -1;
		Point maxPoint = { -1, -1 };
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == 0) {
					for (int d = 0; d < 4; d++) {
						Point currentPoint = { i, j };
						// 아직 현재 위치, 방향에 대해서 탐색한 적이 없다면(캐시 기준)
						if (cache[i][j][d] == -1) {
							int currentScore = dfs(true, true, currentPoint, N, warmHoles, map, cache, currentPoint, d, 0);

							if (currentScore > maxScore) {
								maxScore = currentScore;
								//printf("START %d, %d -> %d\n", i, j, d);
								//printf("MAX %d, %d = %d\n", i, j, maxScore);
							}
						}
					}
				}
			}
		}

		// 출력
		cout << "#" << caseCount << ' ' << maxScore << endl;
	}

	return 0;
}