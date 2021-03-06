// 보호 필름

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>

using namespace std;

class tableWrapper {
public:
	int table[13][20];
	int D, W, K;
	bool possibleMedicine[13];
	int medicineCount;

	tableWrapper(int t[][20], int d, int w, int k) {
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < w; j++) {
				table[i][j] = t[i][j];
			}
		}
		D = d;
		W = w;
		K = k;

		for (int i = 0; i < d; i++) {
			possibleMedicine[i] = true;
		}
		medicineCount = 0;
	}
	bool isPossible(int i) {
		return possibleMedicine[i];
	}
	void putMedicine(int i, int v) {
		if (isPossible(i)) {
			for (int j = 0; j < W; j++) {
				table[i][j] = v;
			}
			possibleMedicine[i] = false;
			medicineCount++;
		}
	}
	bool investigation() {
		// 통과하면 true return
		for (int j = 0; j < W; j++) {
			int continuousValue = table[0][j];
			int continuousFrom = 0;
			// 한줄에 연속된 3특성이 있는지 여부
			bool oneColTest = false;
			for (int i = 0; i < D; i++) {
				if (table[i][j] == continuousValue) {
					// 연속될 경우
					if (i - continuousFrom + 1 >= K) {
						oneColTest = true;
						break;
					}
				}
				else {
					continuousValue = table[i][j];
					continuousFrom = i;
				}
			}
			// 검사에 미달이면 도중에 종료
			if (oneColTest == false)
				return false;
		}
		return true;
	}
};

void test(const int D, const int W, const int K, int &minPuttedMedicine, tableWrapper tw, int row, int puttedMedicine) {
	// 현재 값이 최솟값 이상이면 종료
	if (minPuttedMedicine < puttedMedicine) {
		return;
	}
	// 모든 행에 대해서 약물처리를 완료했다면 검사 후 종료
	if (row == D) {
		// 검사
		if (tw.investigation()) {
			minPuttedMedicine = puttedMedicine;
		}
		return;
	}

	// 약물 미주입
	test(D, W, K, minPuttedMedicine, tw, row + 1, puttedMedicine);

	// 약물 A 주입
	tableWrapper tw0 = tw;
	tw0.putMedicine(row, 0);
	test(D, W, K, minPuttedMedicine, tw0, row + 1, puttedMedicine + 1);

	// 약물 B 주입
	tableWrapper tw1 = tw;
	tw1.putMedicine(row, 1);
	test(D, W, K, minPuttedMedicine, tw1, row + 1, puttedMedicine + 1);
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		// 필름 테이블
		int table[13][20];
		// 필름 두께, 가로크기, 합격기준
		int D, W, K;

		// 초기화
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 20; j++) {
				table[i][j] = -1;
			}
		}

		// 입력 데이터
		cin >> D >> W >> K;

		for (int i = 0; i < D; i++) {
			for (int j = 0; j < W; j++) {
				cin >> table[i][j];
			}
		}

		// 완전탐색 & 백트래킹
		int result = K;
		tableWrapper tw(table, D, W, K);
		test(D, W, K, result, tw, 0, 0);

		// 출력
		cout << "#" << caseCount << ' ' << result << endl;
	}

	return 0;
}