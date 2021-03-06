// 암호문 1

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <deque>
#include <string>

using namespace std;

struct command
{
	char c;
	int x;
	int y;
	deque<string> nums;
};

int main()
{
	freopen("input.txt", "r", stdin);

	int caseCount = 1;

	do
	{
		int result = 0;

		////////////////////////////////////////////////////////////////////////////////////////////

		int num;
		deque<string> pw;
		int command_num;
		deque<command> commands;
		

		cin >> num;

		for (int i = 0; i < num; i++) {
			string temp;
			cin >> temp;
			pw.push_back(temp);
		}

		cin >> command_num;

		for (int i = 0; i < command_num; i++) {
			command temp;

			cin >> temp.c >> temp.x >> temp.y;
			for (int j = 0; j < temp.y; j++) {
				string temp_num;
				cin >> temp_num;
				//temp.nums.push_back(temp_num);
				pw.insert(pw.begin() + temp.x + j, temp_num);
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount++;
		for (int i = 0; i < 10; i++) {
			cout << " " << pw[i];
		}
		cout << endl;
	} while (caseCount < 11);

	return 0;
}