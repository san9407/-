//정적으로 짜기2 이차원 링크드 리스트
#include <cstdio>
using namespace std;
#pragma warning(disable:4996)

struct Node
{
	int data;
	Node* prev;
	Node* next;
};

int nodeCnt = 0;
Node nodePool[600001];
Node* newNode()
{
	return &nodePool[nodeCnt++];
}

struct List
{
	Node* head;
	Node* tail;
	Node* ptr;

	List()
	{
		head = newNode();
		tail = head;
		head->next = tail;
		head->prev = tail;
		tail->next = head;
		tail->prev = head;
		ptr = head;
	}

	void add(char c)
	{
		Node* temp = newNode();
		temp->data = c;
		ptr->next->prev = temp;
		temp->next = ptr->next;
		ptr->next = temp;
		temp->prev = ptr;
		ptr = temp;
	}

	void del()
	{
		if (ptr != head)
		{
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			ptr = ptr->prev;
		}
	}
}arr[500][500];


int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int x, y, d;
		scanf("%d %d %d", &x, &y,&d);
		arr[x][y].add(d);
	}
	int x, y;
	scanf("%d %d", &x, &y);
	Node* ptr = arr[x][y].head->next;
	while (ptr != arr[x][y].tail)
	{
		printf("%d ", ptr->data);
		ptr = ptr->next;
	}
	puts("");
	return 0;
}
