// 탈주범 검거

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <deque>
#include <algorithm>

using namespace std;

struct Coord
{
	int row, col;
	bool operator==(Coord b) const {
		return row == b.row && col == b.col;
	}
};

// 상, 하, 좌, 우
Coord Directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


// 터널 구조물 타입에 따라 진행할 수 있는 방향의 deque를 반환
deque<Coord> getDirections(int d)
{
	deque<Coord> directions;
	switch (d)
	{
	case 1: // 상하좌우
		directions.push_back(Directions[0]);
		directions.push_back(Directions[1]);
		directions.push_back(Directions[2]);
		directions.push_back(Directions[3]);
		break;
	case 2: // 상하
		directions.push_back(Directions[0]);
		directions.push_back(Directions[1]);
		break;
	case 3: // 좌우
		directions.push_back(Directions[2]);
		directions.push_back(Directions[3]);
		break;
	case 4: // 상우
		directions.push_back(Directions[0]);
		directions.push_back(Directions[3]);
		break;
	case 5: // 하우
		directions.push_back(Directions[1]);
		directions.push_back(Directions[3]);
		break;
	case 6: // 하좌
		directions.push_back(Directions[1]);
		directions.push_back(Directions[2]);
		break;
	case 7: // 상좌
		directions.push_back(Directions[0]);
		directions.push_back(Directions[2]);
		break;
	default:
		break;
	}
	return directions;
}

// end에서 start로 길이 연결되는지 확인(start->end는 이미 연결되었다고 가정)
bool isConnected(int map[][50], Coord start, Coord end)
{
	// end 지점 값
	int endValue = map[end.row][end.col];
	// end 지점에서 갈 수 있는 방향을 확인
	deque<Coord> directions = getDirections(endValue);
	// 모든 directions 확인해서 start 지점으로 갈 수 있는지 확인
	while (!directions.empty()) {
		Coord direction = directions.back();
		directions.pop_back();
		Coord nextPosition = { end.row + direction.row, end.col + direction.col };
		if (nextPosition == start)
			return true;
	}
	return false;
}

// BFS를 통해서 범죄자가 경과시간 내에 범죄자가 이동할 수 있는 장소를 탐색
void explore(int map[][50], int cache[][50], const int passedTime, const Coord c, const int t)
{
	deque<pair<Coord, int>> exploreQueue;
	exploreQueue.push_back({ c, t + 1 });

	// 큐에 값이 없을 때까지 반복
	while (!exploreQueue.empty()) {
		pair<Coord, int> tempPair = exploreQueue.front();
		exploreQueue.pop_front();
		// 현재 장소, 현재 시간
		Coord currentPosition = tempPair.first;
		int currentTime = tempPair.second;

		// 현재 시간이 경과시간보다 작은 경우에만 진행
		if (currentTime < passedTime) {
			// 현재 장소에서 갈 수 있는 방향 탐색
			int currentValue = map[currentPosition.row][currentPosition.col];
			deque<Coord> directions = getDirections(currentValue);

			// 현재 장소에서 갈 수 있는 장소들에 대해서 반대쪽에서도 길이 이어져 있는지 확인
			while (!directions.empty()) {
				Coord direction = directions.back();
				directions.pop_back();
				Coord nextPosition = { currentPosition.row + direction.row, currentPosition.col + direction.col };
				// 반대쪽에서도 연결되어 있으면서 아직 진행하지 않은 길이면 진행
				if (isConnected(map, currentPosition, nextPosition) && cache[nextPosition.row][nextPosition.col] != 1) {
					cache[nextPosition.row][nextPosition.col] = 1;
					exploreQueue.push_back({ nextPosition, currentTime + 1 });
				}
			}
		}
		/*for (int i = 0; i < exploreQueue.size(); i++) {
			printf("(%d, %d), ", exploreQueue[i].first.row, exploreQueue[i].first.col);
		}
		cout << endl;*/
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);

	int maxCount;

	cin >> maxCount;

	for (int caseCount = 1; caseCount <= maxCount; caseCount++)
	{
		int map[50][50];
		int cache[50][50];
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				map[i][j] = -1;
				cache[i][j] = 0;
			}
		}
		
		int N, M, R, C, L;

		cin >> N >> M >> R >> C >> L;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> map[i][j];
			}
		}

		Coord startPosition = { R, C };
		int startTime = 0;
		cache[R][C] = 1;
		explore(map, cache, L, startPosition, startTime);

		// cache에서 1의 개수를 파악
		int passedCount = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (cache[i][j] == 1) {
					passedCount++;
				}
				/*printf("%2d", cache[i][j]);*/
			}
			/*cout << endl;*/
		}


		// 출력
		cout << "#" << caseCount << ' ';
		cout << passedCount << endl;
	}

	return 0;
}