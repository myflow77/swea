// Magnetic

#include <iostream>
#include <fstream>

using namespace std;

int table[100][100];
int length;

void step()
{
	// 아래쪽부터 N극 자성체를 하강
	for (int i = length - 1; i <= 0; i--) {
		for (int j = 0; j < length; j++) {
			if (table[i][j] == 1) {
				// 테이블 끝에 도달
				if (i == length - 1) {
					table[i][j] = 0;
				}
				// S극 자성체 만남
				else if (table[i + 1][j] == 2) {

				}
				// 이동
				else
				{
					table[i][j] = 0;
					table[i + 1][j] = 1;
				}
			}
		}
	}
	// 위쪽부터 S극 자성체를 하강
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (table[i][j] == 2) {
				// 테이블 끝에 도달
				if (i == 0) {
					table[i][j] = 0;
				}
				// S극 자성체 만남
				else if (table[i - 1][j] == 1) {

				}
				// 이동
				else
				{
					table[i][j] = 0;
					table[i - 1][j] = 2;
				}
			}
		}
	}
}

int main()
{
	int caseCount = 1;

	do
	{
		int result = 0;

		cin >> length;

		////////////////////////////////////////////////////////////////////////////////////////////

		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				cin >> table[i][j];
			}
		}

		// step 진행
		for (int i = 0; i < length; i++) {
			step();
		}

		// 교착 상태 개수 파악
		int count = 0;
		for (int i = 0; i < length - 1; i++) {
			for (int j = 0; j < length; j++) {
				if (table[i][j] == 1) {
					if (table[i + 1][j] == 2) {
						count++;
					}
				}
			}
		}

		result = count;

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount++ << " " << result << endl;
	} while (caseCount < 11);

	return 0;
}

