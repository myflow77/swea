// Contact

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

struct node
{
	int number;
	node *next;
};

struct contact
{
	int number;
	int time;
};

void addNode(node *members[], int from, int to)
{
	if (members[from] == NULL) {
		node *tempNode = new node();
		tempNode->number = to;
		tempNode->next = NULL;

		members[from] = tempNode;
	}
	else
	{
		node *currentNode = members[from];
		// 이미 같은 노드가 있으면 함수 종료
		if (currentNode->number == to)
			return;
		while (currentNode->next != NULL) {
			// 다음 노드
			currentNode = currentNode->next;
			// 이미 같은 노드가 있으면 함수 종료
			if (currentNode->number == to)
				return;
		}

		node *tempNode = new node();
		tempNode->number = to;
		tempNode->next = NULL;

		currentNode->next = tempNode;
	}
}

//void contactMembers(node *members[], bool visited[], int times[], int current, int time)
//{
//	visited[current] = true;
//	times[current] = time;
//	if (members[current] != NULL) {
//		node *currentNode = members[current];
//		while (currentNode != NULL)
//		{
//			if (visited[currentNode->number] == false) {
//				//cout << currentNode->number << ' ' << time << endl;
//				contactMembers(members, visited, times, currentNode->number, time + 1);
//			}
//			currentNode = currentNode->next;
//		}
//	}
//}

// 큐기반
void contactMembers(deque<contact> &contactQueue, node *members[], bool visited[], int times[], int current, int time)
{
	//cout << current << ' ' << time << endl;
	if (members[current] != NULL) {
		node *currentNode = members[current];
		while (currentNode != NULL)
		{
			if (visited[currentNode->number] == false) {
				contact tempContact = { currentNode->number, time + 1 };
				contactQueue.push_back(tempContact);

				visited[currentNode->number] = true;
				times[currentNode->number] = time + 1;
			}
			currentNode = currentNode->next;
		}
	}
}

void printMembers(node *members[]) {
	// 테스트용 출력함수
	for (int i = 0; i < 101; i++) {
		cout << i << ' ';
		node *currentNode = members[i];
		while (currentNode != NULL)
		{
			cout << currentNode->number << ' ';
			currentNode = currentNode->next;
		}
		cout << endl;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	int caseCount = 1;

	for (int caseCount = 1; caseCount <= 10; caseCount++)
	{
		////////////////////////////////////////////////////////////////////////////////////////////

		node *members[101];
		for (int i = 0; i < 101; i++) {
			members[i] = NULL;
		}

		int length, startSpot;
		cin >> length >> startSpot;

		for (int i = 0; i < length / 2; i++) {
			int from, to;
			cin >> from >> to;
			addNode(members, from, to);
		}

		// 테스트용 출력 함수
		//printMembers(members);

		// 연락여부, 연락시간을 저장하는 배열
		bool visited[101];
		int times[101];
		for (int i = 0; i < 101; i++) {
			visited[i] = false;
			times[i] = -1;
		}

		// 각 멤버들에게 연락하는 재귀함수
		//contactMembers(members, visited, times, startSpot, 0);

		// 큐기반
		deque<contact> contactQueue;
		visited[startSpot] = true;
		times[startSpot] = 0;
		contactMembers(contactQueue, members, visited, times, startSpot, 0);
		while (!contactQueue.empty()) {
			contact tempContact = contactQueue.front();
			contactQueue.pop_front();
			contactMembers(contactQueue, members, visited, times, tempContact.number, tempContact.time);
		}

		// 연락하는데 가장 오래걸린 멤버를 판단
		int maxIndex = 0, maxTime = -1;
		for (int i = 0; i < 101; i++) {
			if (times[i] > maxTime) {
				maxIndex = i;
				maxTime = times[i];
			}
			else if (times[i] == maxTime) {
				if (i > maxIndex) {
					maxIndex = i;
				}
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////

		cout << "#" << caseCount << ' ';
		cout << maxIndex << endl;
	}

	return 0;
}