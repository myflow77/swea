// 암호문 2

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

	for (int caseCount = 1; caseCount <= 10; caseCount++)
	{
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

			if (temp.c == 'I') {
				for (int j = 0; j < temp.y; j++) {
					string temp_num;
					cin >> temp_num;
					pw.insert(pw.begin() + temp.x + j, temp_num);
				}
			}
			else if (temp.c == 'D') {
				for (int j = 0; j < temp.y; j++) {
					pw.erase(pw.begin() + temp.x);
				}
			}
			else {
				// ERROR
			}
			
		}

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount;
		for (int i = 0; i < 10; i++) {
			cout << " " << pw[i];
		}
		cout << endl;
	}

	return 0;
}