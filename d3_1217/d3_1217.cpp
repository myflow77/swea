// 두 수의 거듭제곱을 계산

#include <iostream>

using namespace std;

int power(int base, int loop, int current) {
	if (loop < 1)
		return current;
	return power(base, loop - 1, current * base);
}

int main()
{
	int caseCount = -1;

	do
	{
		int result = -1;

		cin >> caseCount;

		////////////////////////////////////////////////////////////////////////////////////////////
		int base, loop;

		cin >> base >> loop;

		result = power(base, loop, 1);

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount << " " << result << endl;
	} while (caseCount < 10);

	return 0;
}