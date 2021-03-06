// 1206.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int count = 1;
	while (count <= 10) {
		int goodPlace = 0;

		int ary[1000];
		for (int i = 0; i < 1000; i++) {
			ary[i] = -1;
		}

		int N;
		cin >> N;

		for (int i = 0; i < N; i++) {
			int temp;
			cin >> temp;
			ary[i] = temp;
		}

		for (int i = 0; i < N; i++) {
			int height = ary[i]; // 현재 건물의 높이
			for (int j = 0; j <= height; j++) {
				// 건물을 아래에서 위로 타고 올라감
				// j = 현재 위치
				bool trigger = true;
				if (i - 2 >= 0 && ary[i - 2] >= j) {
					trigger = false;
				}
				if (i - 1 >= 0 && ary[i - 1] >= j) {
					trigger = false;
				}
				if (i + 1 < N && ary[i + 1] >= j) {
					trigger = false;
				}
				if (i + 2 < N && ary[i + 2] >= j) {
					trigger = false;
				}
				if (trigger)
					goodPlace++;
			}
		}
		cout << "#" << count++ << " " << goodPlace << endl;
	}

    return 0;
}

