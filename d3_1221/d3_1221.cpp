// GNS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct number
{
	int ours;
	string yours;
};

number table[10] = {
	{ 0, "ZRO" },
	{ 1, "ONE" },
	{ 2, "TWO" },
	{ 3, "THR" },
	{ 4, "FOR" },
	{ 5, "FIV" },
	{ 6, "SIX" },
	{ 7, "SVN" },
	{ 8, "EGT" },
	{ 9, "NIN" },
};

vector<int> list;

int get_integer(string str)
{
	for (int i = 0; i < 10; i++) {
		if (str == table[i].yours) {
			return table[i].ours;
		}
	}
}

string get_string(int num)
{
	for (int i = 0; i < 10; i++) {
		if (num == table[i].ours) {
			return table[i].yours;
		}
	}
}

int main()
{
	int case_max = 0;
	cin >> case_max;

	for (int case_num = 1; case_num <= case_max; case_num++) {
		list.clear();
		string trash;
		int length;

		cin >> trash >> length;

		int result = 0;

		//////////////////////////////

		for (int i = 0; i < length; i++) {
			string temp;
			cin >> temp;
			list.push_back(get_integer(temp));
		}

		sort(list.begin(), list.end());

		//////////////////////////////

		cout << "#" << case_num << endl;
		for (int i = 0; i < length; i++) {
			if (i != 0)
				cout << " ";
			cout << get_string(list[i]);
		}
		cout << endl;

	}

	return 0;
}

