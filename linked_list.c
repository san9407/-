//백준 1406 에디터 문제
//C언어로 해보았다.

#include <stdio.h>
#include <malloc.h>
#pragma warning(disable:4996)

typedef struct _Node
{
	char data;
	struct _Node* next;
	struct _Node* prev;
}Node;

int nodeCnt;
Node nodePool[600001];

typedef struct _List
{
	Node* head;
	Node* tail;
	Node* ptr;
}List;

void init(List* list)
{
	list->head = &nodePool[nodeCnt++];
	list->tail = list->head;
	list->head->next = list->tail;
	list->head->prev = list->head;
	list->tail->next = list->tail;
	list->tail->prev = list->head;
	list->ptr = list->head;
}

void add(List* list, char c)
{
	Node* temp = &nodePool[nodeCnt++];
	temp->data = c;
	list->ptr->next->prev = temp;
	temp->next = list->ptr->next;
	list->ptr->next = temp;
	temp->prev = list->ptr;
	list->ptr = temp;
}

void del(List* list)
{
	if (list->ptr != list->head)
	{
		list->ptr->prev->next = list->ptr->next;
		list->ptr->next->prev = list->ptr->prev;
		list->ptr = list->ptr->prev;
	}
}

void moveL(List* list)
{
	if (list->ptr != list->head)
		list->ptr = list->ptr->prev;
}

void moveR(List* list)
{
	if (list->ptr->next != list->tail)
		list->ptr = list->ptr->next;
}

int main()
{
	List* list=(List*)malloc(sizeof(List));
	char str[100001];
	int M,i;
	char c, x;
	scanf("%s", str);
	scanf("%d", &M);
	init(list);
	for (i = 0; str[i]; i++)
		add(list, str[i]);
	for (i = 0; i < M; i++)
	{
		scanf(" %c", &c);
		if (c == 'L')
		{
			moveL(list);
		}
		else if (c == 'D')
		{
			moveR(list);
		}
		else if (c == 'B')
		{
			del(list);
		}
		else
		{
			scanf(" %c", &x);
			add(list, x);
		}
	}
	Node* ptr = list->head->next;
	while (ptr != list->tail)
	{
		printf("%c", ptr->data);
		ptr = ptr->next;
	}
	puts("");
	return 0;
}
