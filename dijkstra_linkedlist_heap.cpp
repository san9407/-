//링크드 리스트+힙을 이용하여 다익스트라 구현
//남들보다 살짝 느린거같아 불안하다.
//연산자 오버로딩하면 힙이 좀더 보기 멋져짐
#include <cstdio>
using namespace std;
const int INF = 1e9 + 1;
const long long LINF = 1e18 + 1;

struct pair
{
	int p;
	long long w;
}heap[1000000];
int heapSize;

void heapPush(int p, long long w)
{
	heap[heapSize].p = p;
	heap[heapSize].w = w;
	int current = heapSize;
	while (current > 0 && heap[current].w < heap[(current - 1) / 2].w)
	{
		pair temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}
	heapSize = heapSize + 1;
}

void heapPop()
{
	heapSize = heapSize - 1;

	heap[0] = heap[heapSize];

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = heap[current * 2 + 1].w < heap[current * 2 + 2].w ? current * 2 + 1 : current * 2 + 2;
		}

		if (heap[current].w < heap[child].w)
		{
			break;
		}

		pair temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		current = child;
	}
}


struct Node
{
	int p;
	long long w;
	Node* prev;
	Node* next;
};
int nodeCnt;
Node nodePool[1200000];

struct List
{
	Node* head;
	Node* tail;
	Node* ptr;
	/*List()
	{
		head = &nodePool[nodeCnt++];
		tail = head;
		head->next = tail;
		head->prev = head;
		tail->next = tail;
		tail->prev = head;
		ptr = head;
	}*/
	void init();
	void insert(int p, long long w);
};
List list[200000];

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

void List::insert(int p, long long w)
{
	Node* temp = &nodePool[nodeCnt++];
	temp->p = p;
	temp->w = w;
	ptr->next->prev = temp;
	temp->next = ptr->next;
	ptr->next = temp;
	temp->prev = ptr;
	ptr = temp;
}

long long dist[200000];
long long dist2[200000];
bool visit[200000];

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		int N, M;
		scanf("%d %d", &N, &M);
		nodeCnt = 0;
		heapSize = 0;
		for (register int i = 0; i < N; i++)
		{
			list[i].init();
			dist[i] = LINF;
			dist2[i] = 0;
			visit[i] = false;
		}
		for (register int i = 0; i < M; i++)
		{
			int u, v;
			long long w;
			scanf("%d %d %lld", &u, &v, &w);
			u--;
			v--;
			list[u].insert(v, w);
			list[v].insert(u, w);
		}
		heapPush(0, 0);
		dist[0] = 0;
		dist2[0] = 0;
		long long ans = 0;
		while (heapSize)
		{
			int curr = heap[0].p;
			heapPop();
			if (visit[curr])
				continue;
			visit[curr] = true;
			Node* tmp = list[curr].head->next;
			while (tmp != list[curr].tail)
			{
				int next = tmp->p;
				int nextCost = tmp->w;
				if (dist[next] >= dist[curr] + nextCost)
				{
					if (dist[next] == dist[curr] + nextCost)
					{
							dist2[next] = nextCost;
					}
					else
					{
						dist[next] = dist[curr] + nextCost;
						dist2[next] = nextCost;
						heapPush(next, dist[next]);
					}
				}
				tmp = tmp->next;
			}
		}
		for (register int i = 0; i < N; i++)
			ans += dist2[i];
		printf("#%d %lld\n", tc, ans);
	}
	return 0;
}
