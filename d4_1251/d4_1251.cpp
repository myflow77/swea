// 하나로

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <limits>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

struct Node
{
	long long to;
	double price;
	Node *next;
};

struct Item
{
	long long from;
	long long to;
	double price;
};

bool operator>(Item a, Item b)
{
	return a.price > b.price;
}

double getPrice(long long x1, long long y1, long long x2, long long y2, double E)
{
	double distance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	double price = distance * E;

	return price;
}

void addNode(Node *islandsTable[1000], long long from, long long to, long long x1, long long y1, long long x2, long long y2, double E)
{
	if (islandsTable[from] == NULL) {
		Node *tempNode = new Node();
		tempNode->to = to;
		tempNode->price = getPrice(x1, y1, x2, y2, E);
		tempNode->next = NULL;

		islandsTable[from] = tempNode;
	}
	else {
		Node *currentNode = islandsTable[from];
		while (currentNode->next != NULL) {
			currentNode = currentNode->next;
		}
		Node *tempNode = new Node();
		tempNode->to = to;
		tempNode->price = getPrice(x1, y1, x2, y2, E);
		tempNode->next = NULL;

		currentNode->next = tempNode;
	}
}

//// 다익스트라를 통해서 spanning tree 생성
//void exploreIslands(Node *islandsTable[], double d[], long long p[], long long islandNumber)
//{
//	d[0] = 0;
//
//	priority_queue<Item, vector<Item>, greater<Item>> q;
//
//	// source(0)에서 갈 수 있는 노드를 큐에 삽입 -> 초기화
//	Node *currentNode = islandsTable[0];
//	while (currentNode != NULL) {
//		q.push({ currentNode->to, currentNode->price });
//		d[currentNode->to] = currentNode->price;
//		p[currentNode->to] = 0;
//		currentNode = currentNode->next;
//	}
//
//	// 큐가 빌때까지 반복
//	while (q.empty() == false) {
//		// 큐에서 총비용이 가장 작은 노드 회수
//		Item u = q.top();
//		q.pop();
//		
//		// 그 노드에서 갈 수 있는 노드를 순회하며 값을 비교
//		Node *neighbor = islandsTable[u.v];
//		while (neighbor != NULL) {
//			// source에서 u까지의 거리 + u에서 neighbor까지의 거리 -> source에서 neighbor까지의 거리 후보
//			double temp = d[u.v] + neighbor->price;
//			// u를 거치는 길이 더 비용이 작으면 교체한다
//			if (temp < d[neighbor->to]) {
//				d[neighbor->to] = temp;
//				p[neighbor->to] = u.v;
//				q.push({ neighbor->to, temp });
//			}
//
//			neighbor = neighbor->next;
//		}
//	}
//}

// 다익스트라를 수정해서 현재 집합에서 최단거리의 외부 노드를 추가
void exploreIslands(Node *islandsTable[], double d[], long long p[], long long islandNumber)
{
	long long U[1000];
	for (long long i = 0; i < 1000; i++) {
		U[i] = 0;
	}
	U[0] = 1;
	priority_queue<Item, vector<Item>, greater<Item>> q;

	// source(0)에서 갈 수 있는 노드를 큐에 삽입 -> 초기화
	Node *currentNode = islandsTable[0];
	while (currentNode != NULL) {
		q.push({ 0 ,currentNode->to, currentNode->price });
		d[currentNode->to] = currentNode->price;
		p[currentNode->to] = 0;
		currentNode = currentNode->next;
	}
	d[0] = 0;


	// 경로는 N - 1개가 나와야함
	while (true) {
		Item u = q.top();
		q.pop();

		if (U[u.to] == 1)
			continue;

		// 내부 집합에 추가
		U[u.to] = 1;
		p[u.to] = u.from;

		bool flag = true;
		for (long long i = 1; i < islandNumber; i++) {
			if (U[i] == 0) {
				flag = false;
				break;
			}
		}
		if (flag)
			break;

		// u에서 갈 수 있는 외부 집합의 노드를 큐에 추가
		Node *currentNode = islandsTable[u.to];
		while (currentNode != NULL) {
			if (U[currentNode->to] == 0) {
				q.push({ u.to ,currentNode->to, currentNode->price });
			}

			currentNode = currentNode->next;
		}
	}
}

// 출력용
void printRoute(Node *islandsTable[], double d[], long long p[], long long islandNumber)
{
	for (long long i = 0; i < islandNumber; i++) {
		cout << i << " : ";
		Node *currentNode = islandsTable[i];
		while (currentNode != NULL) {
			printf("%d [%f] ", currentNode->to, currentNode->price);

			currentNode = currentNode->next;
		}
		cout << endl;
	}
	
	for (long long i = 0; i < islandNumber; i++) {
		//printf("d[%d] : %d\n", i, d[i]);
	}
	for (long long i = 0; i < islandNumber; i++) {
		printf("p[%d] : %d\n", i, p[i]);
	}
	
}

int main()
{
	freopen("input.txt", "r", stdin);

	long long maxCount;

	cin >> maxCount;

	for (long long caseCount = 1; caseCount <= maxCount; caseCount++)
	{
		////////////////////////////////////////////////////////////////////////////////////////////

		Node *islandsTable[1000];
		double d[1000];
		long long p[1000];

		for (long long i = 0; i < 1000; i++) {
			islandsTable[i] = NULL;
			d[i] = 99999999.0;
			p[i] = -1;
		}
		d[0] = 0;

		long long islands[1000][2];

		long long islandNumber;

		cin >> islandNumber;

		for (long long i = 0; i < islandNumber; i++) {
			cin >> islands[i][0];
		}

		for (long long i = 0; i < islandNumber; i++) {
			cin >> islands[i][1];
		}

		double E;

		cin >> E;

		// 지도 생성
		for (long long i = 0; i < islandNumber; i++) {
			for (long long j = 0; j < islandNumber; j++) {
				if (i != j) {
					addNode(islandsTable, i, j, islands[i][0], islands[i][1], islands[j][0], islands[j][1], E);
				}
			}
		}
		
		// spanning tree 탐색
		exploreIslands(islandsTable, d, p, islandNumber);

		// 테스트
		//printRoute(islandsTable, d, p, islandNumber);

		// 총비용 계산
		double total = 0.0;
		for (long long i = 1; i < islandNumber; i++) {
			long long from = i;
			long long to = p[i];

			Node *currentNode = islandsTable[i];
			while (currentNode != NULL) {
				if (currentNode->to == to)
					break;
				currentNode = currentNode->next;
			}
			total += currentNode->price;
		}
		
		long long result = floor(total + 0.5);

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount << ' ';
		cout << result << endl;
	}

	return 0;
}