// 비밀번호

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

deque<char> pw;

bool one_step()
{
	bool modified = false;
	for (int i = 0; i < pw.size() - 1; i++) {
		if (pw[i] == pw[i + 1]) {
			pw.erase(pw.begin() + i);
			pw.erase(pw.begin() + i);
			modified = true;
		}
	}
	// 수정했다면 true 반환
	if (modified) {
		return true;
	}
	// 수정하지 않았다면 false 반환
	else {
		return false;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	int caseCount = 1;

	for (int caseCount = 1; caseCount <= 10; caseCount++)
	{
		////////////////////////////////////////////////////////////////////////////////////////////

		int pw_length;
		cin >> pw_length;

		pw.clear();
		for (int i = 0; i < pw_length; i++) {
			char temp;
			cin >> temp;
			pw.push_back(temp);
		}

		while (one_step()) {
			/*
			for (int i = 0; i < pw.size(); i++) {
				cout << pw[i];
			}
			cout << endl;
			*/
		}

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount << ' ';
		for (int i = 0; i < pw.size(); i++) {
			cout << pw[i];
		}
		cout << endl;
	}

	return 0;
}