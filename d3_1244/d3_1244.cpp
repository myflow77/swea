// d3_1244.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

struct check
{
	int swap_count;
	int number;
};
//vector<check> check_list;

bool check_list[11][1000000];

void swap_board(string number_board, int &current_max, int swap_num)
{
	if (swap_num < 1) {
		// 현재 숫자판의 수가 지금까지 나온 최대치보다 크다면 갱신
		int temp_num = atoi(number_board.c_str());
		if (temp_num > current_max) {
			current_max = temp_num;
		}
	}
	else {
		// 현재 보드 상태에서 모든 경우의 수에 대해서 교환을 실행
		int board_length = number_board.length();
		for (int i = 0; i < board_length; i++) {
			for (int j = i + 1; j < board_length; j++) {
				// 숫자판을 교환하기 위해 임시 문자열 생성
				char temp_cboard[10];
				//strcpy(temp_cboard, number_board.c_str());
				strcpy_s(temp_cboard, number_board.c_str());

				// 숫자판 교환
				swap(temp_cboard[i], temp_cboard[j]);

				int after_num = atoi(temp_cboard);

				if (check_list[swap_num][after_num] == false) {
					string temp_board = temp_cboard;
					swap_board(temp_board, current_max, swap_num - 1);
					check_list[swap_num][after_num] = true;
				}
			}
		}
	}
}

int main()
{
	int case_num, case_count = 0;
	cin >> case_num;

	while (case_count < case_num) {
		int number_board, swap_num;
		cin >> number_board >> swap_num;

		// 완전탐색으로 풀자(dfs?)
		// 교환 횟수가 끝나는 시점에서 현재 점수와 비교해서 크면 교체
		// 숫자 그대로 넘겨서 메모리 펑펑쓰는걸로
		int current_max = number_board;; // 최소점수는 현재 점수

		stringstream ss;
		ss << number_board;
		swap_board(ss.str(), current_max, swap_num);

		cout << "#" << case_count + 1 << " " << current_max << endl;

		// 케이스 카운트 증가
		case_count++;
	}


	return 0;
}

