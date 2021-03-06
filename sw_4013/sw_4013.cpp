// 특이한 자석

#define _CRT_SECURE_NO_WARNINGS

//#define DEBUG

#include <iostream>
#include <cstdio>
#include <deque>
#include <cmath>

using namespace std;

class MagnetPanel {
public:
	const int right = 2;
	const int left = 6;
	deque<int> magnets;

	MagnetPanel() {

	}

	void addMagnet(int m) {
		magnets.push_back(m);
	}

	int topMagnet() {
		return magnets.front();
	}

	int rightMagnet() {
		return magnets[right];
	}

	int leftMagnet() {
		return magnets[left];
	}

	void clockwise() {
		magnets.push_front(magnets.back());
		magnets.pop_back();
	}

	void counterClockwise() {
		magnets.push_back(magnets.front());
		magnets.pop_front();
	}
};

void chainRotation(deque<MagnetPanel> &magnetPanels, bool canRotate[], int position, int rotation) {
	canRotate[position] = false;

	int CLOCKWISE = 1;
	int COUNTERCLOCKWISE = -1;
	
	int leftPosition = position - 1;
	int rightPosition = position + 1;
	bool leftIsDifferent, rightIsDifferent;
	int otherRotation;

	if (leftPosition >= 0 && canRotate[leftPosition]) {
		leftIsDifferent = (magnetPanels[position].leftMagnet() != magnetPanels[leftPosition].rightMagnet());
	}

	if (rightPosition < 4 && canRotate[rightPosition]) {
		rightIsDifferent = (magnetPanels[position].rightMagnet() != magnetPanels[rightPosition].leftMagnet());
	}

	if (rotation == CLOCKWISE) {
		magnetPanels[position].clockwise();
		otherRotation = COUNTERCLOCKWISE;
	}
	else {
		magnetPanels[position].counterClockwise();
		otherRotation = CLOCKWISE;
	}

#ifdef DEBUG
	printf("%d번 자석 %d 방향 회전\n", position + 1, rotation);
#endif // DEBUG


	if (leftPosition >= 0 && canRotate[leftPosition] && leftIsDifferent) {
		chainRotation(magnetPanels, canRotate, leftPosition, otherRotation);
	}

	if (rightPosition < 4 && canRotate[rightPosition] && rightIsDifferent) {
		chainRotation(magnetPanels, canRotate, rightPosition, otherRotation);
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int caseCount = 1; caseCount <= T; caseCount++)
	{
		//MagnetPanel magnetPanels[4];
		deque<MagnetPanel> magnetPanels(4);
		int rotationInfo[20][2]; // [0] : 회전하는 자석 번호, [1] : 회전 방향

		int K;

		cin >> K;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				int temp;
				cin >> temp;
				magnetPanels[i].addMagnet(temp);
			}
		}

		for (int i = 0; i < K; i++) {
			cin >> rotationInfo[i][0] >> rotationInfo[i][1];
		}

		for (int i = 0; i < K; i++) {
			bool canRotate[20];
			for (int j = 0; j < 20; j++) {
				canRotate[j] = true;
			}
			chainRotation(magnetPanels, canRotate, rotationInfo[i][0] - 1, rotationInfo[i][1]);
#ifdef DEBUG
			cout << endl;
#endif // DEBUG

		}

		int sum = 0;
		for (int i = 0; i < 4; i++) {
#ifdef DEBUG
			cout << magnetPanels[i].topMagnet() << endl;
#endif // DEBUG

			if (magnetPanels[i].topMagnet() == 1) {
				sum += pow(2, i);
			}
		}

		// 출력
		cout << "#" << caseCount << ' ' << sum << endl;
#ifdef DEBUG
		cout << endl;
#endif // DEBUG
	}

	return 0;
}