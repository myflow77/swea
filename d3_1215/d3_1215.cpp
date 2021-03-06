// 주어진 길이의 회문 개수 찾기

#include <iostream>

using namespace std;

char board[8][8];

int main()
{
	int caseCount = 1;

	do
	{
		int result = 0;
		int length = -1;

		cin >> length;

		////////////////////////////////////////////////////////////////////////////////////////////

		int mid = length / 2;
		length = length - 1;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> board[i][j];
			}
		}

		// 가로
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8 - length; j++) {
				int isFel = true;
				// 회문 확인
				for (int k = 0; k < mid; k++) {
					if (board[i][j + k] != board[i][j + length - k]) {
						isFel = false;
						break;
					}
				}
				if (isFel == true) {
					result++;
				}
			}
		}
		// 세로
		for (int j = 0; j < 8; j++) {
			for (int i = 0; i < 8 - length; i++) {
				int isFel = true;
				// 회문 확인
				for (int k = 0; k < mid; k++) {
					if (board[i + k][j] != board[i + length - k][j]) {
						isFel = false;
						break;
					}
				}
				if (isFel == true) {
					result++;
				}
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount++ << " " << result << endl;
	} while (caseCount <= 10);

	return 0;
}

