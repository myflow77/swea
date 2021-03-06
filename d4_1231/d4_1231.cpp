// 중위순회

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>

using namespace std;

char tree[101];

void inorderExplore(char tree[], int current, int maxLength, string &result) {
	if (current * 2 <= maxLength)
		inorderExplore(tree, current * 2, maxLength, result);

	result += tree[current];
	
	if (current * 2 + 1 <= maxLength)
		inorderExplore(tree, current * 2 + 1, maxLength, result);
}

int main()
{
	freopen("input.txt", "r", stdin);

	int caseCount = 1;

	for (int caseCount = 1; caseCount <= 10; caseCount++)
	{
		////////////////////////////////////////////////////////////////////////////////////////////

		for (int i = 0; i < 101; i++) {
			tree[i] = NULL;
		}

		int maxLength;
		string none;
		
		// 트리 노드 수 입력
		getline(cin, none);
		stringstream stream;

		stream.str(none);
		stream >> maxLength;

		// 트리에 문자 입력
		for (int i = 1; i <= maxLength; i++) {
			string line;
			getline(cin, line);

			stringstream stream2;
			stream2.str(line);

			int index;
			char value;
			stream2 >> index >> value;
			tree[index] = value;
		}

		for (int i = 1; i <= maxLength; i++) {
			tree[i];
		}

		string result = "";
		inorderExplore(tree, 1, maxLength, result);

		////////////////////////////////////////////////////////////////////////////////////////////

		// 중위순회하면서 출력
		cout << "#" << caseCount << ' ';
		
		cout << result << endl;
	}

	return 0;
}