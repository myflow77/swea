// 수영장

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

// 분리된 구간을 이용하기 위한 조건
// 1일 : 1일요금 * 월횟수 < 1개월요금
// 1개월 : (1)월요금 ~ (3)월요금 < 3개월요금
// 3개월 : (1)3개월요금 ~ (4)3개월요금 < 1년
// 1년 : 전부 아닐 경우
int findBestFee(int fee[], int schedule[], int currentMonth, int currentFee, int idealFee)
{
	// 현재 요금이 이전의 최저요금보다 비싸졌다면 이후를 확인할 필요는 없다
	if (currentFee > idealFee) {
		return -1;
	}
	// 1년 전체를 조사했다면 현재 요금 반환
	if (currentMonth > 11) {
		//cout << currentMonth << "월 : " << currentFee << endl;
		return currentFee;
	}

	int nextMonth; // 0~11월
	int bestFee = idealFee;
	int resultFee;

	// 0~11월 구간에서만 실시
	if (currentMonth < 12) {
		// 1일 요금 사용 시
		nextMonth = currentMonth + 1;
		resultFee = findBestFee(fee, schedule, nextMonth, currentFee + fee[0] * schedule[currentMonth], bestFee);
		if (resultFee > -1)
			bestFee = min<int>(bestFee, resultFee);

		// 1개월 요금 사용 시
		nextMonth = currentMonth + 1;
		resultFee = findBestFee(fee, schedule, nextMonth, currentFee + fee[1], bestFee);
		if (resultFee > -1)
			bestFee = min<int>(bestFee, resultFee);

		// 3개월 요금 사용 시
		nextMonth = currentMonth + 3;
		resultFee = findBestFee(fee, schedule, nextMonth, currentFee + fee[2], bestFee);
		if (resultFee > -1)
			bestFee = min<int>(bestFee, resultFee);
	}

	return bestFee;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int maxCount;

	cin >> maxCount;

	for (int caseCount = 1; caseCount <= maxCount; caseCount++)
	{
		int fee[4];
		int schedule[12];

		// 데이터 입력
		for (int i = 0; i < 4; i++) {
			cin >> fee[i];
		}

		for (int i = 0; i < 12; i++) {
			cin >> schedule[i];
		}

		// 연산
		int bestFee = fee[3]; // 최저비용을 1년권 비용으로 초기화
		bestFee = findBestFee(fee, schedule, 0, 0, bestFee);


		// 출력
		cout << "#" << caseCount << ' ';
		cout << bestFee << endl;
	}

	return 0;
}