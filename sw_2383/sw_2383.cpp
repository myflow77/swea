// 점심 식사시간

#define _CRT_SECURE_NO_WARNINGS

//#define DEBUG

#include <iostream>
#include <cstdio>
#include <deque>
#include <cmath>
#include <algorithm>

using namespace std;

class Person {
public:
	int row, col;
	int stairIndex;
	int stairTime[2];

	Person(int r, int c) {
		row = r;
		col = c;
		stairIndex = 0;
	}

	void setStair(int r, int c) {
		if (stairIndex < 2) {
			stairTime[stairIndex] = abs(row - r) + abs(col - c);
			stairIndex++;
		}
		else {
			cout << "계단 2 초과" << endl;
		}
	}

	int minStair() {
		if (stairTime[0] > stairTime[1]) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int minStairTime() {
		return min<int>(stairTime[0], stairTime[1]);
	}

	bool operator<(Person p) {
		return minStairTime() < p.minStairTime();
	}
};

class Stair {
public:
	int stairNumber;
	int row, col;
	int K;
	// 그 사람이 계단에 도착하는 시간을 저장
	deque<int> persons;
	// 그 사람이 계단을 빠져나가는 시간을 저장
	deque<int> stairPersons;

	Stair(int s, int r, int c, int k) {
		stairNumber = s;
		row = r;
		col = c;
		K = k;
	}

	// 현재 계단에 있는 가장 빠른 사람이 완료되는 시간
	int firstPersonRemoveTime() {
		if (stairPersons.size() < 3) {
			return 0;
		}
		else {
			//return stairPersons.at(0);
			int minTime = stairPersons.at(0);
			for (int i = 0; i < stairPersons.size(); i++) {
				if (stairPersons[i] < minTime)
					minTime = stairPersons[i];
			}
			return minTime;
		}
	}

	// 현재 계단에 있는 가장 느린 사람이 완료되는 시간
	int lastPersonRemoveTime() {
		if (stairPersons.size() == 0) {
			return 0;
		}
		else {
			//return stairPersons.at(stairPersons.size() - 1);
			int maxTime = stairPersons.at(0);
			for (int i = 0; i < stairPersons.size(); i++) {
				if (stairPersons[i] > maxTime)
					maxTime = stairPersons[i];
			}
			return maxTime;
		}
	}

	// 계단에 사람을 보냄
	void pushPerson(Person person) {
		persons.push_back(person.stairTime[stairNumber] + 1);
	}

	// 사람들이 도착 순서대로 계단을 내려가기 시작
	// 가장 최후에 나간 사람의 시간을 반환
	int pushPersonsToStair() {
		// 사람들을 도착 순서대로 정렬
		sort(persons.begin(), persons.end());
		// 계단으로 내려보내기 시작
		for (int i = 0; i < persons.size(); i++) {
			// 계단에 0, 1, 2명이 있을 경우에는 즉시 출발
			if (stairPersons.size() < 3) {
				stairPersons.push_back(persons[i] + K);
			}
			// 사람이 3명 이상 있을 경우에는 1명이 나가면 출발
			else {
				int startTime = max<int>(persons[i], stairPersons[i - 3]);
				stairPersons.push_back(startTime + K);
			}
		}

		/*for (int i = 0; i < persons.size(); i++) {
		cout << persons[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < stairPersons.size(); i++) {
		cout << stairPersons[i] << " ";
		}
		cout << endl;*/

		// 가장 최후에 나간 사람의 시간을 반환
		if (stairPersons.size() > 0) {
			return stairPersons[stairPersons.size() - 1];
		}
		else {
			return 0;
		}
	}

	void printStair() {
		for (int i = 0; i < stairPersons.size(); i++) {
			printf("계단 %d - %d : %d\n", stairNumber, i, stairPersons[i]);
		}
	}
};

int searchMinCase(deque<Person> &persons, deque<Stair> stairs, int minTime, int index)
{
	if (index >= persons.size()) {
		int time0 = stairs[0].pushPersonsToStair();
		//cout << "-------------------------------------------------" << endl;
		int time1 = stairs[1].pushPersonsToStair();
		//cout << "=================================================" << endl;


		return max<int>(time0, time1);

		if (time0 == 0) {
			return time1;
		}
		else if (time1 == 0) {
			return time0;
		}
		else {
			return max<int>(time0, time1);
		}
	}
	/*else if (max<int>(stairs[0].lastPersonRemoveTime(), stairs[1].lastPersonRemoveTime()) > minTime) {
	return minTime;
	}*/
	else {
		int returnValue;
		deque<Stair> stairs0 = stairs;
		stairs0[0].pushPerson(persons[index]);
		returnValue = searchMinCase(persons, stairs0, minTime, index + 1);
		minTime = min(minTime, returnValue);


		deque<Stair> stairs1 = stairs;
		stairs1[1].pushPerson(persons[index]);
		returnValue = searchMinCase(persons, stairs1, minTime, index + 1);
		minTime = min(minTime, returnValue);

		return minTime;
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		int map[10][10];
		int stair[2][3];
		deque<Person> persons;
		deque<Stair> stairs;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				map[i][j] = -1;
			}
		}

		int N;

		cin >> N;

		int stairIndex = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1) {
					Person tempPerson(i, j);
					persons.push_back(tempPerson);
				}
				else if (map[i][j] > 1) {
					stair[stairIndex][0] = i;
					stair[stairIndex][1] = j;
					stair[stairIndex][2] = map[i][j];
					stairIndex++;
				}
			}
		}

		// 각 사람에게 계단 위치 세팅
		for (int i = 0; i < 2; i++) {
			for (int p = 0; p < persons.size(); p++) {
				persons[p].setStair(stair[i][0], stair[i][1]);
			}
			Stair tempStair(i, stair[i][0], stair[i][1], stair[i][2]);
			stairs.push_back(tempStair);
		}

		//sort(persons.begin(), persons.end());

		int result = searchMinCase(persons, stairs, 9999, 0);

		// 출력
		cout << "#" << caseCount << ' ' << result << endl;
	}

	return 0;
}