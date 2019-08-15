//링크드리스트의 최종본
//삽입 삭제 검색 다 있음
//폴더관리자 문제 유저파일
int cstrlen(char* A)
{
	register int i;
	for (i = 0; A[i]; i++);
	return i;
}

int cstrcmp(char* A, char* B)
{
	register int i = 0;
	while (A[i])
	{
		if (A[i] != B[i])
			break;
		i++;
	}
	return A[i] - B[i];
}

void cstrcpy(char* A, char* B)
{
	register int i;
	for (i = 0; B[i]; i++)
		A[i] = B[i];
	A[i] = '\0';
}

struct Node
{
	int idx;
	char data[21];
	Node* prev;
	Node* next;
};

int nodeCnt;
Node nodePool[54002];
int cnt;
char s[3][3] = { "/","..","*" };
char inf[21] = "zzzzzzzzzzzzzzzzzzzz";
int curIdx;

struct List
{
	Node* head;
	Node* tail;
	Node* ptr;
	List()
	{
		head = &nodePool[nodeCnt++];
		tail = head;
		head->next = tail;
		head->prev = head;
		tail->next = tail;
		tail->prev = head;
		ptr = head;
	}

	void init();
	void make(char* str);
	void change(char* str);
	int remove(char* str);
	int remove2(int n, char* str);
	int removeAll();
	int find(char* str);
	int find2(int n, char* str);
	int findAll();
};
List list[27001];

void List::init()
{
	head = &nodePool[nodeCnt++];
	tail = head;
	head->next = tail;
	head->prev = head;
	tail->next = tail;
	tail->prev = head;
	ptr = head;
}

void List::make(char* str)
{
	bool flag = false;
	Node* tmp = head->next;
	while (tmp != tail)
	{
		if (cstrcmp(tmp->data, str) == 0)
		{
			flag = true;
			return;
		}
		tmp = tmp->next;
	}
	if (!flag)
	{
		Node* temp = &nodePool[nodeCnt++];
		cstrcpy(temp->data, str);
		list[++cnt].head->idx = curIdx;
		temp->idx = cnt;
		ptr->next->prev = temp;
		temp->next = ptr->next;
		ptr->next = temp;
		temp->prev = ptr;
		ptr = temp;
	}
}

void List::change(char* str)
{
	if (cstrcmp(str, s[0]) == 0)
	{
		curIdx = 0;
	}
	else if (cstrcmp(str, s[1]) == 0)
	{
		if (curIdx != 0)
		{
			curIdx = head->idx;
		}
	}
	else if (cstrcmp(str, s[2]) == 0)
	{
		Node* tmp = head->next;
		char tname[21];
		int tidx = -1;
		cstrcpy(tname, inf);
		while (tmp != tail)
		{
			if (cstrcmp(tname, tmp->data) >= 0)
			{
				cstrcpy(tname, tmp->data);
				tidx = tmp->idx;
			}
			tmp = tmp->next;
		}
		if (tidx != -1)
		{
			curIdx = tidx;
		}
	}
	else
	{
		int len = cstrlen(str);
		if (str[len - 1] == '*')
		{
			Node* tmp = head->next;
			char tname[21];
			int tidx = -1;
			cstrcpy(tname, inf);
			while (tmp != tail)
			{
				bool flag = false;
				for (register int i = 0; i < len - 1; i++)
				{
					if (str[i] != tmp->data[i])
					{
						flag = true;
						break;
					}
				}
				if (!flag)
				{
					if (cstrcmp(tname, tmp->data) >= 0)
					{
						cstrcpy(tname, tmp->data);
						tidx = tmp->idx;
					}
				}
				tmp = tmp->next;
			}
			if (tidx != -1)
			{
				curIdx = tidx;
			}
		}
		else
		{
			Node* tmp = head->next;
			while (tmp != tail)
			{
				if (cstrcmp(tmp->data, str) == 0)
				{
					curIdx = tmp->idx;
					break;
				}
				tmp = tmp->next;
			}
		}
	}
}

int List::remove(char* str)
{
	int ret = 0;
	Node* temp = head->next;
	while (temp != tail)
	{
		if (cstrcmp(temp->data, str) == 0)
		{
			ret += list[temp->idx].removeAll();
			if (temp != head)
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp = temp->prev;
				ptr = temp;
				ret++;
				break;
			}
		}
		temp = temp->next;
	}
	return ret;
}

int List::remove2(int n, char* str)
{
	int ret = 0;
	Node* temp = head->next;
	while (temp != tail)
	{
		bool flag = false;
		for (int i = 0; i < n; i++)
		{
			if (temp->data[i] != str[i])
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			ret += list[temp->idx].removeAll();
			if (temp != head)
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp = temp->prev;
				ptr = temp;
				ret++;
			}
		}
		temp = temp->next;
	}
	return ret;
}

int List::removeAll()
{
	int ret = 0;
	Node* temp = head->next;
	while (temp != tail)
	{
		ret += list[temp->idx].removeAll();
		if (temp != head)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			temp = temp->prev;
			ptr = temp;
			ret++;
		}
		temp = temp->next;
	}
	return ret;
}

int List::find(char* str)
{
	int ret = 0;
	Node* temp = head->next;
	while (temp != tail)
	{
		ret += list[temp->idx].find(str);
		if (cstrcmp(temp->data, str) == 0)
		{
			ret++;
		}
		temp = temp->next;
	}
	return ret;
}

int List::find2(int n, char* str)
{
	int ret = 0;
	Node* temp = head->next;
	while (temp != tail)
	{
		bool flag = false;
		ret += list[temp->idx].find2(n, str);
		for (int i = 0; i < n; i++)
		{
			if (temp->data[i] != str[i])
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			ret++;
		}
		temp = temp->next;
	}
	return ret;
}

int List::findAll()
{
	int ret = 0;
	Node* temp = head->next;
	while (temp != tail)
	{
		ret += list[temp->idx].findAll();
		ret++;
		temp = temp->next;
	}
	return ret;
}

void init()
{
	cnt = 0;
	nodeCnt = 0;
	curIdx = 0;
	for (register int i = 0; i < 27001; i++)
		list[i].init();
}

void make(char keyword[])
{
	list[curIdx].make(keyword);
}

void change(char keyword[])
{
	list[curIdx].change(keyword);
}
int remove(char keyword[])
{
	int len = cstrlen(keyword);
	int ret = 0;
	if (cstrcmp(keyword, s[2]) == 0)
	{
		ret = list[curIdx].removeAll();
	}
	else if (keyword[len - 1] == '*')
	{
		keyword[len - 1] = '\0';
		ret = list[curIdx].remove2(len - 1, keyword);
	}
	else
		ret = list[curIdx].remove(keyword);
	return ret;
}

int find(char keyword[])
{
	int len = cstrlen(keyword);
	int ret = 0;
	if (cstrcmp(keyword, s[2]) == 0)
	{
		ret = list[curIdx].findAll();
	}
	else if (keyword[len - 1] == '*')
	{
		keyword[len - 1] = '\0';
		ret = list[curIdx].find2(len - 1, keyword);
	}
	else
		ret = list[curIdx].find(keyword);
	return ret;
}
