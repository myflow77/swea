// 가장 긴 회문 찾기

#include <iostream>

using namespace std;

char board[100][100];

int main()
{
	int caseCount = 1;

	do
	{
		int result = 0;

		cin >> caseCount;

		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				cin >> board[i][j];
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////

		for (int max_len = 100; max_len > 0; max_len--) {
			bool isExist = false;
			int mid = max_len / 2;
			int length = max_len - 1;

			// 가로
			for (int i = 0; i < 100; i++) {
				if (isExist) {
					break;
				}
				for (int j = 0; j < 100 - length; j++) {
					int isFel = true;
					// 회문 확인
					for (int k = 0; k < mid; k++) {
						if (board[i][j + k] != board[i][j + length - k]) {
							isFel = false;
							break;
						}
					}
					if (isFel == true) {
						isExist = true;
						break;
					}
				}
			}
			// 세로
			for (int j = 0; j < 100; j++) {
				if (isExist) {
					break;
				}
				for (int i = 0; i < 100 - length; i++) {
					int isFel = true;
					// 회문 확인
					for (int k = 0; k < mid; k++) {
						if (board[i + k][j] != board[i + length - k][j]) {
							isFel = false;
							break;
						}
					}
					if (isFel == true) {
						isExist = true;
						break;
					}
				}
			}
			if (isExist) {
				result = max_len;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount << " " << result << endl;
	} while (caseCount < 10);

	return 0;
}

