// 달팽이 숫자

#include <iostream>

using namespace std;

int main()
{
	int ary[100][100];

	int repeat;
	cin >> repeat;

	int a = 0;
	while (a++ < repeat) {
		int N;
		cin >> N;

		int currentNum = 1;

		int px = 0, py = 0;

		int depth = 0;

		while (currentNum <= N * N)
		{
			// right
			while (px < N - depth && currentNum <= N * N) {
				ary[py][px] = currentNum++;
				px++;
			}
			px--; py++;
			// down
			while (py < N - depth && currentNum <= N * N) {
				ary[py][px] = currentNum++;
				py++;
			}
			py--; px--;
			// left
			while (px >= depth && currentNum <= N * N) {
				ary[py][px] = currentNum++;
				px--;
			}
			px++; py--;
			// up
			while (py >= depth + 1 && currentNum <= N * N) {
				ary[py][px] = currentNum++;
				py--;
			}
			py++; px++;

			depth++;
		}

		cout << "#" << a << endl;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << ary[i][j] << " ";
			}
			cout << endl;
		}
	}

	return 0;
}

