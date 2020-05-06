//백준 2161
//동적할당으로 짜봤다.
//쓰레기 코드
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#pragma warning(disable:4996)

typedef struct _Node
{
	int data;
	struct _Node* next;
	struct _Node* prev;
}Node;

typedef struct _List
{
	int cnt;
	Node* head;
	Node* tail;
	Node* ptr;
}List;

void init(List* list)
{
	list->cnt = 1;
	list->head = (Node*)malloc(sizeof(Node));
	list->tail = list->head;
	list->head->next = list->tail;
	list->head->prev = list->head;
	list->tail->next = list->tail;
	list->tail->prev = list->head;
	list->ptr = list->head;
}

void add(List* list, int d)
{
	list->cnt++;
	Node* temp = malloc(sizeof(Node));
	temp->data = d;
	list->ptr->next->prev = temp;
	temp->next = list->ptr->next;
	list->ptr->next = temp;
	temp->prev = list->ptr;
	list->ptr = temp;
}

int pop(List* list)
{
	int ret = 0;
	Node* temp;
	if (list->head!=list->head->next)
	{
		list->cnt--;
		if (list->cnt == 1)
			list->ptr = list->head;
		temp = list->head->next;
		ret = temp->data;
		list->head->next = temp->next;
		free(temp);
		return ret;
	}
}

int main()
{
	int i;
	int t;
	int N;
	scanf("%d", &N);
	List* list = (List*)malloc(sizeof(List));
	init(list);
	for (i = 1; i <= N; i++)
		add(list, i);
	while (1)
	{
		t = pop(list);
		printf("%d ", t);
		if (list->cnt == 1)
		{
			puts("");
			free(list);
			return 0;
		}
		t = pop(list);
		add(list, t);
	}
	return 0;
}
