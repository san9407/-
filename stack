//https://github.com/baactree/Algorithm/tree/master/Stl
//박트리님껄 보고 그대로 따라쳤는데 정말 좋다.
#pragma once
#include <iostream>
using namespace std;

template<class T>
class _stack
{
public:
	struct Node
	{
		T val;
		Node* next;
		Node(T val) :val(val), next(0) {}
	};
	Node* head;
	int _size;
	_stack()
	{
		head = 0;
		_size = 0;
	}
	void push(T val)
	{
		Node* temp = new Node(val);
		if (head == 0)
			head = temp;
		else
		{
			temp->next = head;
			head = temp;
		}
		_size++;
	}
	void pop()
	{
		Node* temp = head;
		head = head->next;
		delete temp;
		_size--;
	}
	bool empty() const
	{
		return _size == 0;
	}
	int size() const
	{
		return _size;
	}
	T top() const
	{
		return head->val;
	}
};
