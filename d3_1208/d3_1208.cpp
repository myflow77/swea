// d3_1208.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <iostream>
#include <limits.h>

using namespace std;

int ary[100];
int maxPosition = INT_MIN;
int maxHeight = INT_MIN;
int minPosition = INT_MAX;
int minHeight = INT_MAX;

void dump()
{
	ary[maxPosition]--;
	ary[minPosition]++;
	
	maxPosition = INT_MIN;
	maxHeight = INT_MIN;
	minPosition = INT_MAX;
	minHeight = INT_MAX;

	for (int i = 0; i < 100; i++) {
		if (ary[i] > maxHeight) {
			maxHeight = ary[i];
			maxPosition = i;
		}

		if (ary[i] < minHeight) {
			minHeight = ary[i];
			minPosition = i;
		}
	}
}

int main()
{
	int count = 0;

	while (count++ < 10) {
		int dumpCount;
		cin >> dumpCount;
		
		for (int i = 0; i < 100; i++) {
			int tempNum;
			cin >> tempNum;
			ary[i] = tempNum;

			if (tempNum > maxHeight) {
				maxHeight = tempNum;
				maxPosition = i;
			}

			if (tempNum < minHeight) {
				minHeight = tempNum;
				minPosition = i;
			}
		}

		while (dumpCount-- > 0) {
			dump();
		}

		cout << "#" << count << " " << maxHeight - minHeight << endl;
	}

    return 0;
}

