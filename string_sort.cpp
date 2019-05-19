#include <cstdio>
#pragma warning(disable:4996)

template <typename It>
void _swap(It& a, It& b)
{
	It c = a;
	a = b;
	b = c;
}

template<typename It,typename Comp>
void _sort(It begin, It end, Comp comp)
{
	if (begin == end)
		return;
	_swap(*begin, *((end - begin) / 2 + begin));
	It pi = begin;
	It le = begin + 1;
	It ri = end - 1;
	while (le <= ri)
	{
		while (le <= ri && !comp(*pi, *le))
			le++;
		while (le <= ri && !comp(*ri, *pi))
			ri--;
		if (le <= ri)
			_swap(*le, *ri);
	}
	_swap(*pi, *ri);
	_sort(begin, ri, comp);
	_sort(ri + 1, end, comp);
}

int cstrlen(char* str)
{
	int i;
	for (i = 0; str[i]; i++);
	return i;
}

int cstrcmp(char* A, char* B)
{
	int i = 0;
	while (A[i] != 0)
	{
		if (A[i] != B[i])
			break;
		i++;
	}
	return (A[i] - B[i]);
}

void cstrcpy(char* A, char* B)
{
	for (int i = 0; B[i]; i++)
	{
		A[i] = B[i];
	}
}

struct Node
{
	int cnt;
	char data[21];
};

bool cmp(Node& A, Node& B)
{
	if (A.cnt == B.cnt)
		return cstrcmp(A.data, B.data)<=0;
	return A.cnt > B.cnt;
}


Node arr[100];

int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int cnt;
		char str[21];
		scanf("%d %s", &cnt, str);
		arr[i].cnt = cnt;
		cstrcpy(arr[i].data, str);
	}
	_sort(arr, arr + N, cmp);
	for (int i = 0; i < N; i++)
	{
		printf("%d %s\n", arr[i].cnt, arr[i].data);
	}
	return 0;
}
