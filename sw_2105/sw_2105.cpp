// 디저트 카페

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <deque>
#include <algorithm>
#include <functional>

using namespace std;

// 북동, 남동, 남서, 북서 - 시계방향
int Directions[4][2] = { { -1, 1 },{ 1, 1 },{ 1, -1 },{ -1, -1 } };

struct Coord {
	int row;
	int col;

	bool operator==(Coord a) const {
		return row == a.row && col == a.col;
	}
};

class Route
{
public:
	bool desert[101];
	int count;

	Route() {
		for (int i = 0; i < 101; i++) {
			desert[i] = false;
		}
		count = 0;
	}

	// 디저트 리스트에서 디저트 번호를 체크
	// 새로운 디저트에 체크 시 -> true 반환
	// 이미 있는 디저트에 체크 시 -> false 반환
	bool addDesert(int p) {
		if (desert[p] == false) {
			desert[p] = true;
			count++;
			return true;
		}
		else {
			return false;
		}
	}

	// 디버깅용
	void print() {
		for (int i = 0; i < 101; i++) {
			if (desert[i] == true)
				cout << i << " ";
		}
		cout << endl;
	}

	bool operator==(Route a) const {
		for (int i = 0; i < 101; i++) {
			if (desert[i] != a.desert[i])
				return false;
		}
		return true;
	}

	bool operator<(Route a) const {
		return count < a.count;
	}

	bool operator>(Route a) const {
		return count > a.count;
	}
};

void exploreMap(int map[][20], int &longestLength, int &N, Coord origin, Coord currentPositioin, Route currentRoute, int prevDirection, bool isStart, deque<int> remainedDirections) {
	// 지도 안일 경우 탐색 지속
	if (0 <= currentPositioin.row && currentPositioin.row < N && 0 <= currentPositioin.col && currentPositioin.col < N) {
		// 원점으로 돌아왔을 경우 탐색 종료
		if (currentPositioin == origin && isStart == false) {

			/*Coord temp = { 0, 2 };
			if (origin == temp)
			currentRoute.print();*/

			if (currentRoute.count > longestLength) {
				//currentRoute.print();
				longestLength = currentRoute.count;
			}
		}
		// 원점이 아닐 경우 탐색 지속
		else {
			/*Coord temp = { 0, 2 };
			if (origin == temp)
			cout << currentPositioin.row << ", " << currentPositioin.col << " // " << prevDirection << endl;*/

			// 저장된 경로 상에 현재 위치의 디저트가 있을 경우 탐색 종료
			if (!currentRoute.addDesert(map[currentPositioin.row][currentPositioin.col]))
				return;

			// 이전에 선택한 방향은 조건없이 반복 가능
			if (prevDirection >= 0) {
				Coord nP = { currentPositioin.row + Directions[prevDirection][0], currentPositioin.col + Directions[prevDirection][1] };
				exploreMap(map, longestLength, N, origin, nP, currentRoute, prevDirection, false, remainedDirections);
			}

			bool finished = false;

			// 남은 방향을 탐색
			for (int i = 0; i < remainedDirections.size(); i++) {
				int direction = remainedDirections[i];

				if (isStart && (direction == 0 || direction == 3 || direction == 3))
					continue;

				// 이전의 방향의 반대방향은 선택할 수 없음
				if (direction == (prevDirection + 2) % 4)
					continue;

				// 다음 위치
				Coord nextPosition = { currentPositioin.row + Directions[direction][0], currentPositioin.col + Directions[direction][1] };

				// 선택한 방향이 없는 새로운 방향 리스트를 생성
				deque<int> newDirections(remainedDirections);
				newDirections.erase(newDirections.begin() + i);

				// 재귀탐색
				exploreMap(map, longestLength, N, origin, nextPosition, currentRoute, direction, false, newDirections);
			}
		}
	}
	// 지도 밖으로 벗어나면 탐색 중지
	else {
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int maxCount;

	cin >> maxCount;

	for (int caseCount = 1; caseCount <= maxCount; caseCount++)
	{
		int map[20][20];
		int longestLength = 0;
		// 디저트의 가짓수는 1~100
		// [101]의 배열을 만들어서 먹은 디저트에 대해서 체크
		// 배열이 같을 경우 동일한 경로로 취급

		// 입력 데이터
		int N;

		cin >> N;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		// 연산 - 지도 상의 각 점에서 완전탐색하면서 새로운 경로를 리스트에 추가
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// 가능한 최장경로가 현재 최장경로보다 짧다면 패스
				if ((N - i) * 2 <= longestLength)
					continue;
				// 한 번의 경로탐색에서 사용할 수 있는 방향은 4가지
				// 조건1 : 직전에 사용한 방향의 반대방향은 사용이 불가능하다.
				// 조건2 : 직전에 사용한 방향은 반복적으로 사용 가능하다.
				deque<int> remainedDirections;
				Coord currentPosition = { i, j };
				Route currentRoute;

				for (int i = 0; i < 4; i++) {
					remainedDirections.push_back(i);
				}
				exploreMap(map, longestLength, N, currentPosition, currentPosition, currentRoute, -1, true, remainedDirections);
			}
		}

		int result;
		// routeList를 길이순으로 정렬
		if (longestLength > 0) {
			result = longestLength;
		}
		else {
			result = -1;
		}

		// 출력
		cout << "#" << caseCount << ' ';
		cout << result << endl;
	}

	return 0;
}