// 요리사

#define _CRT_SECURE_NO_WARNINGS

//#define DEBUG

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Combination {
public:
	vector<int> materials;
	int sumValue;

	Combination() {
		sumValue = 0;
	}

	void addMaterial(int &material) {
		materials.push_back(material);
	}

	void setSumValue(int table[][16]) {
		for (int i = 0; i < materials.size() - 1; i++) {
			for (int j = i + 1; j < materials.size(); j++) {
				int material0 = materials[i], material1 = materials[j];
				int value0, value1;
				value0 = table[material0][material1];
				value1 = table[material1][material0];
				sumValue += (value0 + value1);
			}
		}
#ifdef DEBUG
		for (int i = 0; i < materials.size(); i++) {
			cout << materials[i] << " ";
		}
		cout << " : " << sumValue << endl;
#endif // DEBUG
	}

	bool isDifferent(Combination &c) {
		bool isDifferent = true;
		for (int i = 0; i < materials.size(); i++) {
			for (int j = 0; j < c.materials.size(); j++) {
				if (materials[i] == c.materials[j]) {
					isDifferent = false;
					break;
				}
				else if (materials[i] < c.materials[j]) {
					break;
				}
			}
			if (!isDifferent)
				break;
		}
		
		return isDifferent;
	}

	int getDifference(Combination &c) {
		return abs(sumValue - c.sumValue);
	}

	bool operator<(Combination &c) const {
		return sumValue < c.sumValue;
	}
};

void dfs(int &N, int table[][16], bool usableStartingNumber[], Combination combinationA, Combination combinationB, int numberOfA, int numberOfB, int currentPosition, int &minDifference)
{
	if (currentPosition == N) {
		combinationA.setSumValue(table);
		combinationB.setSumValue(table);

		int difference = combinationA.getDifference(combinationB);
		if (difference < minDifference) {
			minDifference = difference;
#ifdef DEBUG
			
#endif // DEBUG
		}
	}
	else {
		if (numberOfA < N / 2) {
			if (numberOfA == 0) {
				if (usableStartingNumber[currentPosition]) {
					// A에 추가
					Combination newCombinationA = combinationA;
					newCombinationA.addMaterial(currentPosition);
					usableStartingNumber[currentPosition] = false;
					dfs(N, table, usableStartingNumber, newCombinationA, combinationB, numberOfA + 1, numberOfB, currentPosition + 1, minDifference);
				}
			}
			else {
				// A에 추가
				Combination newCombinationA = combinationA;
				newCombinationA.addMaterial(currentPosition);
				dfs(N, table, usableStartingNumber, newCombinationA, combinationB, numberOfA + 1, numberOfB, currentPosition + 1, minDifference);
			}
		}
		if (numberOfB < N / 2) {
			if (numberOfB == 0) {
				if (usableStartingNumber[currentPosition]) {
					// B에 추가
					Combination newCombinationB = combinationB;
					newCombinationB.addMaterial(currentPosition);
					usableStartingNumber[currentPosition] = false;
					dfs(N, table, usableStartingNumber, combinationA, newCombinationB, numberOfA, numberOfB + 1, currentPosition + 1, minDifference);
				}
			}
			else {
				// B에 추가
				Combination newCombinationB = combinationB;
				newCombinationB.addMaterial(currentPosition);
				dfs(N, table, usableStartingNumber, combinationA, newCombinationB, numberOfA, numberOfB + 1, currentPosition + 1, minDifference);
			}
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		int table[16][16];
		bool usableStartingNumber[16];
		for (int i = 0; i < 16; i++) {
			usableStartingNumber[i] = true;
		}
		int N;

		cin >> N;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> table[i][j];
			}
		}

		Combination combinationA, combinationB;
		int minDifference = INT_MAX;
		dfs(N, table, usableStartingNumber, combinationA, combinationB, 0, 0, 0, minDifference);


		int result = minDifference;

		// 출력
		cout << "#" << caseCount << ' ' << result << endl;
	}

	return 0;
}