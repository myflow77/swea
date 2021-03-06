// 숫자 만들기

#define _CRT_SECURE_NO_WARNINGS

//#define DEBUG

#include <iostream>
#include <cstdio>
#include <climits>

using namespace std;

void dfs(const int N, int numberAry[], int operatorAry[], int operatorCountAry[], int usedOperatorAry[], int &maxNumber, int &minNumber, int operatorIndex)
{
	// operator를 전부 배치했다면 숫자를 연산
	if (operatorIndex == N - 1) {
		int calculatedNumber = numberAry[0];
		for (int i = 0; i < N - 1; i++) {
			switch (usedOperatorAry[i]) {
			case 0:
				calculatedNumber += numberAry[i + 1];
				break;
			case 1:
				calculatedNumber -= numberAry[i + 1];
				break;
			case 2:
				calculatedNumber *= numberAry[i + 1];
				break;
			case 3:
				calculatedNumber /= numberAry[i + 1];
				break;
			}
		}

#ifdef DEBUG
		cout << numberAry[0] << " ";
		for (int i = 0; i < N - 1; i++) {
			switch (usedOperatorAry[i]) {
			case 0:
				cout << "+ ";
				break;
			case 1:
				cout << "- ";
				break;
			case 2:
				cout << "* ";
				break;
			case 3:
				cout << "/ ";
				break;
			}
			cout << numberAry[i + 1] << " ";
		}
		cout << " : " << calculatedNumber << endl;
#endif // DEBUG

		if (calculatedNumber > maxNumber) {
			maxNumber = calculatedNumber;
		}
		if (calculatedNumber < minNumber) {
			minNumber = calculatedNumber;
		}
	}
	// 현재 위치에 operator를 종류별로 배치해보고 재귀
	else {
		for (int i = 0; i < 4; i++) {
			// 이 operator가 아직 사용 횟수가 남았다면 사용 operator에 추가하고 재귀
			if (operatorCountAry[i] < operatorAry[i]) {
				operatorCountAry[i]++;
				usedOperatorAry[operatorIndex] = i;

				dfs(N, numberAry, operatorAry, operatorCountAry, usedOperatorAry, maxNumber, minNumber, operatorIndex + 1);

				usedOperatorAry[operatorIndex] = -1;
				operatorCountAry[i]--;
			}
		}
	}
}

int solve(const int N, int operatorAry[], int numberAry[])
{
	int operatorCountAry[4]; // +, -, *, /
	int usedOperatorAry[11]; // 숫자 = operator 배열 숫자 항의 문자
	for (int i = 0; i < 4; i++) {
		operatorCountAry[i] = 0;
	}
	for (int i = 0; i < 11; i++) {
		usedOperatorAry[i] = -1;
	}

	//int maxNumber = INT_MIN, minNumber = INT_MAX;
	int maxNumber = -100000000, minNumber = 100000000;
	
	dfs(N, numberAry, operatorAry, operatorCountAry, usedOperatorAry, maxNumber, minNumber, 0);

#ifdef DEBUG
	printf("max : %d, min : %d\n", maxNumber, minNumber);
#endif // DEBUG


	return maxNumber - minNumber;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		int operatorAry[4]; // +, -, *, /
		int numberAry[12];

		int N;

		cin >> N;

		for (int i = 0; i < 4; i++) {
			cin >> operatorAry[i];
		}

		for (int i = 0; i < N; i++) {
			cin >> numberAry[i];
		}

		int result = solve(N, operatorAry, numberAry);

		// 출력
		cout << "#" << caseCount << ' ' << result << endl;
	}

	return 0;
}