//백준 1448 삼각형 만들기
//머지소트
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)

int arr[1000001];
int arr2[1000001];

void merge(int left, int right)
{
	int mid = (left + right) / 2;

	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid && j <= right)
	{
		if (arr[i] < arr[j])
			arr2[k++] = arr[i++];
		else
			arr2[k++] = arr[j++];
	}
	while (i <= mid)
		arr2[k++] = arr[i++];
	while (j <= right)
		arr2[k++] = arr[j++];
	for (i = left; i <= right; i++)
		arr[i] = arr2[i];
}

void msort(int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		msort(left, mid);
		msort(mid + 1, right);
		merge(left, right);
	}
}

int main()
{
	int i, j;
	int N;
	int a, b, c;
	scanf("%d", &N);
	for (i = 0; i < N; i++)
		scanf("%d", arr + i);
	msort(0, N - 1);
	a = N - 3;
	b = N - 2;
	c = N - 1;
	while (a >= 0 && b >= 0)
	{
		if (arr[c] < arr[b] + arr[a])
		{
			printf("%d\n", arr[a] + arr[b] + arr[c]);
			return 0;
		}
		else
		{
			c--;
			b--;
			a--;
		}
	}
	puts("-1");
	return 0;
}
