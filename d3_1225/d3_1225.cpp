// 암호 생성기
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

deque<int> nums;

int main()
{
	freopen("input.txt", "r", stdin);

	int caseCount = 1;

	do
	{
		int result = 0;
		int c;

		cin >> c;

		////////////////////////////////////////////////////////////////////////////////////////////
		nums.clear();
		for (int i = 0; i < 8; i++) {
			int temp;
			cin >> temp;
			nums.push_back(temp);
		}

		bool is_zero = false;
		while (!is_zero) {
			for (int i = 1; i <= 5; i++) {
				int temp = nums.front();
				nums.pop_front();
				temp -= i;
				if (temp <= 0) {
					temp = 0;
					is_zero = true;
				}
				nums.push_back(temp);
				if (is_zero)
					break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount++;
		for (int i = 0; i < 8; i++) {
			cout << ' ' << nums[i];
		}
		cout << endl;
	} while (caseCount < 11);

	return 0;
}