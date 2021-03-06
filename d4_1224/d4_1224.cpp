// 계산기 3

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

int change_to_post(int start)
{
	vector<int> stack;

	int current = start;
	while (current < input_string.size()) {
		char current_char = input_string[current];
		// 숫자
		if (is_int(current_char)) {
			post_string.push_back(current_char);
		}
		// +
		else if (current_char == '+') {
			// 스택의 모든 기호를 배열에 추가
			while (stack.empty() == false) {
				post_string.push_back(stack.back());
				stack.pop_back();
			}
			// 자신을 스택에 추가
			stack.push_back(current_char);
		}
		// *
		else if (current_char == '*') {
			if (stack.empty() == false) {
				// + 를 만나면 자신을 스택에 추가
				if (stack.back() == '+' || stack.back() == '*') {
					stack.push_back(current_char);
				}
			}
			else {
				// 스택이 비어있으면 자신을 스택에 추가
				stack.push_back(current_char);
			}
		}
		// (
		else if (current_char == '(') {
			// current + 1부터 시작하는 내부 연산을 변환
			current = change_to_post(current + 1);
		}
		// )
		else if (current_char == ')') {
			// 내부 연산을 종료
			break;
		}
		current++;
	}
	// 스택을 비우고 current 반환
	while (stack.empty() == false) {
		post_string.push_back(stack.back());
		stack.pop_back();
	}
	return current;
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

		int final_index = change_to_post(0);

		length = post_string.size();
		
		/*
		for (int i = 0; i < length; i++)
		cout << post_string[i];
		cout << endl;
		*/

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

				int result;
				if (post_string[current] == '+') {
					result = left + right;
				}
				else if (post_string[current] == '*') {
					result = left * right;
				}
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

