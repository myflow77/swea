// 무선 충전

#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int Directions[][2] = { {0, 0}, {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

class BC {
public:
	int X, Y;
	int C;
	int P;

	vector<int> used;

	BC(int x, int y, int c, int p) {
		X = x;
		Y = y;
		C = c;
		P = p;
	}

	int getDistance(int x, int y) {
		return abs(X - x) + abs(Y - y);
	}

	bool isNear(int x, int y) {
		return getDistance(x, y) <= C;
	}

	void pushUser(int user) {
		used.push_back(user);
	}

	int popUser() {
		int powerSum = 0;
		int power;

		if (used.size() == 0)
			return powerSum;
		else if (used.size() == 1) {
			power = P;
		}
		else if (used.size() == 2) {
			power = P / 2;
		}

		while (!used.empty()) {
			switch (used.back())
			{
			case 0:
				//userA[time] = power;
				powerSum += power;
#ifdef DEBUG
				//printf("%d시간 A사용자 %d파워\n", time, power);
#endif // DEBUG
				break;
			case 1:
				//userB[time] = power;
				powerSum += power;
#ifdef DEBUG
				//printf("%d시간 B사용자 %d파워\n", time, power);
#endif // DEBUG
				break;
			default:
				break;
			}
			used.pop_back();
		}

		return powerSum;
	}

	bool operator<(BC bc) const {
		return P > bc.P;
	}
};

void getBestComb(vector<BC> bcs, int ax, int ay, int bx, int by, bool canA, bool canB, int bcNumber, int &bestNumber) {
	if (bcNumber < bcs.size()) {

		vector<BC> bcs0 = bcs;
		getBestComb(bcs0, ax, ay, bx, by, canA, canB, bcNumber + 1, bestNumber);

		if (bcs[bcNumber].isNear(ax, ay) && canA) {
			vector<BC> bcs1 = bcs;
			bcs1[bcNumber].pushUser(0);
			getBestComb(bcs1, ax, ay, bx, by, false, canB, bcNumber + 1, bestNumber);
		}

		if (bcs[bcNumber].isNear(bx, by) && canB) {
			vector<BC> bcs2 = bcs;
			bcs2[bcNumber].pushUser(1);
			getBestComb(bcs2, ax, ay, bx, by, canA, false, bcNumber + 1, bestNumber);
		}

		if (bcs[bcNumber].isNear(ax, ay) && canA && bcs[bcNumber].isNear(bx, by) && canB) {
			vector<BC> bcs3 = bcs;
			bcs3[bcNumber].pushUser(0);
			bcs3[bcNumber].pushUser(1);
			getBestComb(bcs3, ax, ay, bx, by, false, false, bcNumber + 1, bestNumber);
		}
	}
	else {
		int totalPower = 0;
		for (int i = 0; i < bcs.size(); i++) {
			totalPower += bcs[i].popUser();
		}
		if (totalPower > bestNumber) {
			bestNumber = totalPower;
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		int M, A;

		cin >> M >> A;

		int movesOfA[101];
		int chargedOfA[101];
		int movesOfB[101];
		int chargedOfB[101];

		for (int i = 0; i < 101; i++) {
			movesOfA[i] = 0;
			movesOfB[i] = 0;
			chargedOfA[i] = 0;
			chargedOfB[i] = 0;
		}

		for (int i = 0; i < M; i++) {
			cin >> movesOfA[i];
		}
		for (int i = 0; i < M; i++) {
			cin >> movesOfB[i];
		}
		
		vector<BC> BCs;
		for (int i = 0; i < A; i++) {
			int x, y, c, p;
			cin >> x >> y >> c >> p;
			BC tempBC(x, y, c, p);
			BCs.push_back(tempBC);
		}

		sort(BCs.begin(), BCs.end());

		int ax = 1, ay = 1;
		int bx = 10, by = 10;
		int currentTime = 0;

		while (true) {
#ifdef DEBUG
			printf("\nA : (%d, %d)\n", ax, ay);
			printf("B : (%d, %d)\n", bx, by);
#endif // DEBUG
			int best = 0;
			getBestComb(BCs, ax, ay, bx, by, true, true, 0, best);
			chargedOfA[currentTime] = best;

			// 종료 검사
			if (currentTime >= M)
				break;

			// 다음 위치로 이동
			ax += Directions[movesOfA[currentTime]][1];
			ay += Directions[movesOfA[currentTime]][0];
			bx += Directions[movesOfB[currentTime]][1];
			by += Directions[movesOfB[currentTime]][0];

			// 시간 증가
			currentTime++;
		}

		int totalPower = 0;
		for (int i = 0; i <= M; i++) {
			totalPower += chargedOfA[i];
			totalPower += chargedOfB[i];
		}

		// 출력
		printf("#%d %d\n", caseCount, totalPower);
	}

	return 0;
}