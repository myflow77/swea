// 단순 2진 암호 코드

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>

using namespace std;

int ary[50][100];

void print_ary(int N, int M)
{
	cout << N << ", " << M << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << ary[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

int get_number(int code)
{
	switch (code)
	{
	case 3211:
		return 0;
	case 2221:
		return 1;
	case 2122:
		return 2;
	case 1411:
		return 3;
	case 1132:
		return 4;
	case 1231:
		return 5;
	case 1114:
		return 6;
	case 1312:
		return 7;
	case 1213:
		return 8;
	case 3112:
		return 9;
	default:
		return -1;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	int caseCount = 1;
	int maxCase;
	cin >> maxCase;

	for (int caseCount = 1; caseCount <= maxCase; caseCount++)
	{
		////////////////////////////////////////////////////////////////////////////////////////////

		// 초기화
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 100; j++) {
				ary[i][j] = -1;
			}
		}

		// 입력
		int N, M;
		cin >> N >> M;

		for (int n = 0; n < N; n++) {
			for (int m = 0; m < M; m++) {
				char temp;
				cin >> temp;
				ary[n][m] = temp - '0';
			}
		}
		//print_ary(N, M);

		// 연산

		// 가장 상단에 있는 뒤에서 첫번째 1을 찾는다
		bool found = false;
		int rightup_row = 0, rightup_col = 0;
		for (int i = 0; i < N; i++) {
			for (int j = M - 1; j >= 0; j--) {
				if (ary[i][j] == 1) {
					rightup_row = i;
					rightup_col = j;
					found = true;
					break;
				}
			}
			if (found)
				break;
		}
		// 시작 기준점을 정한다
		int row = rightup_row;
		int col = rightup_col - 55;
		if (col < 0) {
			col = 0;
		}
		// 첫번째 1을 만날 때까지 or 배열 끝에 도달할 때까지, 한칸씩 window를 이동하며 암호를 판단한다
		int pw[8];
		bool successed = false;
		while (!successed) {
			//printf("row : %d, col : %d\n", row, col);
			bool transformed = true;
			// 배열 해석
			for (int i = 0; i < 8; i++) {
				int prev = ary[row][col + 7 * i]; // 시작 숫자 저장
				int count = 1; // 같은 숫자 카운트 저장
				int base = 1000;
				int result = 0;
				for (int j = 1; j < 7; j++) {
					// 현재 숫자가 이전과 다르면
					if (ary[row][col + 7 * i + j] != prev) {
						// 개수를 저장하고 이전 숫자를 변경
						result += count * base;
						base = base / 10;
						count = 1;
						prev = ary[row][col + 7 * i + j];
					}
					// 이전과 같으면
					else {
						count++;
					}
				}
				// 마지막 케이스 저장
				result += count * base;
				// 코드 -> 숫자
				int temp = get_number(result);
				if (temp != -1) {
					// 올바른 코드는 추가
					pw[i] = temp;
				}
				else {
					// 올바르지 않은 코드라면 변환 실패
					transformed = false;
					//cout << "result : " << i << ", " << result << endl;
					break;
				}
			}
			// 결과 검증
			if (transformed) {
				int odd = 0, even = 0;
				for (int i = 0; i < 7; i++) {
					if ((i + 1) % 2 == 1) {
						odd += pw[i];
					}
					else {
						even += pw[i];
					}
				}
				int parsed = odd * 3 + even + pw[7];
				if (parsed % 10 == 0) {
					successed = true;
				}
			}

			// 첫번째 1을 만나거나 window 우측이 배열 끝에 도달하면 종료
			if (ary[row][col] == 1 || col + 55 == M - 1) {
				break;
			}
			// 아니면 다음 window 설정
			else {
				// PASS
				col++;
			}
		}

		int result = 0;
		if (successed) {
			for (int i = 0; i < 8; i++) {
				result += pw[i];
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount << ' ';
		cout << result << endl;
	}

	return 0;
}