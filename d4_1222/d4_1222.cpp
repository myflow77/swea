// 계산기 1

#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

vector<char> input_string;
vector<char> post_string;


bool is_int(char temp)
{
	if ('0' <= temp && temp <= '9') {
		return true;
	}
	else
	{
		return false;
	}
}

void change_to_post()
{
	deque<int> stack;

	int current = 0;
	while (current < input_string.size()) {
		if (is_int(input_string[current])) {
			stack.push_back(input_string[current]);
		}
		else if (stack.empty() == true) {
			stack.push_back(input_string[current + 1]);
			stack.push_back(input_string[current]);
			current++;
		}
		else {
			stack.push_back(input_string[current + 1]);
			stack.push_back(input_string[current]);
			current++;
		}
		current++;
	}
	// 출력
	while (stack.empty() == false) {
		post_string.push_back(stack.front());
		stack.pop_front();
	}
}

int main()
{
	int caseCount = 1;

	do
	{
		int result = 0;
		int length;
		vector<int> stack;

		input_string.clear();
		post_string.clear();

		cin >> length;

		////////////////////////////////////////////////////////////////////////////////////////////

		for (int i = 0; i < length; i++) {
			char temp;
			cin >> temp;
			input_string.push_back(temp);
		}

		change_to_post();

		int current = 0;
		while (current < length) {
			if (is_int(post_string[current])) {
				stack.push_back(post_string[current]);
			}
			else {
				int right = stack.back() - '0';
				stack.pop_back();

				int left = stack.back() - '0';
				stack.pop_back();

				int result = left + right;
				stack.push_back(result + '0');
			}
			current++;
		}

		result = stack.back() - '0';

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount++ << " " << result << endl;
	} while (caseCount < 11);

	return 0;
}

