// 행렬찾기

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class SubMatrix
{
public:
	int rowStart, colStart;
	int rowSize, colSize;
	int size;

	SubMatrix(int _rowStart, int _colStart, int _rowSize, int _colSize);
	int getSize();
	int getBig();
	int getSmall();
	bool operator<(SubMatrix a) const {
		if (this->size == a.size)
			return this->rowSize < a.rowSize;
		else
			return this->size < a.size;
	}
};

SubMatrix::SubMatrix(int _rowStart, int _colStart, int _rowSize, int _colSize)
{
	rowStart = _rowStart;
	colStart = _colStart;
	rowSize = _rowSize;
	colSize = _colSize;
	size = _rowSize * _colSize;
}

int SubMatrix::getSize()
{
	return size;
}

int SubMatrix::getBig()
{
	if (rowSize > colSize)
		return rowSize;
	else
		return colSize;
}

int SubMatrix::getSmall()
{
	if (rowSize < colSize)
		return rowSize;
	else
		return colSize;
}

int main()
{
	freopen("input.txt", "r", stdin);

	int caseSize;

	cin >> caseSize;

	for (int caseCount = 1; caseCount <= caseSize; caseCount++)
	{
		// 초기화
		int matrix[100][100];
		vector<SubMatrix> subMatrixList;

		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				matrix[i][j] = -1;
			}
		}

		// 데이터 입력
		int n;
		cin >> n;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> matrix[i][j];
			}
		}

		// n * n 행렬에서 탐색을 시작
		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				int currentValue = matrix[row][col];
				// 현재 위치의 값이 0보다 크면 내부 행렬 탐색을 시작
				if (currentValue > 0) {
					// 가로로 0이 나올 때까지 탐색
					int colMax = -1;
					for (int j = col; j < n; j++) {
						if (matrix[row][j] == 0) {
							colMax = j;
							break;
						}
					}
					if (colMax == -1)
						colMax = n;
					// 세로로 0이 나올때까지 탐색
					int rowMax = -1;
					for (int i = row; i < n; i++) {
						if (matrix[i][col] == 0) {
							rowMax = i;
							break;
						}
					}
					if (rowMax == -1)
						rowMax = n;
					// 테스트
					//printf("%d~%d, %d~%d\n", row, rowMax, col, colMax);
					// 서브행렬이 유효한지 확인
					bool existZero = false;
					bool borderZero = true;
					bool sameRowCol = false;
					// 내부에 0이 없는가
					for (int i = row; i < rowMax; i++) {
						for (int j = col; j < colMax; j++) {
							if (matrix[i][j] == 0) {
								existZero = true;
								break;
							}
						}
					}
					// 테두리가 0으로 둘러쌓여있는가
					if (borderZero) {
						for (int j = col; j < colMax; j++) { // 상
							if (row - 1 >= 0 && matrix[row - 1][j] != 0) {
								borderZero = false;
								break;
							}
						}
					}
					if (borderZero) {
						for (int j = col; j < colMax; j++) { // 하
							if (rowMax < n && matrix[rowMax][j] != 0) {
								borderZero = false;
								break;
							}
						}
					}
					if (borderZero) {
						for (int i = row; i < rowMax; i++) { // 좌
							if (col - 1 >= 0 && matrix[i][col - 1] != 0) {
								borderZero = false;
								break;
							}
						}
					}
					if (borderZero) {
						for (int i = row; i < rowMax; i++) { // 우
							if (colMax < n && matrix[i][colMax] != 0) {
								borderZero = false;
								break;
							}
						}
					}
					// 행의 크기와 열의 크기가 다른가
					if (rowMax - row == colMax - col)
						sameRowCol = true;
					// 서브행렬이 유효할 경우
					if (existZero == false && borderZero == true && sameRowCol == false) {
						// 리스트에 저장
						SubMatrix sub(row, col, rowMax - row, colMax - col);
						subMatrixList.push_back(sub);
						// 행렬에 -1 마킹
						for (int i = row; i < rowMax; i++) {
							for (int j = col; j < colMax; j++) {
								matrix[i][j] = -1;
							}
						}
					}
				}
			}
		}

		sort(subMatrixList.begin(), subMatrixList.end());

		// 출력
		cout << "#" << caseCount << ' ';
		cout << subMatrixList.size() << ' ';
		for (int i = 0; i < subMatrixList.size(); i++) {
			printf("%d %d ", subMatrixList[i].rowSize, subMatrixList[i].colSize);
		}
		cout << endl;
	}

	return 0;
}