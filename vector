//https://github.com/baactree/Algorithm/tree/master/Stl
//박트리님꺼
#pragma once
#include <iostream>
using namespace std;

template<class T>
class _vector
{
public:
	int _size;
	int capacity;
	T *arr;
	_vector()
	{
		_size = 0;
		capacity = 32;
		arr = new T[capacity];
	}
	_vector(int k)
	{
		_size = k;
		capacity = k;
		arr = new T[capacity];
	}
	~_vector()
	{
		delete[] arr;
	}
	void clear()
	{
		delete[] arr;
		_size = 0;
		capacity = 32;
		arr = new T[capacity];
	}
	void resize(int k)
	{
		T* temp = new T[k];
		for (int i = 0; i < _size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
		_size = capacity = k;
	}
	int size() const
	{
		return _size;
	}
	T* begin() const
	{
		return &arr[0];
	}
	T* end() const
	{
		return &arr[0] + _size;
	}
	void push_back(T val)
	{
		if (_size == capacity)
		{
			resize(_size * 2);
			_size /= 2;
		}
		arr[_size++] = val;
	}
	void pop_back()
	{
		_size--;
	}
	T& operator [](int idx)
	{
		return arr[idx];
	}
	T operator [](int idx) const
	{
		return arr[idx];
	}
};
