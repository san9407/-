//최적화할 부분은 아직 많이 남았지만
//1월 비형문제 이런식으로 풀었다면 비형을 땄다.
struct CAR
{
	int age;       // 0 ~ 19
	int passenger; // 2 ~ 12
	int engine;    // 1000 ~ 4999
	int price;     // 10000 ~ 39999
};
int fromA, toA;
int fromP, toP;
int fromE, toE;
int fromPrice, toPrice;
int sCnt;


template <typename It>
void _swap(It& a, It& b)
{
	It c = a;
	a = b;
	b = c;
}

struct Node
{
	int age;
	int passenger;
	int engine;
	int price;
	Node* prev;
	Node* next;
};
int nodeCnt;
Node nodePool[2300000];

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
	void insert(int age, int passenger, int engine, int price);
	int remove();
	int removeAll();
	void find();
};
List list[20][11][40][30];
List re[12000];

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

void List::insert(int age, int passenger, int engine, int price)
{
	Node* temp = &nodePool[nodeCnt++];
	temp->age = age;
	temp->passenger = passenger;
	temp->engine = engine;
	temp->price = price;
	ptr->next->prev = temp;
	temp->next = ptr->next;
	ptr->next = temp;
	temp->prev = ptr;
	ptr = temp;
}

int List::remove()
{
	int ret = -1;
	Node* temp = head->next;
	while (temp != tail)
	{
		if ((fromA <= temp->age && temp->age <= toA) && (fromP <= temp->passenger && temp->passenger <= toP) && (fromE <= temp->engine && temp->engine <= toE) && (fromPrice <= temp->price && temp->price <= toPrice))
		{
			if (temp != head)
			{
				re[sCnt].insert(temp->age, temp->passenger, temp->engine, temp->price);
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp = temp->prev;
				ptr = temp;
				ret = 1;
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

void List::find()
{
	Node* temp = head->next;
	while (temp != tail)
	{
		if (temp != head)
		{
			list[temp->age][temp->passenger - 2][(temp->engine - 1000) / 100][(temp->price - 10000) / 1000].insert(temp->age, temp->passenger, temp->engine, temp->price);
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			temp = temp->prev;
			ptr = temp;
		}
		temp = temp->next;
	}
}

void buy(CAR car)
{
	list[car.age][car.passenger - 2][(car.engine - 1000) / 100][(car.price - 10000) / 1000].insert(car.age, car.passenger, car.engine, car.price);
}


void filter_by_age(int from, int to)
{
	if (from > to)
		_swap(from, to);
	fromA = from;
	toA = to;
}


void filter_by_passenger(int from, int to)
{
	if (from > to)
		_swap(from, to);
	fromP = from;
	toP = to;
}


void filter_by_engine(int from, int to)
{
	if (from > to)
		_swap(from, to);
	fromE = from;
	toE = to;
}


void filter_by_price(int from, int to)
{
	if (from > to)
		_swap(from, to);
	fromPrice = from;
	toPrice = to;
}

int sell(void)
{
	int ret = -1;
	bool flag = false;
	for (int i = fromA; i <= toA; i++)
	{
		for (int j = fromP - 2; j <= toP - 2; j++)
		{
			for (int k = (fromE - 1000) / 100; k <= (toE - 1000) / 100; k++)
			{
				for (int l = (fromPrice - 10000) / 1000; l <= (toPrice - 10000) / 1000; l++)
				{
					ret = list[i][j][k][l].remove();
					if (ret != -1)
					{
						flag = true;
					}
				}
			}
		}
	}
	if (flag)
	{
		ret = sCnt;
		sCnt++;
	}
	return ret; // order_number ( >= 0)
}


void refund(int order_number)
{
	re[order_number].find();
}


int empty(void)
{
	int ret = 0;
	nodeCnt = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			for (int k = 0; k < 40; k++)
			{
				for (int l = 0; l < 30; l++)
				{
					ret += list[i][j][k][l].removeAll();
					list[i][j][k][l].init();
				}
			}
		}
	}
	for (int i = 0; i < 12000; i++)
	{
		re[i].removeAll();
		re[i].init();
	}
	//nodeCnt = 20 * 11 * 40 * 30 + 131;
	sCnt = 0;
	return ret;
}
