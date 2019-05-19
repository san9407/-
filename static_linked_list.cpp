//1406 에디터문제 정적으로 리스트 짜기
#include <cstdio>
using namespace std;

struct Node
{
	char data;
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
			ptr=ptr->prev;
		}
	}
	void moveL()
	{
		if (ptr != head)
			ptr = ptr->prev;
	}
	void moveR()
	{
		if (ptr->next != tail)
			ptr = ptr->next;
	}
};


int main()
{
	char str[100001];
	scanf("%s", str);
	List list;
	for (int i = 0; str[i]; i++)
		list.add(str[i]);
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		char c;
		scanf(" %c", &c);
		if (c == 'L')
		{
			list.moveL();
		}
		else if (c == 'D')
		{
			list.moveR();
		}
		else if (c == 'B')
		{
			list.del();
		}
		else if (c == 'P')
		{
			char x;
			scanf(" %c", &x);
			list.add(x);
		}
	}
	Node* ptr = list.head->next;
	while (ptr != list.tail)
	{
		printf("%c", ptr->data);
		ptr = ptr->next;
	}
	puts("");
	return 0;
}
