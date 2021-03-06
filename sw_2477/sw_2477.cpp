// 차량 정비소

#define _CRT_SECURE_NO_WARNINGS

//#define DEBUG

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>

using namespace std;

int solve(int n[], int m[], int k[][3], int N, int M, int K, int A, int B)
{
	int receptionCustomers[10][2], repairCustomers[10][2]; // [0]고객번호, [1]값 = 종료시간, 0일 경우 사람 없음
	for (int i = 1; i <= 9; i++) {
		receptionCustomers[i][0] = -1;
		receptionCustomers[i][1] = -1;
		repairCustomers[i][0] = -1;
		repairCustomers[i][1] = -1;
	}

	
	int time = 0;
	int receptionCustomerIndex = 1;
	int repairCustomerNumber = 0;
	deque<int> repairQueue; // 정비창구로 이동한 고객번호를 저장
	int lastCustomer = -1, lastCustomerTime = -1;
	while (1) {
		// 접수창구 확인
		for (int i = 1; i <= N; i++) {
			// 현재 접수가 완료되었으면
			if (receptionCustomers[i][1] == time) {
				repairQueue.push_back(receptionCustomers[i][0]);
#ifdef DEBUG
				printf("시간 %d : 고객 %d, 접수처 %d ==> 처리완료\n", time, receptionCustomers[i][0], i);
#endif // DEBUG

				receptionCustomers[i][0] = -1;
				receptionCustomers[i][1] = -1;
			}

			// 고객이 전부 처리되었다면 패스
			if (receptionCustomerIndex > K) {
				continue;
			}

			// 대기 중인 고객이 있으면
			if (k[receptionCustomerIndex][0] <= time) {
				// 접수 창구가 비어있으면
				if (receptionCustomers[i][0] == -1) {
					int startTime = max<int>(time, k[receptionCustomerIndex][0]);
					// 접수 종료 시간 = 접수시작시간 + 프로세스시간
					receptionCustomers[i][0] = receptionCustomerIndex;
					receptionCustomers[i][1] = startTime + n[i];
					k[receptionCustomerIndex][1] = i;
#ifdef DEBUG
					printf("시간 %d : 고객 %d, 접수처 %d ==> 처리시작\n", time, receptionCustomerIndex, i);
#endif // DEBUG
					receptionCustomerIndex++;
				}
			}
		}

		bool isFinished = false;
		// 정비창구 확인
		for (int i = 1; i <= M; i++) {
			// 정비가 완료된 곳이 있으면
			if (repairCustomers[i][1] == time) {
				repairCustomerNumber++;
#ifdef DEBUG
				printf("시간 %d : 고객 %d, 정비처 %d ==> 처리완료\n", time, repairCustomers[i][0], i);
#endif // DEBUG
				if (repairCustomerNumber == K) {
					isFinished = true;
					break;//
				}
				repairCustomers[i][0] = -1;
				repairCustomers[i][1] = -1;
			}

			// 대기 중인 고객이 있으면
			if (repairQueue.size() > 0) {
				// 정비 창구가 비어있으면
				if (repairCustomers[i][0] == -1) {
					// 정비종료시간 = 시작시간 + 프로세스시간
					repairCustomers[i][0] = repairQueue.front();
					repairCustomers[i][1] = time + m[i];
					k[repairQueue.front()][2] = i;
#ifdef DEBUG
					printf("시간 %d : 고객 %d, 정비처 %d ==> 처리시작\n", time, repairQueue.front(), i);
#endif // DEBUG
					repairQueue.pop_front();
				}
			}
		}

		if (isFinished)
			break;
		time++;
	}

	// 예상 고객을 선정
	int total = 0;
	for (int i = 1; i <= K; i++) {
		if (k[i][1] == A && k[i][2] == B)
			total += i;
	}
	if (total == 0)
		return -1;
	else
		return total;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		// 변수
		int n[10], m[10];
		int k[1001][3]; // [0]방문시간, [1]접수창구번호, [2]정비창구번호
		for (int i = 1; i <= 9; i++) {
			n[i] = -1;
			m[i] = -1;
		}
		for (int i = 1; i <= 1000; i++) {
			k[i][0] = -1;
			k[i][1] = -1;
			k[i][2] = -1;
		}

		// 입력 데이터
		int N, M, K, A, B;
		cin >> N >> M >> K >> A >> B;

		for (int i = 1; i <= N; i++) {
			cin >> n[i];
		}

		for (int i = 1; i <= M; i++) {
			cin >> m[i];
		}

		for (int i = 1; i <= K; i++) {
			cin >> k[i][0];
		}

		// 연산
		int result = solve(n, m, k, N, M, K, A, B);

		// 출력
		cout << "#" << caseCount << ' ' << result << endl;
	}

	return 0;
}