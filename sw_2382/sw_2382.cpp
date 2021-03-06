// 미생물 격리

#define _CRT_SECURE_NO_WARNINGS

//#define DEBUG

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int Directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

class Association {
public:
	int row;
	int col;
	int number;
	int direction;

	Association (int r, int c, int n, int d) {
		row = r;
		col = c;
		number = n;
		direction = d;
	}

	void move(int N) {
		row = row + Directions[direction - 1][0];
		col = col + Directions[direction - 1][1];
		if (row == 0 || row == N - 1 || col == 0 || col == N - 1) {
			number /= 2;
			switch (direction)
			{
			case 1:
				direction = 2;
				break;
			case 2:
				direction = 1;
				break;
			case 3:
				direction = 4;
				break;
			case 4:
				direction = 3;
				break;
			default:
				break;
			}
		}
	}

	bool operator<(Association a) const {
		if (row == a.row) {
			return col < a.col;
		}
		else {
			return row < a.row;
		}
	}
};

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		vector<Association> associationList;
		int N, M, K;

		cin >> N >> M >> K;

		for (int i = 0; i < K; i++) {
			int row, col, number, direction;
			cin >> row >> col >> number >> direction;
			Association tempAssociation(row, col, number, direction);
			associationList.push_back(tempAssociation);
		}

		// M 시간 만큼 반복
		for (int m = 0; m < M; m++) {
#ifdef DEBUG
			int tempMap[100][100];
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					tempMap[i][j] = 0;
				}
			}
			int s = 0;
			for (int i = 0; i < associationList.size(); i++) {
				int row = associationList[i].row;
				int col = associationList[i].col;
				tempMap[row][col] = associationList[i].number;
				s += associationList[i].number;
			}
			printf("%d, %d\n", associationList.size(), s);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					printf("%5d", tempMap[i][j]);
				}
				cout << endl;
			}
			cout << endl;
#endif // DEBUG
			// 모든 미생물을 현재 방향으로 이동 후 지도에 추가
			for (int j = 0; j < associationList.size(); j++) {
				associationList[j].move(N);
			}
			// 미생물들을 좌표순으로 정렬
			sort(associationList.begin(), associationList.end());
			// 연속된 미생물들 중 같은 좌표에 있는 것들을 합침
			vector<Association> tempVector;
			int endIndex = associationList.size() - 1;
			int r = associationList[endIndex].row;
			int c = associationList[endIndex].col;
			int split, current = endIndex;
			while (!associationList.empty()) {
				int t = current;
				int r = associationList[t].row;
				int c = associationList[t].col;
				while (r == associationList[t].row && c == associationList[t].col) {
					split = t;
					t--;
					if (t < 0) {
						split = 0;
						break;
					}
				}
				Association tempAsso = associationList[current];
				int maxNumber = -1;
				int direction = -1;
				int number = 0;;
				while (current >= split) {
					number += associationList[current].number;
					if (maxNumber < associationList[current].number) {
						maxNumber = associationList[current].number;
						direction = associationList[current].direction;
					}
					current--;
					associationList.pop_back();
				}
				tempAsso.direction = direction;
				tempAsso.number = number;
				tempVector.push_back(tempAsso);
			}
			associationList = tempVector;
			tempVector.clear();
		}

		int sum = 0;
		for (int i = 0; i < associationList.size(); i++) {
			sum += associationList[i].number;
		}

		// 출력
		cout << "#" << caseCount << ' ' << sum << endl;
	}

	return 0;
}