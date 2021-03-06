#include <iostream>
#include <string>
#include <sstream>
#include <string.h>

using namespace std;

int main()
{
	int caseCount = -1;

	do
	{
		int result = -1;

		cin >> caseCount;

		////////////////////////////////////////////////////////////////////////////////////////////

		int matchCount = 0;

		string goalString;
		cin >> goalString;

		string wholeString;
		cin >> wholeString;

		char goalCString[100];
		strcpy(goalCString, goalString.c_str());
		int goalStringLength = goalString.length();

		char wholeCString[10000];
		strcpy(wholeCString, wholeString.c_str());
		int wholeStringLength = wholeString.length();

		for (int i = 0; i < wholeStringLength - goalStringLength + 1; i++) {
			for (int j = 0; j < goalStringLength; j++) {
				if (goalCString[j] != wholeCString[i + j]) {
					break;
				}
				if (j == goalStringLength - 1 && goalCString[j] == wholeCString[i + j]) {
					matchCount++;
					cout << i << endl;
				}
			}
		}

		result = matchCount;

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount << " " << result << endl;
	} while (caseCount < 10);

	return 0;
}

