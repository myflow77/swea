#include <iostream>

using namespace std;

int map[100][100];

int main()
{
	int caseCount = -1;

	do
	{
		int result = 0;

		cin >> caseCount;

		////////////////////////////////////////////////////////////////////////////////////////////

		// 각 케이스 시작
		for (int row = 0; row < 100; row++) {
			for (int col = 0; col < 100; col++) {
				cin >> map[row][col];
			}
		}

		// 사다리 시작점을 찾아서 가로로 이동
		int px = 0, py = 0;
		int minPathCount = 99999;
		int minPathStart = -1;
		int dx = 0, dy = 1;

		// 오른쪽 끝날때까지 확인
		while (px < 100)
		{
			// 현재 x 위치 저장
			int sx = px;

			// 현재 위치가 사다리의 시작점인지 확인
			if (map[py][px] == 1) {
				int pathCount = 0;
				// 사다리 시작(높이가 100에 도달하면 종료)
				while (py < 100) {
					//cout << "x : " << px << ", " << "y : " << py << endl;

					// 현재 방향에 따라서 판단이 다름

					// 시작할 경우는 일단 아래쪽
					if (py == 0) {
						dx = 0; dy = 1;
					}
					// 아래쪽으로 이동하고 있을 경우
					else if (dx == 0 && dy == 1) {
						// 왼쪽 확인
						if (px - 1 >= 0 && map[py][px - 1] == 1) {
							// 왼쪽으로 방향 설정
							dx = -1; dy = 0;
						}
						// 오른쪽 확인
						else if (px + 1 < 100 && map[py][px + 1] == 1) {
							// 오른쪽으로 방향 설정
							dx = 1; dy = 0;
						}
						// 둘 다 아니면 아래 방향으로 설정
						else {
							dx = 0; dy = 1;
						}
					}
					// 좌우로 이동하고 있을 경우
					else if (dy == 0) {
						// 현재 방향으로 이동하면 막히는지 확인
						if (px + dx < 0 || px + dx >= 100 || map[py + dy][px + dx] == 0) {
							// 막히면 아래 방향으로 설정
							dx = 0; dy = 1;
						}
					}

					// 설정된 방향으로 이동
					px += dx; py += dy;
					pathCount++;

					// 끝인지 확인
					if (py == 99) {
						if (pathCount <= minPathCount) {
							minPathCount = pathCount;
							minPathStart = sx;
						}

						break;
					}
				}
			}
			px = sx; py = 0; px++;
		}

		result = minPathStart;

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount << " " << result << endl;
	} while (caseCount < 10);

	return 0;
}

