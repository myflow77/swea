// 중위순회

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>

using namespace std;

class node
{
public:
	char op;
	int number;
	int left;
	int right;

	node()
	{
		op = NULL;
		number = 0;
		left = -1;
		right = -1;
	}

private:

};

bool isOperator(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/') {
		return true;
	}
	else {
		return false;
	}
}

bool isNumber(char op)
{
	if ('0' <= op && op <= '9') {
		return true;
	}
	else {
		return false;
	}
}

int inorderExplore(node tree[], int current, int maxLength)
{
	if (tree[current].op == NULL) {
		return tree[current].number;
	}
	else {
		int left, right, result;
		if (tree[current].left != -1)
			left = inorderExplore(tree, tree[current].left, maxLength);
		if (tree[current].right != -1)
			right = inorderExplore(tree, tree[current].right, maxLength);
		if (tree[current].op == '+')
			return left + right;
		else if (tree[current].op == '-')
			return left - right;
		else if (tree[current].op == '*')
			return left * right;
		else if (tree[current].op == '/')
			return left / right;
		else {
			cout << "Error" << endl;
			return 9999;
		}

	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	int caseCount = 1;

	for (int caseCount = 1; caseCount <= 10; caseCount++)
	{
		node tree[1001];

		////////////////////////////////////////////////////////////////////////////////////////////

		int maxLength;
		string none;

		// 트리 노드 수 입력
		getline(cin, none);
		stringstream stream;

		stream.str(none);
		stream >> maxLength;

		//cout << maxLength << endl;

		// 트리에 문자 입력
		for (int i = 1; i <= maxLength; i++) {
			string line;
			getline(cin, line);

			stringstream stream1;
			stream1.str(line);

			int index;
			char check;
			char op;
			int number;
			int left = NULL, right = NULL;

			stream1 >> index >> check;
			if (isOperator(check)) {
				stringstream stream2;
				stream2.str(line);
				stream2 >> index >> op >> left >> right;
				tree[index].op = op;
				if (left != NULL) {
					tree[index].left = left;
				}
				if (right != NULL) {
					tree[index].right = right;
				}
			}
			else if (isNumber(check)) {
				stringstream stream2;
				stream2.str(line);
				stream2 >> index >> number >> left >> right;
				tree[index].number = number;
				if (left != NULL) {
					tree[index].left = left;
				}
				if (right != NULL) {
					tree[index].right = right;
				}
			}
		}

		/*for (int i = 1; i <= maxLength; i++) {
			cout << i << ' ' << tree[i].op << ' ' << tree[i].number << ' ' << tree[i].left << ' ' << tree[i].right << endl;
		}*/

		int result = inorderExplore(tree, 1, maxLength);

		////////////////////////////////////////////////////////////////////////////////////////////

		// 중위순회하면서 출력
		cout << "#" << caseCount << ' ';

		cout << result << endl;
	}

	return 0;
}